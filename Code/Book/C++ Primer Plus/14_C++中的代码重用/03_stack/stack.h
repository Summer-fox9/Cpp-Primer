#ifndef STACK_H_
#define STACK_H_

template<class T>
class Stack
{
private:
	enum{NUM = 10};
	T _s[NUM];
	int _top;
public:
	Stack()
		:_top(-1)
	{}

	bool IsEmpty() const;
	bool IsFull() const;
	bool push(T&& val);
	bool push(const T& val);
	T& top();
	bool pop();
};

template<class T>
bool Stack<T>::IsEmpty() const
{
	return _top == -1;
}

template<class T>
bool Stack<T>::IsFull() const
{
	return _top == NUM - 1;
}

template<class T>
bool Stack<T>::push(const T& val)
{
	if (!IsFull())
	{
		_s[++_top] = val;
		return true;
	}
	return false;
}

template<class T>
bool Stack<T>::push(T&& val)
{
	if (!IsFull())
	{
		_s[++_top] = val;
		return true;
	}
	return false;
}

template<class T>
T& Stack<T>::top()
{
	return _s[_top];
}

template<class T>
bool Stack<T>::pop()
{
	if (!IsEmpty())
	{
		--_top;
		return true;
	}
	return false;
}

#endif 