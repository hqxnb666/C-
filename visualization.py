# visualization.py

import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.decomposition import PCA

def plot_clusters(X, labels, save_path='cluster_visualization.png'):
    pca = PCA(n_components=2)
    X_reduced = pca.fit_transform(X)
    plt.figure(figsize=(10, 6))
    sns.scatterplot(x=X_reduced[:, 0], y=X_reduced[:, 1], hue=labels, palette='Set1', legend='full')
    plt.title('Cluster Visualization with PCA')
    plt.xlabel('Principal Component 1')
    plt.ylabel('Principal Component 2')
    plt.legend(title='Cluster')
    plt.savefig(save_path)
    plt.close()  # 关闭图形，避免阻塞
    print(f"聚类可视化图已保存至 {save_path}")
