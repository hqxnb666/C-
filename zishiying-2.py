# 导入必要的库
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import torch
import torch.nn as nn
import torch.nn.functional as F
import torch.optim as optim
from torch.utils.data import DataLoader, Dataset
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error, mean_squared_error, r2_score
from statsmodels.tsa.arima.model import ARIMA
import warnings
warnings.filterwarnings('ignore')
from pykalman import KalmanFilter
# 设置中文字体
plt.rcParams['font.family'] = 'SimHei' 
plt.rcParams['axes.unicode_minus'] = False 

# ------------------------------
# 1. 数据准备
# ------------------------------

# 数据模拟函数
def generate_ship_draft_data(num_samples=2000, anomaly_ratio=0.05, random_seed=42):
    np.random.seed(random_seed)
    
    base_value = 1820.0  # 厘米

    # 波浪效应参数
    amplitude = 5.0       # 振幅
    period = 200          # 周期

    # 时间步
    time_steps = np.arange(num_samples)

    # 模拟波浪效应
    wave_effect = amplitude * np.sin(2 * np.pi * time_steps / period)

    # 添加随机噪声
    noise = np.random.normal(loc=0.0, scale=0.5, size=num_samples)

    # 生成正常的吃水读数
    draft_values = base_value + wave_effect + noise

    # 插入异常值
    num_anomalies = int(num_samples * anomaly_ratio)
    anomaly_indices = np.random.choice(num_samples, num_anomalies, replace=False)
    draft_values[anomaly_indices] += np.random.choice([-20, 20], size=num_anomalies)

    # 创建 DataFrame
    df = pd.DataFrame({
        'Frame': time_steps,
        'Draft(cm)': draft_values,
        'Anomaly': 0
    })

    # 标记异常值
    df.loc[anomaly_indices, 'Anomaly'] = 1

    return df

# 生成数据集
df = generate_ship_draft_data(num_samples=2000, anomaly_ratio=0.05)

# 数据预处理
# 归一化
scaler = MinMaxScaler()
draft_values = df['Draft(cm)'].values.reshape(-1, 1)
draft_values_scaled = scaler.fit_transform(draft_values)

# 序列创建
def create_sequences(values, seq_len):
    xs = []
    ys = []
    for i in range(len(values) - seq_len):
        x = values[i:(i + seq_len)]
        y = values[i + seq_len]
        xs.append(x)
        ys.append(y)
    return np.array(xs), np.array(ys)

seq_len = 50
X, y = create_sequences(draft_values_scaled, seq_len)
anomaly_labels = df['Anomaly'].values[seq_len:]

# 划分数据集（不去除异常）
X_train_val, X_test, y_train_val, y_test, anomaly_train_val, anomaly_test = train_test_split(
    X, y, anomaly_labels, test_size=0.15, shuffle=False)

X_train, X_val, y_train, y_val, anomaly_train, anomaly_val = train_test_split(
    X_train_val, y_train_val, anomaly_train_val, test_size=0.1 / 0.85, shuffle=False)

print(f"训练样本数量: {len(X_train)}")
print(f"验证样本数量: {len(X_val)}")
print(f"测试样本数量: {len(X_test)}")

# 定义数据集类
class ShipDraftDataset(Dataset):
    def __init__(self, sequences, labels, anomaly_labels):
        self.sequences = sequences
        self.labels = labels
        self.anomaly_labels = anomaly_labels

    def __len__(self):
        return len(self.sequences)

    def __getitem__(self, idx):
        return (
            torch.tensor(self.sequences[idx], dtype=torch.float32),
            torch.tensor(self.labels[idx], dtype=torch.float32),
            torch.tensor(self.anomaly_labels[idx], dtype=torch.float32)
        )

# 创建数据集
train_dataset = ShipDraftDataset(X_train, y_train, anomaly_train)
val_dataset = ShipDraftDataset(X_val, y_val, anomaly_val)
test_dataset = ShipDraftDataset(X_test, y_test, anomaly_test)

batch_size = 64
train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
val_loader = DataLoader(val_dataset, batch_size=batch_size)
test_loader = DataLoader(test_dataset, batch_size=batch_size)

# ------------------------------
# 2. 模型实现
# ------------------------------


# 2.2 提出的CNN-Transformer模型

