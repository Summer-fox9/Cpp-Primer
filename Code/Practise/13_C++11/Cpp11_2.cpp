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

	// �ƶ�����
	// ��ֵ����ֻ��ƥ����ֵ
	String2(String2&& str)
		: _str(str._str) // �� str ����Դ�� _str
		, _size(str._size)
	{
		str._str = nullptr; // str ����Դ���� _str ����
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

	// �ƶ���ֵ
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
		// �� p._str �����ֵ��Ȼ����� _str ���ƶ�����
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

	// std::move �ѱ��������Ա�Ϊ��ֵ
	int&& ra = std::move(a);

	//cout << "============== ʹ�� move ǰ ==============" << endl;

	// Person p(getPerson());

	/* 
	 * �����
	 *	String2(const char* str = )
	 *	Person(const char* s)
	 *	String2(const String& str)
	 *	Person(Person&& p)
	 * 
	 * ע�⵽��
	 * Person ���õ����ƶ��������쵫�� String2 ���õ�ȴ�����ƶ���������
	 * ���� String2 ��˵��������ʶ�� Person._str Ϊ����ֵ
	 * ��ʱ�����Ҫʹ��ʹ�� move ��������תΪ��ֵ
	 */

	cout << "============== ʹ�� move �� ==============" << endl;
	
	Person p(getPerson());
	
	/*
	* ============== ʹ�� move �� ==============
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

// ģ�������T&& -> ��ʾδ������
template<class T>
void PerfectForward(T&& t) { Fun(std::forward<T>(t)); }

//int main() {
//	string s1("hello"); 
//	string s2(" world"); 
//	string s3 = s1 + s2; // s3����s1��s2ƴ�����֮��Ľ������������¶���
//	string&& s4 = s1 + s2; // s4����s1��s2ƴ�����֮�����ı���
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

	// Ĭ�ϴ�С��������
	sort(array, array + sizeof(array) / sizeof(array[0]));
	for (auto& e : array)
	{
		cout << e << " ";
	}
	cout << endl;

	// �Ӵ�С������Ҫ�ṩһ���º�������
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

	// ������Ҫ�ṩ const ��Ա��������Ϊ�� const ������ô˺���
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

	// �Զ������͵ıȽ���Ҫ�ṩ�º�������
	// ���� 1������ > < �����
	sort(array, array + sizeof(array) / sizeof(array[0]));
	
	// �Ӵ�С����
	sort(array, array + sizeof(array) / sizeof(array[0]), greater<A>());

	// ���� 2���ṩһ���º����ࣨͬ��Ҳ��Ҫ���� > < �������
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
	[] {}; // ��򵥵� lambda ���ʽ

	int a = 1, b = 2;
	
	// ʹ�� mutable �������б����
	[a, b]() mutable
	{
		return a + b;
	};

	// func ����Ϊ����ָ��
	auto func = [](int a, int b) ->int {a = 1; b = 2; return a + b; };
	// ����ֱ��ʹ��
	func(a, b);


}

void testLambda1()
{
	int a = 1, b = 2;
	
	auto func = [=](int num)mutable->int {
		a = 10;
		b = 20;
		// c = 30; // ���ܲ�׽�� c
		return a + b + num;
	};
	int c = 3;
	
	func(10);
	// a, b ��ֵû�з����仯
}

void testLambda2()
{
	int a = 1, b = 2;

	// ����Ҫ�� mutable Ҳ�����޸Ĳ�׽�б��еı���
	auto func = [&](int num)->int {
		a = 10;
		b = 20;	
		return a + b + num;
	};
	int c = 3;

	func(50);
	cout << a << b << endl;
	// a, b ��ֵ���ı�
}

void testLambda3()
{
	int a = 1, b = 2;

	// [=, &a] ����������ֵ����ʽ��׽��a �����õ���ʽ��׽
	// [=, a] ����д���Ǵ���ģ�������ظ�
	auto func = [=, &a](int num)mutable->int {
		a = 10;
		// b = 20; // b ���ܱ��ı�
		return a + b + num;
	};

	int c = 3;
	
	func(30);
	cout << a << b << endl;
}

int global = 10;

// Error ������ʾ��ָ�����о�̬�洢���޵ı���
//auto _func = [global] {cout << global << endl; };

void testLambda4()
{
	int a = 1, b = 2;

	// ��ʹ����ʾָ�� global ,��Ȼ�Զ���׽  
	auto func = [b, &a](int num)mutable->int {
		a = 10;
		return a + b  +  num;
	};

	auto func2 = [b, &a](int num)mutable->int {
		a = 10;
		return a + b + num;
	};

	// lambda ���ʽ֮�䲻���໥��ֵ
	// func = func2;

	auto func3 = func;
	auto func4(func);

	int d(4);

	int c = 3;

	cout << func(30) << a << b << endl;
	//_func();
}

#include<thread>


// RAII��
//      �ڹ��캯���г�ʼ��
//		�������������ͷ���Դ

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
		// ����̻߳����ڣ���ȴ������
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

	// �����ֲ���������������ʱ���Զ���������������
	// ���������е��� join ����������Դ
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

	// �������Ϊ��Ա��������Ҫд������������ + this ָ��Ķ��� + �ຯ������ 
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
	// ���ô���ʱ����Ϊ�߳����Լ�������ջ�������µ��̸߳ı䲻�˾ɵ��߳��еı���
	// ���Ҫ�޸ģ� ��Ӧ�ý������ĸ�ʽ��Ϊref(a) 
	thread t(refadd, ref(a));

	t.join();
	cout << a << endl;

	// ָ�����Ϳ���ֱ����Ϊ����
	thread t2(pointeradd, &a);
	t2.join();

	cout << a << endl;
}

int main(void)
{
	testThread3();

	return 0;
}