#pragma once
#include <vector>
#include <string>
#include <utility>  // 引入 std::pair

//开放定址法
namespace open_address
{
    // 枚举状态，表示哈希表槽位的状态
    enum State
    {
        EMPTY,   // 空状态
        EXIST,   // 已存在数据
        DELETE   // 已删除
    };

    // 哈希表数据节点的结构体
    template<class K, class V>
    struct HashData
    {
        std::pair<K, V> _kv;  // 键值对
        State _state;         // 当前槽位的状态

        // 构造函数，初始化为 EMPTY 状态
        HashData() : _state(EMPTY) {}
    };

    template<class K>
    struct HashFunc
    {
        size_t operator()(const K& key)
        {
            return size_t(key);
        }
    };
    //模板的特化，处理string，可以采用BKDR
    template<>
    struct HashFunc<std::string>
    {
        size_t operator()(const std::string& key)
        {
            return key[0];
        }
    };
    struct StringHashFunc
    {
        size_t operator()(const std::string& key)
        {
            return key[0];
        }
    };
    // 哈希表类的定义
    template<class K, class V, class Hash = HashFunc<K>>
    class HashTable
    {
    public:
        // 构造函数，初始化哈希表大小，默认大小为10
        HashTable(size_t size = 10) : _tables(size), _n(0) {}

        // 插入方法，接受一个常量引用的键值对
        bool Insert(const std::pair<K, V>& kv)
        {
            // 检查负载因子是否超过阈值（0.7）
            if (_n * 10 / _tables.size() >= 7)
            {
                size_t newsize = _tables.size() * 2;
                HashTable<K, V, Hash> newHT(newsize);
                for (size_t i = 0; i < _tables.size(); i++)
                {
                    if (_tables[i]._state == EXIST)  // 使用比较运算符
                    {
                        newHT.Insert(_tables[i]._kv);
                    }
                }
                _tables.swap(newHT._tables);
                _n = newHT._n;
            }

            // 计算哈希值

            Hash hs;
            size_t hashi = hs(kv.first) % _tables.size();  // 使用 % 而非 %= 

            // 线性探测寻找空槽
            while (_tables[hashi]._state == EXIST)
            {
                ++hashi;
                hashi %= _tables.size();
            }

            // 插入键值对
            _tables[hashi]._kv = kv;
            _tables[hashi]._state = EXIST;
            ++_n;
            return true;
        }

        // 查找方法，返回指向 HashData 的指针
        HashData<K, V>* Find(const K& key)
        {
            Hash hs;
            size_t hashi = hs(key) % _tables.size();
            while (_tables[hashi]._state != EMPTY)
            {
                if (_tables[hashi]._state == EXIST &&
                    _tables[hashi]._kv.first == key)
                {
                    return &_tables[hashi];
                }
                ++hashi;
                hashi %= _tables.size();
            }
            return nullptr;  // 未找到时返回 nullptr
        }

        // 删除方法，根据键删除对应的键值对
        bool Erase(const K& key)
        {
            HashData<K, V>* ret = Find(key);
            if (ret == nullptr) {
                return false;
            }
            else
            {
                ret->_state = DELETE;
                --_n;
                return true;
            }
        }

    private:
        std::vector<HashData<K, V>> _tables;  // 哈希表的数据存储向量
        size_t _n;  // 哈希表中存在的元素个数
    };
    void Test2()
    {
        HashTable<std::string, int> h1;
        h1.Insert(std::make_pair("sort", 1));
    }
}

