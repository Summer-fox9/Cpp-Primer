#pragma once
#include<iostream>
#include"RBTree.hpp"

using namespace std;

// set£∫key ∫Õ value œ‡Õ¨
template<class Key>
class Set
{
	typedef Key Value;

	struct SetKeyOfValue
	{
		const Key& operator()(const Value& data)
		{
			return data;
		}
	};

public:

	typedef RBTree<Key, Value, SetKeyOfValue> RBType;
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
private:
	RBType _rbt;
};

