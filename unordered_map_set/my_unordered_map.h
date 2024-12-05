#pragma once
#include "HashTable.h"
namespace bit
{
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
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
	public:

		struct MapKeyOfT
		{
			const K& operator()(const std::pair<K, V>& kv)
			{
				return kv.first;
			}
		};
		typedef typename hash_bucket::HashTable<K,  std::pair<const K, V>, MapKeyOfT, Hash>::iterator iterator;
		std::pair<iterator, bool> insert(const std::pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}
		iterator begin()
		{
			return _ht.begin();
		}
		const V& operator[](const K& key)
		{
			std::pair<iterator, bool> ret = insert(std::make_pair(key, V()));
			return ret.first->second;
		}
		iterator end()
		{
			return _ht.end();
		}
	private:
		hash_bucket::HashTable<K, std::pair<const K, V>,MapKeyOfT,Hash> _ht;
	};
}