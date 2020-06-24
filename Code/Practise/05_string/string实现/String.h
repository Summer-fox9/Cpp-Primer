#pragma once

#include<cstring>
#include<iostream>

using namespace std;

class String
{
public:

	typedef char* iterator;
	typedef const char* const_iterator;
  static const size_t npos;

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

    // n 大于 capacity 需要重新申请空间
		if (n > _capacity)
		{
			reserve(n);
		}
    // n 大于 _size 小于 _capacity 
		if (n > _size)
		{
			memset(_str + _size, ch, n - _size);
		}

    // 更新
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

  
  char& operator[](size_t pos)
  {
    if(pos <= _size)
    {
      return *(_str + pos);
    }
  }

  const char& operator[](size_t pos) const 
  {
    if(pos <= _size)
    {
      return *(_str + pos);
    }
  }

  String& insert(size_t pos, const char* s)
  {
    if(pos <= _size && s != nullptr)
    {
      size_t len = strlen(s);
      
      if(_size + len > _capacity)
        reserve(_size + len);

      // 移动 [pos, _size] 的元素到 [pos + len, _size + len]
      size_t end = _size + len; // '\0' 也应该移动
      
      // 因为 end 是 size_t（unsigned int） 类型，如果右式 == 0，end 再次自减不会小于 0，这样会造成无限循环
      // 解决办法就是在判断表达式中不要出现 = 号
      while(end > pos + len - 1)
      {
        _str[end] = _str[end - len];
        end--;
      }

      for(size_t i = 0; i < len; i++)
      {
        _str[pos + i] = s[i];
      }
      
      _size += len;
    }
    return *this;
  }
  

  String& insert(size_t pos, size_t n, const char& ch)
  {
    if(pos <= _size && n > 0)
    {
      if(_size + n > _capacity)
        reserve(_size + n);
      size_t end = _size + n;
      while(end > pos + n - 1)
      {
        _str[end] = _str[end - n];
        end--;
      }

      for(size_t i = 0; i < n; i++)
      {
        _str[pos + i] = ch;
      }

      _size += n;
    }
    return *this;
  }


  String& erase(size_t pos = 0, size_t len = npos)
  {
    if(pos > _size)
      return *this;

    // 删除 pos 后字符串中所有内容
    // pos 代表字符串 [0, pos - 1] 的内容
    // len 代表字符串 [pos, pos + len)
    // 直接将 pos 位置的元素置为 '\0' 即可
    // 如果缺省 len 调用 erase，len 将会是 size_t 的最大值
    // 如果此时加上 pos 就会变成一个比较小的值（看 pos 的大小
    if(pos + len >= _size || len == npos)
    {
      _str[pos] = '\0';
      _size = pos;
    }
    else
    {
      // [pos + len, _size] 移动到 [pos, ]
      size_t begin = pos + len;
      size_t cur = pos;
      while(begin < _size + 1)
      {
        _str[cur++] = _str[begin++];
      }

      _size -= len;
    }

    return *this;
  }


  String& operator+=(const String& str)
  {
    insert(_size, str._str);
    return *this;
  }

  String& operator+=(const char* str)
  {
    insert(_size, str);
    return *this;
  }

  String& append(const String& str)
  {
    insert(_size, str._str);
    return *this;
  }

  String& append(const char* str)
  {
    insert(_size, str);
    return *this;
  }

  void push_back(char ch)
  {
    insert(_size, 1, ch);
  }

  void pop_back()
  {
    if(_size != 0)
    {
      _str[--_size] = '\0';
    }
  }


  size_t find(const char* s, size_t pos = 0)
  {
    char* tar_str = strstr(_str + pos, s);

    if(tar_str)
      // 找到的字串的位置偏移等于，字串的首地址减去整个字符串的首地址（注意不要搞乱顺序）
      return tar_str - _str; 
    else 
      return npos;
  }

  void print(){
    cout << _str << " " << _size << " " << _capacity << endl;
  }



// 观察 string 类对象的成员变量，发现主要有三个
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};


const size_t String::npos = -1;

String operator+(const String& left, const String& right)
{
  String tmp(left);
  tmp += right;
  return tmp;
}

String operator+(const String& left, const char* s)
{
  String tmp(left);
  tmp += s;
  return tmp;
}

String operator+(const char* s, const String& right)
{
  String tmp(right);
  tmp += s;
  return tmp;
}

bool operator==(const String& left, const String& right)
{
  const char* sl = left.c_str();
  const char* rl = right.c_str();
  
  return strcmp(sl, rl) == 0;
  
}
bool operator>(const String& left, const String& right)
{
  const char* sl = left.c_str();
  const char* rl = right.c_str();

  return strcmp(sl, rl) > 0;
}

ostream& operator<<(ostream& _cout, const String& s)
{
  _cout << s.c_str(); 
  return _cout;
}


