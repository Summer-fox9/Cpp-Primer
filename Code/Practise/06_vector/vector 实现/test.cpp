#include<iostream>
#include<vector>
#include<string>
#include"vector.h"

using namespace std;



void test1()
{
	Vector<int> V;

	V.push_back(1);
	V.push_back(2);
	V.push_back(3);
	cout << V.capacity() << endl;



	Vector<string> V1;

	V1.push_back("111");
	V1.push_back("222");
	V1.push_back("3333");

	// printVector(V);
}

void test2()
{
	Vector<int> V;

	V.resize(2);
	V.resize(5, 1);
	V.resize(3);
	V.printVector();

	Vector<string> V1;

	V1.resize(2);
	V1.resize(5, "123");
	V1.resize(3);
	V1.printVector();
}

void test3()
{
	Vector<int> V;

	V.insert(V.begin(), 5);
	V.insert(V.end(), 3);
	cout << *V.insert(V.end() - 1, 4) << endl;;
	V.printVector();

	Vector<string> V1;

	V1.insert(V1.begin(), "ooo");
	V1.insert(V1.end(), "xxx");
	V1.insert(V1.end() - 1, "---");
	V1.printVector();

	cout << "==================================" << endl;
	
	// 解引用 erase 的返回值之前先判断返回值与 end() 是否相等

	Vector<int>::iterator iit;
	if ((iit = V.erase(V.begin())) != V.end())
		cout << *iit << endl;
	V.erase(V.end() - 1);
	V.printVector();

	Vector<string>::iterator sit;
	if ((sit = V1.erase(V1.begin())) != V1.end())
		cout << *sit << endl;
	V1.erase(V1.end() - 1);
	V1.printVector();
}

void test4()
{
	Vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	
	// v {1, 2, 3, 4, 5, 6, 7}

	Vector<int>::iterator it = v.begin();
	
	// 删除奇数，程序有没有问题？ 
	while (it != v.end())
	{
		if (*it % 2 != 0)
			it = v.erase(it);
		it++;
	}
	v.printVector();

	// 删除偶数呢？
	while (it != v.end())
	{
		if (*it % 2 == 0)
			it = v.erase(it);
		it++;
	}
	v.printVector();

	// 思考一下原因
	// 其实这和迭代器失效也有关系
	// 删除奇数的正确写法：
	while (it != v.end())
	{
		if (*it % 2 != 0)
			it = v.erase(it);
			// 另外，不更新迭代器在这里也是可以正常编译运行的
			// 但是这个前提是迭代器不失效而且容器是顺序表存储的，如果是链表存储，那么这里就是错误的
		else
			it++;
	}
	v.printVector();	
}

void test5()
{
	Vector<int> v;

	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);

	Vector<int> v1(v);
	v1.printVector();

	v1.push_back(8);

	v = v1;
	v.printVector();
}

class B
{
private:
	char ch;
};

class A
{
public:
	~A()
	{

	}

	int a;
	B b;
};

void test6()
{
	Vector<string> v;

	v.push_back("aaa");
	v.push_back("bbb");
	v.push_back("ccc");
	
	Vector<string> v2(v);
	v2.printVector();
	v2.push_back("ddd");

	v = v2;
	v.printVector();
}


int main() 
{
	test6();

	return 0;
}

