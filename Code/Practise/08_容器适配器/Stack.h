#pragma once

#include<deque>
#include<iostream>

using namespace std;

template<class T, class Container = deque<T>>
class Stack
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
		_c.pop_back();
	}

	T& top() 
	{
		return _c.back();
	}

	const T& top() const
	{
		return _c.back();
	}

	bool empty() const
	{
		return _c.empty();
	}

	size_t size() const
	{
		return _c.size();
	}


};
