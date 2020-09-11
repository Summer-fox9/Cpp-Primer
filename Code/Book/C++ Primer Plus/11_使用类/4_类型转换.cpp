#include<iostream>

using namespace std;

class A
{
private:
	int _a;
public:
	// 单参构造函数
	A(int a)
	{
		_a = a;
	}

	//operator int() const
	//{
	//	return _a;
	//}

	//operator double() const
	//{
	//	return double(_a);
	//}

	int A_to_int()
	{
		return _a;
	}

	double A_to_double()
	{
		return (double)_a;
	}
};

//void test1()
//{
//	// 3.1 首先转换为 int 类型，然后调用 A(3)
//	A b = 3.1;
//
//	int i = b;		// ok
//	double d = b;	// ok
//	
//	// 存在二义性：double 和 int 都可以转换为 long
//	// long l = b;
//	
//	cout << int(b) << endl;		// ok
//	cout << double(b) << endl;	// ok
//	
//	// 存在二义性：b 可以转换为 double 或 int
//	// cout << b << endl;
//}

//void test2()
//{
//	A a(3);
//
//	int a = a.A_to_int();
//	double d = a.A_to_double();
//
//	cout << a << endl; // Error!
//}

class B
{
private:
	double _b;
public:
	B(double b)
	{
		cout << "B(double b) " << endl;
		_b = b;
	}
	//operator double() const
	//{
	//	return _b;
	//}

	B operator+(const B& b)
	{
		// 第三次构造
		B ret(_b + b._b);
		return ret;
	}

	//B operator+(double d)
	//{
	//	return B(_b + d);
	//}

	double Show()
	{
		return _b;
	}

};

void test3()
{
	B b(3); 
	double d = 3.6;
	
	cout << (d + b) << endl;
}

int main(void)
{
	test3();
}