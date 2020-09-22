#ifndef STACK_H_
#define STACK_H_

template<class T>
class Stack
{
private:
	enum{NUM = 5};
	int _size;// 栈大小
	// 为 _s 分配内存是需要用到 _size，因此，_size 应该写在 _s 之前（初始化列表的顺序）
	T* _s;
	int _top;
public:
	// 单参构造函数，记得可以使用 explicit 
	explicit Stack(int size = NUM);
	Stack(const Stack<T>& s);
	Stack<T>& operator=(const Stack<T>& s);
	~Stack() { delete[] _s; };

	bool IsEmpty() const;
	bool IsFull() const;
	bool push(const T& val);
	T& top();
	bool pop();
};

template<class T>
Stack<T>::Stack(int size)
	:_top(-1)
	,_size(size)
	,_s(new T[_size])
{}

template<class T>
Stack<T>::Stack(const Stack<T>& s)
	:_top(s._top)
	,_size(s._size)
	,_s(new T[_size])
{
	for (int i = 0; i < _size; i++)
		_s[i] = s._s[i];
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
	if (this != &s)
	{
		delete[] _s;
		_top = s._top;
		_size = s._size;
		_s = new T[_size];
		for (int i = 0; i < _size; i++)
			_s[i] = s._s[i];
	}
	return *this;
}

template<class T>
bool Stack<T>::IsEmpty() const
{
	return _top == -1;
}

template<class T>
bool Stack<T>::IsFull() const
{
	return _top == _size - 1;
}

template<class T>
bool Stack<T>::push(const T& val)
{
	// 扩容
	if (IsFull())
	{
		int newSize = 2 * _size;
		T* newS = new T[newSize];
		for (int i = 0; i < _size; i++)
		{
			newS[i] = _s[i];
		}
		
		delete[] _s;
		_s = newS;

		_size = newSize;
	}

	_s[++_top] = val;
	
	return true;
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