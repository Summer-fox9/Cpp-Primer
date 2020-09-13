#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<iostream>
#include<map>

using namespace std;

class A
{
public:
	// A() = default;
	A()
	{
		cout << "A()" << endl;
	}

	// A(const A& a) = default;
	A(const A& a) 
	{
		cout << "A(const A& a)" << endl;
	}

	A(int a, int b)
		:_a(a)
		,_b(b)
	{}

	A(int a)
		:_a(a)
		, _b(0)
	{}
private:
	int _a;
	int _b;
};

template<class T>
class Vector
{
public:
	Vector(size_t n)
		:_array(new T[n])
		,_size(0)
		,_capacity(n)
	{}

	Vector(const initializer_list<T>& ilst)
		:_array(new T[ilst.size()])
		,_size(0)
		,_capacity(ilst.size())
	{
		for (const auto& e : ilst)
		{
			_array[_size++] = e;
		}
	}

private:
	T* _array;
	size_t _size;
	size_t _capacity;
};

// C++ 11 支持 内置类型和自定义类型 的列表初始化
void test1()
{
	// 两种形式
	vector<int> v1 = { 1, 2, 3 };
	vector<int> v2{ 1, 2, 3 };

	int i1 = { 1 };
	int i2{ 1 };

	pair<int, int> p = { 1, 1 };
	map<int, int> m = { {1, 1}, {2, 2}, };

	// 下面这两种意思是等价的
	A a1{ 1, 2 };
	A a2(1, 2);

	// 单参构造函数的隐式类型转换
	// 5 先构造成匿名对象，然后 a3 调用拷贝构造函数
	A a3 = 5; 

	// 需要注意的是，自己实现的序列式容器（比如你自己实现一个 vector）是无法天然支持列表初始化的
	// 需要提供参数为 initializer_list 的构造函数
	Vector<int> V{ 1, 2, 3, 4, 5 };
	
}

int func()
{
	return 1;
}

// 类型推导
void test2()
{
	// auto 编译时根据初始化表达式进行类型推导
	map<string, string> m;
	auto it = m.begin();

	// decltype 运行时类型推导
	decltype(2 - 1) d1;

	// 根据函数返回值推导类型
	decltype(func()) d2;

	// 函数有参数，推导函数返回值类型
	cout << "d2 type: " << typeid(d2).name() << endl; // int 

	// 函数没有参数，推导函数的接口类型
	cout << "d2 type: " << typeid(decltype(func)).name() << endl;  // int __cdecl(void)
}

class B
{
public:

	//`default`：让编译器显示生成一个默认函数

	//`delete`：把一个函数声明成删除函数，不能再被使用
	B() = default;

	B(const B& b) = delete; // 防拷贝

	B& operator=(const B& b) = delete;
};

void test3()
{
	/* 左值：可以放在 = 左侧，可以取地址
	 * 右值：不能放在 = 左侧，不能取地址
	 * 
	 * 常量，临时变量，匿名变量都是右值
	 */

	/*
	 * 左值引用：既可以引用左值，也可以引用右值
	 */
	
	int a = 3;

	int& ra = a;
	// 左值引用可以引用右值，需要加上 const
	const int& rc = 10;

	/*
	 * 右值引用：只能引用右值
	 */

	int&& r1 = 10;
	// int&& r2 = a;
	
	// 匿名对象的引用
	A&& a1 = A();

	const A& a2 = A();

}

void test4()
{
	A&& a1 = A();

	const A& a2 = A();

	/*
	 * 输出：
	 * A()
	 * A()
	 * 说明编译器进行了优化，只调用了 a1，a2 的构造函数
	 * 如果没有进行优化，编译器应该调用的是：构造函数 + 拷贝构造
	 */
}

class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
		,_size(strlen(str))
	{
		strcpy(_str, str);
		cout << "String(const char* str = "")" << endl;
	}

	String(const String& str)
		: _str(new char[strlen(str._str) + 1])
		, _size(str._size)
	{
		strcpy(_str, str._str);
		cout << "String(const String& str)" << endl;
	}
	

	~String()
	{
		if (_str)
		{
			delete[] _str;
		}
	}
