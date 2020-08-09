#include<iostream>
#include"RBTree.hpp"

using namespace std;

template<class Key, class Value>
class Map
{
public:
	struct MapKeyOfValue
	{
		const Key& operator()(const pair<Key, Value>& data)
		{
			return data.first;
		}
	};

	typedef RBTree<Key, pair<Key, Value>, MapKeyOfValue> RBType;
	typedef typename RBType::iterator iterator;


	iterator begin()
	{
		return _rbt.begin();
	}

	iterator end()
	{
		return _rbt.end();
	}

	pair<iterator, bool> insert(const pair<Key, Value>& data)
	{
		return _rbt.insert(data);
	}

	Value& operator[](const Key& key)
	{
		pair<iterator, bool> ret = _rbt.insert(make_pair(key, Value()));
		return ret.first->second;
	}

private:
	RBType _rbt;
};
