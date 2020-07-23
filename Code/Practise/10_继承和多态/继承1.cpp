#include<iostream>

using namespace std;

/**
 * 父类/基类:
 *
 */
class Person
{
public:
	void print()
	{
		cout << "age = " << _age << " name =  " << _name << " " << _test << endl;
	}

public:
	int start;

protected:
	int _age = 20;
	string _name = "Shepard";

// 私有成员是子类的一部分，但是子类不可见（不能直接访问）
// 但是子类继承的 print() 函数会访问私有成员，调用子类的 print 函数，是可以访问这个私有成员的
private:
	int _test = 1;
};

/**
 * 子类/派生类: 
 * 
 */
class Student : public Person
{};

class Empty
{};

void test1()
{
	Student s;
	s.print();
	
	// 空的子类的大小和父类相同，空类的大小为 1
	cout << sizeof(Person) << endl;
	cout << sizeof(Student) << endl;
	cout << sizeof(Empty) << endl;
}

class Student2 : public Person
{
public:
	void setAge(int age)
	{
		_age = age;
	}

public:
	int id = 1234;
};

/**
 * 切片
 */
void test2()
{
	Person p;
	Student2 s;

	// 切片操作，把子类的一部分（整体）切给父类
	// 切片不是隐式类型转换，是安全的
	p = s;
	Person& rp = s;
	Person* pp = &s;

	// s = p; // 子类对象不能用父类对象来赋值
	// 可以强转父类类型，但是这样不安全，可能会访问越界
	// 指针的类型决定能访问的内存大小。
	// 因为 Student2 类型大小大于其父类，所以 Student2* 能访问的内存更多
	// 指针是 Student2 类型，ps 实际指向的是 Person 类型对象
	Student2& rs = (Student2&)p;
	Student2* ps = (Student2*)&p;
	
	cout << rs.id << " " << ps->id << endl; // -858993460 -858993460
	
	// 这样写是安全的，指针是 Student2 类型，ps 实际指向的也是 Student2 类型的对象
	Student2& rs2 = (Student2&)rp;
	Student2* ps2 = (Student2*)pp;

	cout << rs2.id << " " << ps2->id << endl; // 	1234 1234

}

void test2p()
{
	Person p;
	Student2 s;

	Student2* pp = (Student2*)&p;
	
	// pp 是指向 Person 类型的指针
	// start 是 Person 类中的第一个成员变量，所以它的地址就是Person 类型对象 p 的首地址
	// 用 Person 对象的首地址减去 pp->id 的地址，我们就可以知道 pp->id 相对于 p 首地址的偏移量
	cout << &pp->start - &pp->id << endl;

	Student2* ps = &s;
	
	// ps 就是指向 Student 类型的指针
	// 计算结果可以看出 成员 id 相对于 Student 类型对象 s 首地址的偏移量
	cout << &ps->start - &ps->id << endl;

	// 输出都是 10
	// 这说明，对对象的成员访问实际上是靠指针偏移量完成的
}

void print()
{
	cout << "global" << endl;
}

/**
 *	父类和子类的作用域独立，可以有同名的成员
 *	子类会就近访问自己定义的成员，使用 父类::成员 访问父类成员
 *	
 *	函数隐藏/屏蔽 ≠ 函数重载
 *	不同的作用域没有重载的概念
 *	
 *	注意是隐藏而不是覆盖，如果要调用父类或全局的同名函数需要特殊处理（不像 C 语言能调用就调用）
 *	调用全局函数 ::函数名
 */
class Student3 : public Person
{
public:
	void print()
	{
		// 隐藏子类中父类的同名成员（作用域就近）
		cout << _age << endl; // 26
		// 要输出父类中的 _age
		cout << Person::_age << endl;
		
		// 调用的是 Student3 的成员函数，从而引发递归
		// print();

		// 访问父类的同名函数
		Person::print();

		// 调用全局的 print 函数
		::print();
	}
	

protected:
	int _age = 26;
};

void test3()
{
	Person p;
	Student3 s;
	
	cout << sizeof(p) << " " << sizeof(s) << endl;// 36 40

	s.print();
}

/**
 * 成员函数
 */
class Person2
{
public:
	Person2(string name = "Shepard", int age = 20)
		:_name(name)
		,_age(age)
	{
		cout << "Person2(string = , int = )" << endl;
	}

	Person2(string name, int age, int nouse)
		:_name(name)
		,_age(age)
	{
		cout << "Person2(string, int)" << endl;
	}

	Person2(const Person2& p)
		:_name(p._name)
		,_age(p._age)
	{
		cout << "Person2(const Person2& p)" << endl;
	}

	Person2& operator=(const Person2& p)
	{
		if (this != &p)
		{
			_name = p._name;
			_age = p._age;
			cout << "Person2& operator=(const Person2& p)" << endl;
		}
		return *this;
	}

	~Person2()
	{
		cout << "~Person2()" << endl;
	}

protected:
	string _name;
	int _age;
};

class Student4 : public Person2
{
	// 如果没有显示的调用父类的构造函数，编译器自动调用父类的默认构造函数,完成父类成员的初始化
	// 如果父类没有默认构造函数，必须显示的调用
public:
	// 自定义的默认构造也会调用父类的默认构造（初始化列表处）
	// 先构造父类，然后再构造子类

	// 调用父类的默认构造
	Student4(int id = 1234)
		:_id(id)
	{
		cout << "Student4(id = )" << endl;
		//cout << _name << " " << _age << " " << _id << endl;
	}

	// 指定调用父类的构造函数
	// 先构造父类然后再初始化子类的成员
	Student4(int id, int nouse)
		:Person2("Samantha", 26)
		,_id(id)
	{
		cout << "Student4(int, int)" << endl;
		//cout << _name << " " << _age << " " << _id << endl;
	}

	// 1.编译器自动生成的拷贝构造调用父类的拷贝构造
	// 2.显示定义的拷贝构造调用父类的默认构造
	// 3.调用父类拷贝构造就是切片操作
	Student4(const Student4& s)
		:Person2(s) // 切片
		// 也可以 Person(s._name, s,_age) 调用父类的默认构造
		,_id(s._id)
	{
		cout << "Student4(const Student4& s)" << endl;
	}
	
	// 1.编译器自动生成的赋值运算符重载函数调用父类的赋值运算符重载函数
	// 2.显示定义的赋值运算符重载函数不会调用父类的，因为同名/成员隐藏
	//   需要显示调用父类的赋值运算符重载函数
	Student4& operator=(const Student4& s)
	{
		if (this != &s)
		{
			Person2::operator=(s);
			_id = s._id;
			cout << "Student4& operator=(const Student4& s)" << endl;
		}
		return *this;
	}
	
	// 自动调用父类析构
	// 先调用子类析构然后调用父类析构
	~Student4()
	{
		cout << "~Student4()" << endl;
		// ~Person2(); // 不能直接调用析构，因为底层子类和父类的函数名相同，构成函数隐藏
		//Person2::~Person2(); // 不管是否显示调用父类析构，编译器都会自动调用一次父类析构
		// 不要显示的调用父类析构，可能会造成资源的二次释放
	}
	
protected:
	int _id;
};

void test4()
{
	//Student4 s(4321, 0);
	Student4 s2;
	//Student4 copy(s2);

	//s = s2;

}

/**
 * 菱形继承和菱形虚拟继承
 * 虚基表和虚基表指针
 *
 */

int main(void)
{
	test4();
	

	return 0;
}