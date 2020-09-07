#include"HashTable.hpp"

template<class K, class V, class HashFun = KeyIsInt<int>>
class UnorderedMap
{
	// 私有，尽在此类中使用
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& val)
		{
			return val.first;
		}
	};
public:
	// 这里一定要加上 typename
	typedef typename HashTable<K, pair<K, V>, MapKeyOfValue, HashFun>::Iterator iterator;

	pair<iterator, bool> insert(const pair<K, V>& val)
	{
		return _hashTable.insert(val);
	}

	V& operator[](const K& key)
	{
		// 首先尝试插入
		pair<iterator, bool> ret = _hashTable.insert(make_pair(key, V()));
		
		// ->second 相当于 &_node->_value->second
		return ret.first->second;
	}
	
	iterator begin()
	{
		return _hashTable.begin();
	}

	iterator end()
	{
		return _hashTable.end();
	}

private:
	HashTable<K, pair<K, V>, MapKeyOfValue, HashFun> _hashTable;
};

