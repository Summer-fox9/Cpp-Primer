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
//	// ����һ������ָ�룬Ȼ�󽫺��� func1 ǿתΪ pfun ����
//	typedef void (*pfun)();
//	pfun pf = reinterpret_cast<pfun>(func1);
//	// ���� pf() ����
//	pf();
//	// ����� func1() 2947892 ��Ϊû�д��������a ��ջ�ϵ�һ�����ֵ
//}
//
//void test3()
//{
//	
//	// const int a = 10;
//	// ���� volatile �ؼ��ֽ�ֹ���������Ż�
//	volatile const int a = 10;
//
//	int* p = const_cast<int*>(&a);
//
//	*p = 20;
//
//	cout << "a = " << a << " *p = " << *p << endl;
//	// ����� 
//	// const int ��a = 10 *p = 20
//	// volatile const int��a = 20 *p = 20
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
//	// dynamic_cast ����а�ȫ��飬ֻ�����ڶ�̬
//	Derived* pd1 = dynamic_cast<Derived*>(pb2); // ת���ɹ�
//	Derived* pd2 = dynamic_cast<Derived*>(pb1); // ת��ʧ�ܣ�pd2 Ϊ nullptr
//
//	// static_cast ������м��s
//	Derived* pd3 = static_cast<Derived*>(pb1); // ת���ɹ�
//}
//
//int main(void)
//{
//	test4();
//}
//