class PositionalEncoding(nn.Module):
    def __init__(self, d_model, max_len=5000):
        super(PositionalEncoding, self).__init__()
        self.position_embedding = nn.Embedding(max_len, d_model)

    def forward(self, x):
        positions = torch.arange(0, x.size(1), device=x.device).unsqueeze(0)
        position_embeddings = self.position_embedding(positions)
        return x + position_embeddings

class AdaptiveAttention(nn.Module):
    def __init__(self, d_model, n_heads):
        super(AdaptiveAttention, self).__init__()
        self.n_heads = n_heads
        self.d_k = d_model // n_heads

        self.q_linear = nn.Linear(d_model, d_model)
        self.k_linear = nn.Linear(d_model, d_model)
        self.v_linear = nn.Linear(d_model, d_model)
        self.out_linear = nn.Linear(d_model, d_model)
        
        # 自适应缩放参数
        self.scale = nn.Parameter(torch.ones(1))
        # 时间衰减因子
        self.time_decay = nn.Parameter(torch.ones(1, n_heads, 1, 1))
        # 门控机制
        self.gate = nn.Sigmoid()

    def forward(self, q, k, v):
        bs = q.size(0)

        # 线性变换并拆分成多头
        k = self.k_linear(k).view(bs, -1, self.n_heads, self.d_k)
        q = self.q_linear(q).view(bs, -1, self.n_heads, self.d_k)
        v = self.v_linear(v).view(bs, -1, self.n_heads, self.d_k)

        # 转置计算注意力
        k = k.transpose(1, 2)  # [bs, n_heads, seq_len, d_k]
        q = q.transpose(1, 2)
        v = v.transpose(1, 2)

        # 计算注意力
        scores = torch.matmul(q, k.transpose(-2, -1)) / np.sqrt(self.d_k)

        # 自适应缩放
        scores = scores * self.scale

        # 加入时间衰减因子
        seq_len = scores.size(-1)
        time_decay_factors = torch.exp(-self.time_decay * torch.abs(torch.arange(seq_len).unsqueeze(0).unsqueeze(0).unsqueeze(0).to(q.device)))
        scores = scores * time_decay_factors

        # 计算注意力权重
        attn = torch.softmax(scores, dim=-1)

        # 门控机制
        G = self.gate(scores)
        attn = attn * G

        # 存储注意力权重
        self.attn_weights = attn

        # 加权求和
        context = torch.matmul(attn, v)
        context = context.transpose(1, 2).contiguous().view(bs, -1, self.n_heads * self.d_k)

        # 输出线性变换
        out = self.out_linear(context)
        return out

class EncoderLayer(nn.Module):
    def __init__(self, d_model, n_heads, d_ff, dropout=0.1):
        super(EncoderLayer, self).__init__()
        self.attention = AdaptiveAttention(d_model, n_heads)
        self.norm1 = nn.LayerNorm(d_model)
        self.dropout1 = nn.Dropout(dropout)

        self.ff = nn.Sequential(
            nn.Linear(d_model, d_ff),
            nn.ReLU(),
            nn.Linear(d_ff, d_model)
        )
        self.norm2 = nn.LayerNorm(d_model)
        self.dropout2 = nn.Dropout(dropout)

    def forward(self, x):
        attn_out = self.attention(x, x, x)
        x = x + self.dropout1(attn_out)
        x = self.norm1(x)

        ff_out = self.ff(x)
        x = x + self.dropout2(ff_out)
        x = self.norm2(x)
        return x

class Encoder(nn.Module):
    def __init__(self, num_layers, d_model, n_heads, d_ff, dropout=0.1):
        super(Encoder, self).__init__()
        self.layers = nn.ModuleList([
            EncoderLayer(d_model, n_heads, d_ff, dropout) for _ in range(num_layers)
        ])

    def forward(self, x):
        for layer in self.layers:
            x = layer(x)
        return x

class DropConnectLinear(nn.Linear):
    def __init__(self, in_features, out_features, bias=True, drop_connect_rate=0.5):
        super(DropConnectLinear, self).__init__(in_features, out_features, bias)
        self.drop_connect_rate = drop_connect_rate

    def forward(self, input):
        if self.training:
            mask = torch.bernoulli(torch.full_like(self.weight, 1 - self.drop_connect_rate))
            weight = self.weight * mask
        else:
            weight = self.weight * (1 - self.drop_connect_rate)
        return F.linear(input, weight, self.bias)

