#include<iostream>

using namespace std;

class A
{
public:
	// final: 定义的函数不能被重写，体现实现继承（拿来直接用）
	virtual void print() final
	{
		cout << "A: " << _a << endl;
	}

	virtual void drive()
	{
		cout << "A 开车"<< endl;
	}

private:
	int _a = 10;
};

class B : public A
{
public:
	// override: 必须要函数重写，编译器提供检查,接口继承（拿来需要自己实现）
	void drive() override
	{
		cout << "B 开车" << endl;
	}
};

void test1()
{
	A* pa = new B;
	pa->drive();
}

// 抽象类：包含纯虚函数的类
class A2
{
public:
	// 纯虚函数
	virtual void print() = 0;
};

void test2()
{
	// 抽象类不能实例化出对象
	// A2 a;
}

class Base
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}

	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}

	void Func3()
	{
		cout << "Base::Func3()" << endl;
	}

private:
	int _b = 1;
};

class Derive : public Base
{
public:
	virtual void Func1()
	{
		cout << "Derive::Func1()" << endl;
	}

	virtual void Func3()
	{
		cout << "Derive::Func3()" << endl;
	}

	virtual void Func4()
	{
		cout << "Derive::Func4()" << endl;
	}

private:
	int _d = 2;
};

typedef void (*VFPTR)();

void PrintVTable(VFPTR* VTable)
{
	cout << "虚表地址：" << VTable << endl;
	for (int i = 0; VTable[i] != nullptr; i++)
	{
		cout << "第 " << i + 1 << " 个虚函数地址：" << VTable[i] << endl;
		VFPTR f = VTable[i];
		f();
	}
}

void test3()
{
	Base b;
	Derive d;
	
	VFPTR* VTable = (VFPTR*)(*(int*)&b);
	PrintVTable(VTable);

	VTable = (VFPTR*)(*(int*)&d);
	PrintVTable(VTable);

	// 如果你的虚表打印出来的特别多，清理一下解决方案，重新编译运行（gcc 是绝不会出现这种问题的，垃圾 windows
}

class Base1
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}

	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}

private:
	int _b = 1;
};

class Base2
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}

	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}

private:
	int _b = 1;
};

class Derive2 : public Base1, public Base2
{
public:
	virtual void Func1()
	{
		cout << "Derive::Func1()" << endl;
	}

	virtual void Func3()
	{
		cout << "Derive::Func3()" << endl;
	}


private:
	int _d = 2;
};

void test4()
{
	Derive2 d;
	
	// Base1 的虚表指针
	VFPTR* VTable = (VFPTR*)*(int*)&d;
	PrintVTable(VTable);

	// Base2 的虚表指针
	VTable = (VFPTR*)*(int*)((char*)&d + sizeof(Base1));
	PrintVTable(VTable);
}

int main(void)
{
	test4();

	return 0;
}