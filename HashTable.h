#pragma once
#include <vector>
#include <string>
#include <utility>  // ���� std::pair

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
    // ��ϣ����Ķ���
    template<class K, class V, class Hash = HashFunc<K>>
    class HashTable
    {
    public:
        // ���캯������ʼ����ϣ���С��Ĭ�ϴ�СΪ10
        HashTable(size_t size = 10) : _tables(size), _n(0) {}

        // ���뷽��������һ���������õļ�ֵ��
        bool Insert(const std::pair<K, V>& kv)
        {
            // ��鸺�������Ƿ񳬹���ֵ��0.7��
            if (_n * 10 / _tables.size() >= 7)
            {
                size_t newsize = _tables.size() * 2;
                HashTable<K, V, Hash> newHT(newsize);
                for (size_t i = 0; i < _tables.size(); i++)
                {
                    if (_tables[i]._state == EXIST)  // ʹ�ñȽ������
                    {
                        newHT.Insert(_tables[i]._kv);
                    }
                }
                _tables.swap(newHT._tables);
                _n = newHT._n;
            }

            // �����ϣֵ

            Hash hs;
            size_t hashi = hs(kv.first) % _tables.size();  // ʹ�� % ���� %= 

            // ����̽��Ѱ�ҿղ�
            while (_tables[hashi]._state == EXIST)
            {
                ++hashi;
                hashi %= _tables.size();
            }

            // �����ֵ��
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

