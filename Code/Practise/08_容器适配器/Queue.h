#pragma once

#include<deque>
#include<iostream>

using namespace std;

template<class T, class Container = deque<T>>
class Queue
{
private:
	Container _c;
public:
	void push(const T& val)
	{
		_c.push_back(val);
	}

	void pop()
	{
		_c.pop_front();
	}

	const T& front() const
	{
		return _c.front();
	}

	const T& back() const 
	{
		return _c.back();
	}

	size_t size() const
	{
		return _c.size();
	}

	bool empty() const
	{
		return _c.empty();
	}
};
