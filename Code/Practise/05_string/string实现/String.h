#pragma once

#pragma warning(disable : 4996)

#include<cstring>
#include<iostream>



using namespace std;

class String
{
public:
	// 无参构造
	String()
		:_str(new char[16])
		, _size(0)
		, _capacity(0)
	{
		_str[_size] = '\0';
		// 注意：_size 和 _capacity 的大小不包含结尾的终止字符
		_capacity = 15;
	}

	// c 风格字符串构造
	String(const char* s)
	{
		_size = strlen(s);
		_capacity = _size;
		_str = new char[_capacity];
		strcpy(_str, s);
	}


	/*拷贝构造
   String(const String& str)
	   :_str(new char[str._capacity + 1])
	   ,_size(str._size)
	   ,_capacity(str._capacity)
   {
	   strcpy(_str, str._str);
   }*/

   // 拷贝构造现代写法，利于代码复用
	String(const String& str)
		:_str(nullptr)
		// 一定要初始化为空，因为交换后 tmp._str 指向本来 this->_str 指向的空间
		// 如果 this->_str 没有初始化，临时变量 tmp 被释放时，会调用析构释放 tmp._str
		// 也就是本来的（this->_str） 指向的空间，而这个空间是随机的，因此会引发未定义行为
	{
		// 调用 c 风格构造函数
		String tmp(str._str);
		Swap(tmp);
		// 如果调用内置的 swap(*this, tmp) 传入两个引用，
		// 会申请一个临时的 String 类型的变量，然后还会有两次类类型间的赋值，比较低效

	}

	void Swap(String& tmp)
	{
		swap(_str, tmp._str);
		swap(_size, tmp._size);
		swap(_capacity, tmp._capacity);
	}
	//void Swap(String& str)
	//{
	//	//拷贝构造
	//	String tmp = str;
	//	//赋值运算符
	//	str = *this;
	//	//赋值运算符
	//	*this = tmp;
	//}

	// 赋值运算符重载函数
	// 参数值传递，这样参数改变不影响本来的值
	String& operator=(String str)
	{
		Swap(str);
		// 不需要调用拷贝构造，因为实参传给形参时就是拷贝构造
		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
		}
	}


	const char* c_str() const
	{
		return _str;
	}

	typedef char* iterator;
	typedef const char* const_iterator;

	iterator begin()
	{
		return _str;
	}

	iterator end()
	{
		return _str + _size;
	}

	const_iterator cbegin() const
	{
		return _str;
	}

	const_iterator cend() const
	{
		return _str + _size;
	}

	size_t size() const
	{
		return _size;
	}

	void resize(size_t n, char ch = '\0')
	{
		if (n == _size)
			return;

		if (n > _capacity)
		{
			reserve(n);
		}
		if (n > _size)
		{
			memset(_str + _size, ch, n - _size);
		}

		_size = n;
		_str[_size] = '\0';
	}

	void reserve(size_t n = 0)
	{
		if (n <= _capacity)
			return;
		
		// 开新空间
		char* tmp = new char[n + 1];
		// 挪旧内容
		strcpy(tmp, _str);
		// 释放旧空间
		delete[] _str;
		
		// 更新
		_str = tmp;
		_capacity = n;
	}



// 观察 string 类对象的成员变量，发现主要有三个
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};
