#define _CRT_SECURE_NO_WARNINGS

#include<iostream>

using namespace std;

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

class Person
{
public:
	Person(const char* s)
		:_str(s)
	{
		cout << "Person(const char* s)" << endl;
	}

	Person(const Person& p)
		:_str(p._str)
	{
		cout << "Person(const Person& p)" << endl;
	}

	Person(Person&& p)
		// 将 p._str 变成右值，然后进行 _str 的移动构造
		:_str(move(p._str))
	{
		cout << "Person(Person&& p)" << endl;
	}

private:
	String2 _str;
};

Person getPerson()
{
	Person p("Shepard");

	return p;
}

void test1()
{
	int a = 10;

	// std::move 把变量的属性变为右值
	int&& ra = std::move(a);

	//cout << "============== 使用 move 前 ==============" << endl;

	// Person p(getPerson());

	/* 
	 * 输出：
	 *	String2(const char* str = )
	 *	Person(const char* s)
	 *	String2(const String& str)
	 *	Person(Person&& p)
	 * 
	 * 注意到：
	 * Person 调用的是移动拷贝构造但是 String2 调用的却不是移动拷贝构造
	 * 对于 String2 来说，并不能识别 Person._str 为将亡值
	 * 这时候就需要使用使用 move 函数将其转为右值
	 */

	cout << "============== 使用 move 后 ==============" << endl;
	
	Person p(getPerson());
	
	/*
	* ============== 使用 move 后 ==============
	*	String2(const char* str = )
	*	Person(const char* s)
	*	String2(String2&& str)
	*	Person(Person&& p)
	**/
}

void Fun(int& x) { cout << "lvalue ref" << endl; }
void Fun(int&& x) { cout << "rvalue ref" << endl; } 
void Fun(const int& x) { cout << "const lvalue ref" << endl; } 
void Fun(const int&& x) { cout << "const rvalue ref" << endl; }

// 模板参数：T&& -> 表示未定类型
template<class T>
void PerfectForward(T&& t) { Fun(std::forward<T>(t)); }

//int main() {
//	string s1("hello"); 
//	string s2(" world"); 
//	string s3 = s1 + s2; // s3是用s1和s2拼接完成之后的结果拷贝构造的新对象
//	string&& s4 = s1 + s2; // s4就是s1和s2拼接完成之后结果的别名
//	return 0; 
//}

//template<typename T>
//void PerfectForward(const T& t) { Fun(t); }

void testPerfectForward() {
	PerfectForward(10); // rvalue ref 
	int a = 1;
	PerfectForward(a); // lvalue ref 
	PerfectForward(std::move(a)); // rvalue ref 
	const int b = 8; 
	PerfectForward(b); // const lvalue ref 
	PerfectForward(std::move(b)); // const rvalue ref return 0; 
}

#include<algorithm>

void testSort()
{
	int array[] = { 9, 5, 2, 7 };

	// 默认从小到大排序
	sort(array, array + sizeof(array) / sizeof(array[0]));
	for (auto& e : array)
	{
		cout << e << " ";
	}
	cout << endl;

	// 从大到小排序需要提供一个仿函数对象
	sort(array, array + sizeof(array) / sizeof(array[0]), greater<int>());
	for (auto& e : array)
	{
		cout << e << " ";
	}
	cout << endl;
}


class A
{
private:
	int _a;
public:
	A(int a)
		:_a(a)
	{}

	// 这里需要提供 const 成员函数，因为是 const 对象调用此函数
	bool operator<(const A& ref) const 
	{
		return _a < ref._a;
	}

	bool operator>(const A& ref) const 
	{
		return _a > ref._a;
	}
};

struct LessA
{
	bool operator()(const A& a1, const A& a2)
	{
		return a1 < a2;
	}
};

struct GreaterA
{
	bool operator()(const A& a1, const A& a2)
	{
		return a1 > a2;
	}
};

void testSort2()
{
	A array[] = { {9}, {5}, {2}, {7} };

	// 自定义类型的比较需要提供仿函数对象
	// 方法 1：重载 > < 运算符
	sort(array, array + sizeof(array) / sizeof(array[0]));
	
	// 从大到小排序
	sort(array, array + sizeof(array) / sizeof(array[0]), greater<A>());

	// 方法 2：提供一个仿函数类（同样也需要重载 > < 运算符）
	sort(array, array + sizeof(array) / sizeof(array[0]), LessA());

	sort(array, array + sizeof(array) / sizeof(array[0]), GreaterA());
}

