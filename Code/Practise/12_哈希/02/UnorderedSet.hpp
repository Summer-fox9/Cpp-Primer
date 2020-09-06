#pragma once
#include"HashTable.hpp"

template<class K, class HashFun>
class UnorderedSet
{
	typedef K V;

	struct SetKeyOfValue
	{
		const K& operator()(const V& val)
		{
			return val;
		}
	};
public:

	typedef typename HashTable<K, V, SetKeyOfValue, HashFun>::Iterator iterator;

	iterator begin()
	{
		return _hashTable.begin();
	}

	iterator end()
	{
		return _hashTable.end();
	}

	bool insert(const V& val)
	{
		return _hashTable.insert(val);
	}
private:
	HashTable<K, V, SetKeyOfValue, HashFun> _hashTable;
};
