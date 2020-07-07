#pragma once

#include<vector>
#include<iostream>

using namespace std;

template<class T>
struct Less
{
	bool operator()(const T& t1, const T& t2)
	{
		return t1 < t2;
	}
};

template<class T>
struct Greater
{
	bool operator()(const T& t1, const T& t2)
	{
		return t1 > t2;
	}
};

template<class T, class Container = vector<T>, class Compare = Less<T>>
class Priority_Queue
{
public:
	void push(const T& val)
	{
		_c.push_back(val);
		shiftUp(_c.size() - 1);
	}

	void pop()
	{
		swap(_c[0], _c[_c.size() - 1]);
		_c.pop_back();
		shiftDown(0);
	}

	const T& top() const
	{
		return _c.front();
	}

	size_t size() const
	{
		return _c.size();
	}

	bool empty() const
	{
		return _c.empty();
	}

private:
	Container _c;
	Compare _cmp;

	void shiftDown(int parent)
	{
		// ×ó¶ù×Ó
		int child = 2 * parent + 1;
		while (child < _c.size())
		{
			if (child + 1 < _c.size() && _cmp(_c[child], _c[child + 1]))
				child++;
			if (_cmp(_c[parent], _c[child]))
			{
				swap(_c[parent], _c[child]);
				parent = child;
				child = parent * 2 + 1;
			}
			else
				break;
		}
	}

	void shiftUp(int child)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_cmp(_c[parent], _c[child]))
			{
				swap(_c[parent], _c[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}
};