private:
	char* _str;
	int _size;
};

String getStr(const char* s)
{
	String str(s);
	return str;
}

void test5()
{
	String str = getStr("Shepard");

	/*
	 * 输出： 
	 *  String(const char* str = )
	 *	String(const String& str)
	 * 
	 * 说明：
	 * 走了 getStr() 中 str 的构造函数 和 test5() 中 str 的拷贝构造
	 * getStr() 中返回的 str 是一个将亡值，是一个右值。
	 * 编译器进行了优化，没有构造返回的临时变量
	 * 
	 * 问题：
	 * 尽管编译器进行了优化，这仍然存在一个问题：
	 * getStr 中返回的 str 并没有真正使用，它的存在只是为了构造 test5 中的 str 对象
	 * 那么先为其开资源，然后再删除似乎是没有什么意义的
	 */
}

class String2
{
public:
	String2(const char* str = "")
		:_str(new char[strlen(str) + 1])
		, _size(strlen(str))
	{
		strcpy(_str, str);
		cout << "String2(const char* str = "")" << endl;
	}

	String2(const String2& str)
		: _str(new char[strlen(str._str) + 1])
		, _size(str._size)
	{
		strcpy(_str, str._str);
		cout << "String2(const String& str)" << endl;
	}

	// 移动构造
	// 右值引用只能匹配右值
	String2(String2&& str)
		: _str(str._str) // 将 str 的资源给 _str
		, _size(str._size)
	{
		str._str = nullptr; // str 的资源将由 _str 清理
		cout << "String2(String2&& str)" << endl;
	}

	~String2()
	{
		if (_str)
		{
			delete[] _str;
		}
	}

	String2& operator=(const String2& str)
	{
		if (&str != this)
		{
			delete[] _str;
			_str = new char[strlen(str._str) + 1];
			_size = str._size;
			strcpy(_str, str._str);
		}

		cout << "String2& operator=(const String2& str)" << endl;
		return *this;
	}

	// 移动赋值
	String2& operator=(String2&& str)
	{
		if (&str != this)
		{
			swap(str._str, _str);
			_size = str._size;
		}
		cout << "String2& operator=(String2&& str)" << endl;
		return *this;
	}


private:
	char* _str;
	int _size;
};

String2 getStr2(const char* s)
{
	String2 str(s);
	return str;
}

void test6()
{
	String2 str = getStr2("Shepard");

	/*
	 * 输出：
	 * String2(const char* str = )
	 * String2(String2&& str)
	 * 
	 * 说明：
	 * 在构造 test6 中的 str 时，调用的是 String2 的参数为右值引用拷贝构造函数
	 * 
	 * 这个拷贝构造函数的功能：
	 * 它直接将右值（将亡值）的资源给了 test6 中的 str，从而避免了test6 中的 str 再次
	 * 申请资源，进而提高了效率
	 */

	// 调用深拷贝构造，因为 str 并不是“没有用”的值
	String2 str2(str);

	/*
	 * String2("Wang") 是一个临时的匿名对象，它的生命周期只有 1 行
	 * 所以如果用其拷贝构造 str3 ，将调用 移动构造
	 * 但是这里编译器会做优化，所以调用的是 str3 的拷贝构造
	 */
	String2 str3 = String2("Wang");

	cout << "============ 赋值运算符重载函数1 ============" << endl;

	// 创建了一个匿名对象来给 str3 赋值。一共创建 3 个对象
	str3 = getStr2("CET-6");

	cout << "============ 赋值运算符重载函数2 ============" << endl;
	
	// 直接用将亡对象给 str3 赋值
	str3 = String2("CET-4");

	/*
	 * 输出：
	 *
	 * ============ 赋值运算符重载函数1 ============
	 *	String2(const char* str = )
	 * 	String2(String2&& str)
	 *	String2& operator=(String2&& str)
	 *	============ 赋值运算符重载函数2 ============
	 *	String2(const char* str = )
	 *	String2& operator=(String2&& str) 
	 */
}

//int main(void)
//{
//	test6();
//}