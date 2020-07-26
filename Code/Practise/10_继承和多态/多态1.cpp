//#include<iostream>
//
//using namespace std;
//
//class Person
//{
//public:
//	virtual void print()
//	{
//		cout << "人类：" << "age = " << _age << " name =  " << _name << " " << _test << endl;
//	}
//
//protected:
//	int _age = 20;
//	string _name = "Shepard";
//
//private:
//	int _test = 1;
//};
//
//class Student : public Person
//{
//	virtual void print()
//	{
//		cout << "学生：" << "age = " << _age << " name =  " << _name << " " <<  endl;
//	}
//};
//
//void print(Person& p)
//{
//	p.print();
//}
//
///**
// *	多态条件：
// *		1.继承
// *		2.子类重写虚函数
// *		3.调用虚函数的类型必须是 指针/引用，父类 指针/引用 指向子类对象（切片）
// */
//void test1()
//{
//	Person p;
//	Student s;
//
//	print(p);
//	print(s);
//}
//
///**
// *	重写父类虚函数规则：函数返回值，参数个数和类型完全一致
// *	例外：1.协变函数重写 2.析构函数重写
// *	
// *	如果子类虚函数重写不合规范，会造成函数隐藏
// *	子类不写 virtual 关键字也可以构成重写
// */
//
//// 1. 协变：返回值可以不同，但必须是构成 父子关系 的指针/引用
//class A
//{
//public:
//	int _a;
//};
//
//class B : public A
//{
//
//};
//
//class Person2
//{
//public:
//	// 返回引用 ok
//	//virtual A& print()
//	//{
//	//	cout << "人类：" << "age = " << _age << " name =  " << _name << " " << _test << endl;
//	//	A a;
//	//	return a; 
//	//}
//	
//	// 返回指针 ok
//	//virtual A* print()
//	//{
//	//	cout << "人类：" << "age = " << _age << " name =  " << _name << " " << _test << endl;
//	//	A a;
//	//	return &a;
//	//}
//
//	// 注意父类父类返回父类（Person2 的 print 返回 A），子类返回子类
//	// 要么都返回引用，要么都返回指针，但是不能返回一个普通变量
//
//protected:
//	int _age = 20;
//	string _name = "Shepard";
//
//private:
//	int _test = 1;
//};
//
//class Student2 : public Person2
//{
//	//virtual B& print()
//	//{
//	//	cout << "学生：" << "age = " << _age << " name =  " << _name << " " << endl;
//	//	B b;
//	//	return b;
//	//}
//
//	virtual B* print()
//	{
//		cout << "学生：" << "age = " << _age << " name =  " << _name << " " << endl;
//		B b;
//		return &b;
//	}
//
//};
//void test2()
//{
//	Person2 p;
//	Student2 s;
//}
//
//// 2. 析构函数
//class Person3
//{
//public:
//	Person3()
//	{
//		cout << "Person3()" << endl;
//	}
//
//	void print()
//	{
//		cout << "人类：" << "age = " << _age << " name =  " << _name << " " << _test << endl;
//	}
//
//	//~Person3()
//	//{
//	//	cout << "~Person3()" << endl;
//	//}
//
//	virtual ~Person3()
//	{
//		cout << "~Person3()" << endl;
//	}
//
//protected:
//	int _age = 20;
//	string _name = "Shepard";
//
//private:
//	int _test = 1;
//};
//
//class Student3 : public Person3
//{
//public:
//	Student3()
//	{
//		cout << "Student3()" << endl;
//	}
//
//	void print()
//	{
//		cout << "学生：" << "age = " << _age << " name =  " << _name << " " << endl;
//	}
//
//	//~Student3()
//	//{
//	//	cout << "~Student3()" << endl;
//	//}
//
//	virtual ~Student3()
//	{
//		cout << "~Student3()" << endl;
//	}
//};
//
//void test3()
//{
//	Person3* p = new Person3;
//	Student3* s = new Student3;
//
//	delete p;
//	delete s;
//	
//	/*
//	构造三次，析构三次
//	 Person3()
//	 Person3()
//	 Student3()
//	 ~Person3()
//	 ~Student3()
//	 ~Person3()
//	*/
//	
//	Person3* p2 = new Person3;
//	Person3* s2 = new Student3;
//
//	delete p2;
//	delete s2;
//	/*
//	构造三次，只析构了两次
//	Person3()
//	Person3()
//	Student3()
//	~Person3()
//	~Person3()
//	*/
//
//	// 这是因为 s2 指针是 Person3 类型，delete 时会调用 Person3 的析构，而不是调用 Student3 的析构
//	// 这时候我们就需要用虚函数重写父类析构，完成多态
//}
//
//class AA
//{
//public:
//	 virtual void print()
//	{
//		cout << "A" << endl;
//	}
//};
//
//class BB : public AA
//{
//public:
//	void print()
//	{
//		cout << "B" << endl;
//	}
//};
//
//class CC : public BB
//{
//public:
//	void print()
//	{
//		cout << "C" << endl;
//	}
//};
//
//void print(AA& r)
//{
//	r.print();
//}
//
//void print2(BB& r)
//{
//	r.print();
//}
//
//void test4()
//{
//	AA a;
//	BB b;
//	CC c;
//
//	print(a);
//	print(b);
//	print2(c);
//}
//
//int main(void)
//{
//	test4();
//
//	return 0;
//}
//
//
//
//
//