class CNNTransformerProposed(nn.Module):
    def __init__(self, seq_len, d_model, n_heads, num_layers, d_ff, kernel_size=3, dropout=0.1):
        super(CNNTransformerProposed, self).__init__()
        self.conv1 = nn.Conv1d(in_channels=1, out_channels=d_model, kernel_size=kernel_size, padding=kernel_size//2)
        self.bn1 = nn.BatchNorm1d(d_model)
        self.relu = nn.ReLU()
        self.positional_encoding = PositionalEncoding(d_model, max_len=seq_len)
        self.encoder = Encoder(num_layers, d_model, n_heads, d_ff, dropout)
        self.output_linear = DropConnectLinear(d_model, 1, drop_connect_rate=0.5)
    
    def forward(self, x):
        # x 形状: [batch_size, seq_len, 1]
        x = x.permute(0, 2, 1)  # 转换为 [batch_size, channels, seq_len]
        x = self.conv1(x)
        x = self.bn1(x)
        x = self.relu(x)
        x = x.permute(0, 2, 1)  # 转换回 [batch_size, seq_len, d_model]
        x = self.positional_encoding(x)
        x = self.encoder(x)
        out = self.output_linear(x[:, -1, :])
        return out

# ------------------------------
# 3. 训练和评估模型
# ------------------------------

# 定义加权MSE损失函数
class WeightedMSELoss(nn.Module):
    def __init__(self, anomaly_weight=10.0):
        super(WeightedMSELoss, self).__init__()
        self.anomaly_weight = anomaly_weight
        self.mse = nn.MSELoss(reduction='none')

    def forward(self, pred, target, anomaly_label):
        # anomaly_label: [batch_size, 1]
        loss = self.mse(pred, target)
        # 根据异常标签对损失进行加权
        weight = torch.where(anomaly_label == 1, self.anomaly_weight, 1.0)
        loss = loss * weight
        return loss.mean()

# 定义训练函数
def train_model_proposed(model, train_loader, val_loader, num_epochs=50, l1_lambda=1e-5, patience=5):
    criterion = WeightedMSELoss(anomaly_weight=10.0)
    optimizer = optim.Adam(model.parameters(), lr=1e-4, weight_decay=1e-5)
    best_val_loss = float('inf')
    wait = 0

    for epoch in range(num_epochs):
        model.train()
        train_loss = 0.0
        for X_batch, y_batch, anomaly_batch in train_loader:
            X_batch = X_batch.to(device)
            y_batch = y_batch.to(device)
            anomaly_batch = anomaly_batch.to(device)

            optimizer.zero_grad()
            outputs = model(X_batch)
            loss = criterion(outputs, y_batch, anomaly_batch)
            l1_norm = sum(p.abs().sum() for p in model.parameters())
            loss = loss + l1_lambda * l1_norm
            loss.backward()
            optimizer.step()
            train_loss += loss.item() * X_batch.size(0)
        train_loss /= len(train_loader.dataset)

        model.eval()
        val_loss = 0.0
        with torch.no_grad():
            for X_batch, y_batch, anomaly_batch in val_loader:
                X_batch = X_batch.to(device)
                y_batch = y_batch.to(device)
                anomaly_batch = anomaly_batch.to(device)

                outputs = model(X_batch)
                loss = criterion(outputs, y_batch, anomaly_batch)
                val_loss += loss.item() * X_batch.size(0)
        val_loss /= len(val_loader.dataset)

        print(f'Epoch {epoch+1}, Train Loss: {train_loss:.6f}, Val Loss: {val_loss:.6f}')

        # 早停策略
        if val_loss < best_val_loss:
            best_val_loss = val_loss
            wait = 0
            best_model_state = model.state_dict()
        else:
            wait += 1
            if wait >= patience:
                print('早停')
                break

    # 加载最佳模型
    model.load_state_dict(best_model_state)
    return model

# 定义评估函数
def evaluate_model(y_true, y_pred):
    mae = mean_absolute_error(y_true, y_pred)
    rmse = np.sqrt(mean_squared_error(y_true, y_pred))
    r2 = r2_score(y_true, y_pred)
    return mae, rmse, r2

# 设置设备
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')

# 模型参数
d_model = 64
n_heads = 4
num_layers = 2
d_ff = 128
kernel_size = 3
dropout = 0.1

# 初始化模型
proposed_model = CNNTransformerProposed(seq_len=seq_len, d_model=d_model, n_heads=n_heads, num_layers=num_layers, d_ff=d_ff, kernel_size=kernel_size, dropout=dropout).to(device)

# 设置训练参数
num_epochs = 50
patience = 5  # 早停策略
l1_lambda = 1e-5  # L1正则化系数

# 训练模型
print("\n开始训练提出的CNN-Transformer模型...")
proposed_model = train_model_proposed(proposed_model, train_loader, val_loader, num_epochs=num_epochs, l1_lambda=l1_lambda, patience=patience)

# 模型测试
proposed_model.eval()
test_predictions = []
test_targets = []
test_anomalies = []

with torch.no_grad():
    for X_batch, y_batch, anomaly_batch in test_loader:
        X_batch = X_batch.to(device)
        y_batch = y_batch.to(device)

        outputs = proposed_model(X_batch)
        test_predictions.extend(outputs.cpu().numpy())
        test_targets.extend(y_batch.cpu().numpy())
        test_anomalies.extend(anomaly_batch.numpy())

# 逆归一化到原始尺度
test_predictions = scaler.inverse_transform(np.array(test_predictions).reshape(-1, 1))
test_targets = scaler.inverse_transform(np.array(test_targets).reshape(-1, 1))

# 应用滑动窗口平均进行校正
def moving_average(data, window_size=5):
    return np.convolve(data, np.ones(window_size)/window_size, mode='valid')

window_size = 5
calibrated_predictions = moving_average(test_predictions.flatten(), window_size=window_size)
calibrated_targets = moving_average(test_targets.flatten(), window_size=window_size)
anomaly_labels_calibrated = moving_average(test_anomalies, window_size=window_size)

# 将滑动窗口后的异常标签二值化，任何窗口内存在异常即视为异常
anomaly_labels_calibrated = (anomaly_labels_calibrated > 0).astype(int)

# 仅保留非异常的预测结果进行评估
valid_indices = anomaly_labels_calibrated == 0
calibrated_predictions_valid = calibrated_predictions[valid_indices]
calibrated_targets_valid = calibrated_targets[valid_indices]
# 将滑动窗口后的异常标签二值化，任何窗口内存在异常即视为异常
anomaly_labels_calibrated = (anomaly_labels_calibrated > 0).astype(int)


# 计算评价指标
mae_proposed, rmse_proposed, r2_proposed = evaluate_model(calibrated_targets_valid, calibrated_predictions_valid)
print(f"提出的模型 - MAE: {mae_proposed:.4f}, RMSE: {rmse_proposed:.4f}, R^2: {r2_proposed:.4f}")

# ------------------------------
# 4. 结果比较和分析
# ------------------------------

# 汇总结果
mae, rmse, r2 = evaluate_model(test_targets, test_predictions)
print(f"CNN-Transformer 模型 - MAE: {mae:.4f}, RMSE: {rmse:.4f}, R^2: {r2:.4f}")

# ------------------------------
# 5. 可视化结果
# ------------------------------

# 5.1 预测结果可视化

# 模拟初始静水值的真值
true_draft_initial = df['Draft(cm)'].iloc[0]  # 初始静水值

# 计算最终的船舶实际吃水值
final_predictions = true_draft_initial + (calibrated_predictions - calibrated_predictions[0])

# 绘制结果对比图
plt.figure(figsize=(15, 5))
plt.plot(calibrated_targets_valid, label='真实值（校正后）', color='blue', alpha=0.6)
plt.plot(calibrated_predictions_valid, label='预测值（校正后）', color='orange', alpha=0.7)
plt.plot(final_predictions[valid_indices], label='最终预测吃水值', color='green', linestyle='--')
plt.xlabel('样本序号')
plt.ylabel('吃水深度（厘米）')
plt.title('提出模型预测值与真实值对比（校正后）')
plt.legend()
plt.show()

# 5.2 残差分析
# 计算残差
residuals = calibrated_targets_valid - calibrated_predictions_valid

# 绘制残差分布的直方图和密度图
plt.figure(figsize=(15, 5))
sns.histplot(residuals, kde=True, bins=30, color='green')
plt.xlabel('残差（厘米）')
plt.ylabel('频数')
plt.title('提出模型残差分布图')
plt.show()

# 5.3 注意力权重可视化
# 获取一批数据
X_batch, y_batch, anomaly_batch = next(iter(test_loader))
X_batch = X_batch.to(device)

# 前向传播获取注意力权重
proposed_model.eval()
with torch.no_grad():
    outputs = proposed_model(X_batch)
    # 获取注意力权重
    attn_weights = proposed_model.encoder.layers[0].attention.attn_weights  # [batch_size, n_heads, seq_len, seq_len]

# 可视化前5个样本和前2个头的注意力权重
#for sample_idx in range(5):
   # for head_idx in range(2):
       # selected_attn = attn_weights[sample_idx, head_idx].cpu().numpy()
        #plt.figure(figsize=(10, 8))
        #sns.heatmap(selected_attn, cmap='viridis')
       # plt.title(f'提出模型注意力权重热力图 - 样本 {sample_idx+1}, 头 {head_idx+1}')
       # plt.xlabel('输入序列位置')
       # plt.ylabel('输入序列位置')
        #plt.show()
# ------------------------------
# 6. 最终模型评估
# ------------------------------

# 计算最终校正后的预测值与真实值之间的误差
mae_final, rmse_final, r2_final = evaluate_model(calibrated_targets_valid, final_predictions[valid_indices])

# 使用模型预测的校正后结果作为观测值
observations = calibrated_predictions_valid  # 已经经过滑动平均校正的预测值
targets = calibrated_targets_valid  # 对应的真实值

# 定义卡尔曼滤波器参数
transition_matrices = [1]  # 状态转移矩阵，假设状态不变
observation_matrices = [1]  # 观测矩阵，假设直接观测到状态

# 初始化卡尔曼滤波器
kf = KalmanFilter(
    transition_matrices=transition_matrices,
    observation_matrices=observation_matrices,
    initial_state_mean=observations[0],  # 初始状态估计为第一个观测值
    initial_state_covariance=1,          # 初始协方差，表示初始不确定性
    observation_covariance=1,            # 测量噪声协方差 R
    transition_covariance=0.1            # 过程噪声协方差 Q
)

# 运行滤波器
state_estimates = kf.filter(observations)[0]  # 获取滤波后的状态估计

# 如果 final_prediction_kalman 是一个数组，取它的最后一个元素作为预测值
final_prediction_kalman = state_estimates[-1]

# 打印最后一个卡尔曼滤波器的预测值，确保它是一个标量
print(f"卡尔曼滤波器估计的最终吃水值: {final_prediction_kalman[0]:.2f} cm" if isinstance(final_prediction_kalman, np.ndarray) else f"卡尔曼滤波器估计的最终吃水值: {final_prediction_kalman:.2f} cm")

# 初始净水真值
initial_true_value = df['Draft(cm)'].iloc[0]  # 或者使用 base_value（1820.0）

# 计算误差
error_kalman = final_prediction_kalman - initial_true_value
print(f"与净水真值的误差: {error_kalman[0]:.2f} cm" if isinstance(error_kalman, np.ndarray) else f"与净水真值的误差: {error_kalman:.2f} cm")

# 评估卡尔曼滤波器的效果
mae_kalman, rmse_kalman, r2_kalman = evaluate_model(targets, state_estimates)
print(f"卡尔曼滤波器 - MAE: {mae_kalman:.4f}, RMSE: {rmse_kalman:.4f}, R²: {r2_kalman:.4f}")

# 绘制最终唯一预测值与净水真值的对比
plt.figure(figsize=(15, 5))

# 假设净水真值是一个固定的常数
# 这里假设您的净水真值存储在 `initial_true_value` 中
plt.plot([initial_true_value] * len(targets), label='净水真值', color='blue', alpha=0.6)  # 蓝色线条表示真实值

# 卡尔曼滤波器唯一预测值（final_prediction_kalman）也应该是常数，表示最终估计的吃水值
plt.plot([final_prediction_kalman] * len(targets), label='卡尔曼滤波器唯一预测值', color='red', linestyle='--')  # 红色虚线表示唯一预测值

plt.xlabel('样本序号')  # 或者时间戳，如果有的话
plt.ylabel('吃水深度（厘米）')
plt.title('卡尔曼滤波器唯一预测值与净水真值对比')
plt.legend()
plt.show()



# 输出最终模型评估
print(f"最终模型 - MAE: {mae_final:.4f}, RMSE: {rmse_final:.4f}, R^2: {r2_final:.4f}")
