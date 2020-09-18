//#include<iostream>
//
//using namespace std;
//
//void test1()
//{
//	char ch = 'a';
//	int i = 10;
//	double d = 3.1;
//	float f = 0.3f;
//
//	i = static_cast<int>(ch);
//	f = static_cast<float>(d);
//}
//
//int func1(int a)
//{
//	cout << "func1() " << a << endl;
//	return a;
//}
//
//void test2()
//{
//	int a = 3;
//
//	int* ptr = reinterpret_cast<int*>(a);
//	
//	// 定义一个函数指针，然后将函数 func1 强转为 pfun 类型
//	typedef void (*pfun)();
//	pfun pf = reinterpret_cast<pfun>(func1);
//	// 调用 pf() 函数
//	pf();
//	// 输出： func1() 2947892 因为没有传入参数，a 是栈上的一个随机值
//}
//
//void test3()
//{
//	
//	// const int a = 10;
//	// 加上 volatile 关键字禁止编译器的优化
//	volatile const int a = 10;
//
//	int* p = const_cast<int*>(&a);
//
//	*p = 20;
//
//	cout << "a = " << a << " *p = " << *p << endl;
//	// 输出： 
//	// const int ：a = 10 *p = 20
//	// volatile const int：a = 20 *p = 20
//}
//
//class Base
//{
//public:
//	virtual void func()
//	{
//
//	}
//};
//
//class Derived : public Base
//{
//	
//};
//
//void test4()
//{
//	Base* pb1 = new Base;
//	Base* pb2 = new Derived;
//
//	// dynamic_cast 会进行安全检查，只适用于多态
//	Derived* pd1 = dynamic_cast<Derived*>(pb2); // 转换成功
//	Derived* pd2 = dynamic_cast<Derived*>(pb1); // 转换失败，pd2 为 nullptr
//
//	// static_cast 不会进行检查s
//	Derived* pd3 = static_cast<Derived*>(pb1); // 转换成功
//}
//
//int main(void)
//{
//	test4();
//}
//
