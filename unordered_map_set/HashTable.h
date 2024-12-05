#pragma once
#include <vector>
#include <string>
#include <utility>  

//���Ŷ�ַ��
namespace open_address
{
    // ö��״̬����ʾ��ϣ���λ��״̬
    enum State
    {
        EMPTY,   // ��״̬
        EXIST,   // �Ѵ�������
        DELETE   // ��ɾ��
    };

    // ��ϣ�����ݽڵ�Ľṹ��
    template<class K, class V>
    struct HashData
    {
        std::pair<K, V> _kv;  // ��ֵ��
        State _state;         // ��ǰ��λ��״̬

        // ���캯������ʼ��Ϊ EMPTY ״̬
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
    //ģ����ػ�������string�����Բ���BKDR
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
            // ��鸺�������Ƿ񳬹���ֵ��0.7��
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

            // �����ϣֵ

            Hash hs;
            size_t hashi = hs(kv.first) % _tables.size(); 

            // ����̽��Ѱ�ҿղ�
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

        // ���ҷ���������ָ�� HashData ��ָ��
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
            return nullptr;  // δ�ҵ�ʱ���� nullptr
        }

        // ɾ�����������ݼ�ɾ����Ӧ�ļ�ֵ��
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
        std::vector<HashData<K, V>> _tables;  // ��ϣ������ݴ洢����
        size_t _n;  // ��ϣ���д��ڵ�Ԫ�ظ���
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
            //����,��������Ϊ1
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

                //�����������ÿ��һ�����¹�ϣ��ʱ����Ҫ��n���������ܺ�ʱ���������ǲ�ȡֱ�ӰѶ�Ӧ�����������
                //Ȼ���ֶ����룬��ʱ��������vector������

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