void UseLambda()
{
	A array[] = { {9}, {5}, {2}, {7} };
	
	sort(array, array + sizeof(array) / sizeof(array[0]),
		[](const A& a1, const A& a2)->bool 
		{
			return a1 < a2;
		});

	sort(array, array + sizeof(array) / sizeof(array[0]),
		[](const A& a1, const A& a2)->bool
		{
			return a1 > a2;
		});
}


void testLambda()
{
	[] {}; // 最简单的 lambda 表达式

	int a = 1, b = 2;
	
	// 使用 mutable 将参数列表给出
	[a, b]() mutable
	{
		return a + b;
	};

	// func 类型为函数指针
	auto func = [](int a, int b) ->int {a = 1; b = 2; return a + b; };
	// 可以直接使用
	func(a, b);


}

void testLambda1()
{
	int a = 1, b = 2;
	
	auto func = [=](int num)mutable->int {
		a = 10;
		b = 20;
		// c = 30; // 不能捕捉到 c
		return a + b + num;
	};
	int c = 3;
	
	func(10);
	// a, b 的值没有发生变化
}

void testLambda2()
{
	int a = 1, b = 2;

	// 不需要加 mutable 也可以修改捕捉列表中的变量
	auto func = [&](int num)->int {
		a = 10;
		b = 20;	
		return a + b + num;
	};
	int c = 3;

	func(50);
	cout << a << b << endl;
	// a, b 的值被改变
}

void testLambda3()
{
	int a = 1, b = 2;

	// [=, &a] 其他变量以值的形式捕捉，a 以引用的形式捕捉
	// [=, a] 这种写法是错误的，会造成重复
	auto func = [=, &a](int num)mutable->int {
		a = 10;
		// b = 20; // b 不能被改变
		return a + b + num;
	};

	int c = 3;
	
	func(30);
	cout << a << b << endl;
}

int global = 10;

// Error 不能显示的指明带有静态存储期限的变量
//auto _func = [global] {cout << global << endl; };

void testLambda4()
{
	int a = 1, b = 2;

	// 即使不显示指明 global ,依然自动捕捉  
	auto func = [b, &a](int num)mutable->int {
		a = 10;
		return a + b  +  num;
	};

	auto func2 = [b, &a](int num)mutable->int {
		a = 10;
		return a + b + num;
	};

	// lambda 表达式之间不能相互赋值
	// func = func2;

	auto func3 = func;
	auto func4(func);

	int d(4);

	int c = 3;

	cout << func(30) << a << b << endl;
	//_func();
}

#include<thread>


// RAII：
//      在构造函数中初始化
//		在析构函数中释放资源

class ThreadManage
{
private:
	thread& _thread;

public:
	ThreadManage(thread& t)
		:_thread(t)
	{}

	~ThreadManage()
	{
		// 如果线程还存在，则等待其结束
		if (_thread.joinable())
			_thread.join();
	}
};

void func1()
{
	cout << "func1" << endl;
}

void func2(int a)
{
	cout << "func2" << a << endl;
}

void func3()
{
	cout << "func3" << endl;
}

void testThread()
{
	thread t1(func1);
	thread t2(func2, 5);
	thread t3(func3);

	// 三个局部变量，函数结束时，自动调用其析构函数
	// 析构函数中调用 join 函数回收资源
	ThreadManage tm1(t1);
	ThreadManage tm2(t2);
	ThreadManage tm3(t3);
}

class ThreadClass
{
public:
	void func(int a)
	{
		cout << a << endl;
	}
};

void testThread2()
{
	ThreadClass tc;

	// 如果函数为成员函数，则要写完整的作用域 + this 指向的对象 + 类函数参数 
	thread t1(&ThreadClass::func, &tc, 10);
	
	t1.join();
}

void refadd(int& a)
{
	a += 10;
}

void pointeradd(int* a)
{
	*a += 10;
}

void testThread3()
{
	int a = 0;
	// 引用传参时，因为线程有自己独立的栈，所以新的线程改变不了旧的线程中的变量
	// 如果要修改， 则应该将参数的格式改为ref(a) 
	thread t(refadd, ref(a));

	t.join();
	cout << a << endl;

	// 指针类型可以直接作为参数
	thread t2(pointeradd, &a);
	t2.join();

	cout << a << endl;
}

int main(void)
{
	testThread3();

	return 0;
}