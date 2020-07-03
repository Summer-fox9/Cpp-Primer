#pragma once

#include<iostream>
#include<cstring>

using namespace std;

template<class T>
class Vector
{
public:
	typedef T* iterator;
	typedef const T* const_iterator;

	Vector()
		:_start(nullptr)
		,_finish(nullptr)
		,_eos(nullptr)
	{}

	Vector(const Vector<T>& v) 
		:_start(new T[v.capacity()])
	{
		// 深拷贝（不懂为什么要这样可以考虑如果 T 为 string 的情况）
		for (int i = 0; i < v.size(); i++)
		{
			_start[i] = v[i];
		}
		_finish = _start + v.size();
		_eos = _start + v.capacity();
	}

	Vector<T>& operator=(const Vector<T> v)
	{
		Swap(v);
		return *this;
	}

	void Swap(Vector<T> v)
	{
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_eos, v._eos);
	}

	~Vector()
	{
		if (_start)
		{
			delete[] _start;
			_start = _finish = _eos = nullptr;
		}
	}


	iterator begin()
	{
		return _start;
	}

	const_iterator begin() const
	{
		return _start;
	}

	iterator end()
	{
		return _finish;
	}

	const_iterator end() const
	{
		return _finish;
	}

	size_t size() const 
	{
		return _finish - _start;
	}

	size_t capacity() const
	{
		return _eos - _start;
	}

	void push_back(const T& val)
	{
		// 1.判断是否需要扩容
		if (_finish == _eos)
		{
			int cap = capacity();
			int newCap = (cap == 0) ? 2 : 2 * cap;
			reserve(newCap);
		}
		// 2. 插入
		*_finish = val;
		// 3. 更新
		_finish++;
	}

	void reserve(size_t n)
	{
		if (n <= capacity())
			return;

		int oldSize = size();

		// 开空间
		T* tmp = new T[n];

		// 如果当前容器不为空，拷贝旧空间内容到新空间
		if (oldSize != 0)
		{
			// 如果 T 为 string 类，memset 的拷贝方式不能实现深拷贝。
			// memcpy(tmp, _start, sizeof(T) * oldSize);
			for (int i = 0; i < oldSize; i++)
			{
				// 调用 T 类型的赋值运算符
				tmp[i] = _start[i];
			}
		}

		//3. 释放原有空间
		delete[] _start;

		//4. 更新空间指向， 容量
		_start = tmp;
		_finish = _start + oldSize;
		_eos = _start + n;
	}

	// 如何理解 const T& val = T()
	// 如果 T 是类类型，会调用 T 的默认构造构造一个匿名对象
	// 如果 T 是内置类型，int 就初始化为 0，指针初始化为 nullptr 字符串初始化为 ""
	void resize(size_t n, const T& val = T())
	{
		if (n > capacity())
		{
			reserve(n);
		}

		if (n > size())
		{
			while (_finish != _start + n)
			{
				*_finish++ = val;
			}
		}
		else
		{
			_finish = _start + n;
		}
	}

	iterator insert(iterator pos, const T& val)
	{	
		// 插入的合法区间
		if (pos >= _start && pos <= _finish)
		{
			// 由于迭代器失效的问题，我们应该先记录插入位置
			size_t insertIdx = pos - _start;
			// 判断是否扩容
			if (_finish == _eos)
			{
				size_t newCap = (capacity() == 0) ? 1 : 2 * capacity();
				reserve(newCap);
			}
			// 更新迭代器
			pos = _start + insertIdx;
			// 移动 [pos, _finish - 1] 的元素 到 [pos + 1, _finish]
			iterator begin = _finish;
			while (begin > pos)
			{
				*begin = *(begin - 1);
				begin--;
			}
			// 插入元素
			*pos = val;
			// 更新
			_finish++;

			return pos;
		}
		else
			return _finish;
	}

	iterator erase(iterator pos)
	{
		if (pos >= _start && pos < _finish)
		{
			// 容器无元素或容器为空
			if (capacity() == 0 || size() == 0)
				return _finish;
			iterator begin = pos;
			while (begin < _finish - 1)
			{
				*(begin) = *(begin + 1);
				begin++;
			}
			_finish--;
			return pos;
		}
		else
			return _finish;
	}

	T& operator[](size_t n)
	{
		return *(_start + n);
	}

	const T& operator[](size_t n) const 
	{
		return *(_start + n);
	}

	void printVector()
	{
		for (int i = 0; i < size(); i++)
		{
			cout << *(_start + i) << " ";
		}
		cout << endl;
	}
	


private:
	T* _start;
	T* _finish;
	T* _eos; // end_of_storage
};

template<class T>
void printVector(const Vector<T>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;

	for (const auto& i : v)
	{
		cout << i << " ";
	}
	cout << endl;

	// typename 表示：原因是vector<T>本身类型就没确定，再给一个迭代器，它就不知道该给迭代器什么类型了，
	// 加上typename表示以后在确定类型，现在先不管
	typename Vector<T>::iterator it = v.begin();

	for (; it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}
