#pragma once
#include <vector>
#include <string>
#include <utility>  

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
   
    template<class K, class V, class Hash = HashFunc<K>>
    class HashTable
    {
    public:
      
        HashTable(size_t size = 10) : _tables(size), _n(0) {}

        bool Insert(const std::pair<K, V>& kv)
        {
            // 检查负载因子是否超过阈值（0.7）
            if (_n * 10 / _tables.size() >= 7)
            {
                size_t newsize = _tables.size() * 2;
                HashTable<K, V, Hash> newHT(newsize);
                for (size_t i = 0; i < _tables.size(); i++)
                {
                    if (_tables[i]._state == EXIST)  
                    {
                        newHT.Insert(_tables[i]._kv);
                    }
                }
                _tables.swap(newHT._tables);
                _n = newHT._n;
            }

            // 计算哈希值

            Hash hs;
            size_t hashi = hs(kv.first) % _tables.size(); 

            // 线性探测寻找空槽
            while (_tables[hashi]._state == EXIST)
            {
                ++hashi;
                hashi %= _tables.size();
            }

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

namespace hash_bucket
{
    template<class T>
    struct HashNode
    {
        T _data;
        HashNode<T>* _next;
        HashNode()
            :_next(nullptr)
            
        {}
        HashNode(const T& data)
            : _data(data), _next(nullptr)
        {}
    };
    
    template<class K, class T, class KeyOfT, class Hash >
    class HashTable;
    template<class K, class T, class KeyOfT, class Hash >
    class __HTIterator
    {
    public:
        typedef HashNode<T> Node;
        typedef __HTIterator<K, T, KeyOfT, Hash> Self;
        Node* _node;
        HashTable<K, T, KeyOfT, Hash>* _pht;
        __HTIterator(Node* node, HashTable<K, T, KeyOfT, Hash>* pht)
            :_node(node),
            _pht(pht)
        {}

        Self& operator++()
        {
            if (_node->_next)
            {
                _node = _node->_next;
            }
            else
            {
                KeyOfT kot;
                Hash hs;
                size_t i = hs(kot(_node->_data)) % _pht->_tables.size();
                ++i;
                for ( ; i < _pht->_tables.size(); i++)
                {
                    if (_pht->_tables[i]) {
                        break;
                    }
                }
                if (i == _pht->_tables.size())
                {
                    _node = nullptr;
                }
                else
                {
                    _node = _pht->_tables[i];
                }
                
            }
            return *this;
        }
        T& operator* ()
        {
            return _node->_data;
        }
        T* operator->()
        {
            return &(_node->_data);
        }
        bool operator!=(const Self& s)
        {
            return _node != s._node;
        }

    };
    template<class K, class T, class KeyOfT,class Hash >
    class HashTable
    {
    public:
        typedef __HTIterator<K, T, KeyOfT, Hash> iterator;
        typedef HashNode<T> Node;
        friend class __HTIterator<K, T, KeyOfT, Hash>;
        iterator begin()
        {
            for (size_t i = 0; i < _tables.size(); i++)
            {
                Node* cur = _tables[i];
               
                if (cur)
                {
                    return iterator(cur, this);
                }
            }
            return end();
        }
        iterator end()
        {
            return iterator(nullptr, this);
        }
        HashTable(size_t size = 10)
            :_tables(size,nullptr),
            _n(0)
        {}
        ~HashTable()
        {
            for (size_t i = 0; i < _tables.size(); i++)
            {
                Node* cur = _tables[i];
                while (cur)
                {
                    Node* tmp = cur;
                    cur = cur->_next;
                    delete tmp;
                }
                _tables[i] = nullptr;
            }
        }
        std::pair<iterator,bool> Insert(const T& data)
        {
            KeyOfT kot;
            iterator it = Find(kot(data));
            if (it != end()) {
                return std::make_pair(it,false);
            }
            Hash hs;
            //扩容,负载因子为1
            if (_n == _tables.size())
            {
                /*size_t newsize = _tables.size() * 2;
                    HashTable<K, V> newHT(newsize) ;
                for (size_t i = 0; i < _tables.size(); i++)
                {
                    Node* cur = _tables[i];
                    while (cur)
                    {
                        newHT.Insert(cur->_kv);
                        cur = cur->_next;
                    }
                }
                _tables.swap(newHT._tables);*/

                //上述方法如果每次一开辟新哈希表时，就要走n个析构，很耗时，所以我们采取直接把对应的数字算出来
                //然后手动插入，到时候析构走vector析构，

                std::vector<Node*> newTables(_tables.size() * 2, nullptr);
                for (size_t i = 0; i < _tables.size(); i++)
                {
                    Node* cur = _tables[i];
                    while (cur)
                    {
                        Node* tmp = cur;
                        cur = cur->_next;
                        size_t hashi = hs(kot(tmp->_data)) % newTables.size();
                        tmp->_next = newTables[hashi];
                      newTables[hashi] = tmp ;
                    }
                    _tables[i] = nullptr;
                }
                _tables.swap(newTables);
            }

            size_t hashi = hs(kot(data)) % _tables.size();
            Node* newnode = new Node(data);
            newnode->_next = _tables[hashi];
            _tables[hashi] = newnode;
            ++_n;
            return std::make_pair(iterator(newnode,this),true);
        }
        bool Erase(const K& key)
        {
            KeyOfT kot;
            Hash hs;
            size_t hashi = hs(key) % _tables.size();
            Node* prev = nullptr;
            Node* cur = _tables[hashi];
            while (cur)
            {
                if (kot(cur->_data) == key)
                {
                    if (prev == nullptr)
                    {
                        _tables[hashi] = cur->_next;
                    }
                    else
                    {
                        prev->_next = cur->_next;
                    }
                    delete cur;
                    return true;
                }
                else
                {
                    prev = cur;
                    cur = cur->_next;
                }

            }
            return false;
        }
        iterator Find(const K& key)
        {
            KeyOfT kot;
            Hash hs;
            size_t hashi = hs(key) % _tables.size();
            Node* cur = _tables[hashi];
            while (cur)
            {
                if (kot(cur->_data) == key)
                {
                    return iterator(cur, this);
                }
                cur = cur->_next;
                
            }
            return end() ;
        }
    private:
        std::vector<Node*> _tables;
        size_t _n;
    };

}