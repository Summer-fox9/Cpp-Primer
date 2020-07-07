#include<iostream>
#include<List>
#include"list.h"

using namespace std;

void test1()
{
	list<int> li;
	li.push_back(1);
	li.push_back(2);
	li.push_back(3);

	list<int>::const_iterator it = li.begin();

	it++;
}

void test2()
{
	List<int> L1;
	List<int>::iterator it = L1.begin();
	it = L1.insert(it, 1);
	it = L1.insert(it, 0);
	printList(L1);
}

class A
{
public:
	friend ostream& operator<<(ostream& _o, const A& L);

	A(int a = 1, int b = 1)
		:_a(a)
		,_b(b)
	{}

	int _a;
	int _b;
};

ostream& operator<<(ostream& _o, const A& L)
{
	_o << L._a << " " << L._b << " ";
	return _o;
}

void test3()
{
	List<A> LA;
	LA.push_back(A());
	LA.push_front(A(0, 0));
	LA.push_back(A(2, 2));

	List<A> copy(LA);
	copy.push_back(A(3, 3));
	
	LA = copy;

	printList(LA);
	printList(copy);

	List<A>::iterator it =  LA.insert(++LA.begin(), A(10, 10));
	LA.insert(it, A(20, 20));

	it = copy.erase(--copy.end()); // 尾删
	copy.erase(it); // it 指向 end() 删除操作不会执行

	printList(LA);
	printList(copy);
}

void test4()
{
	List<A> L;
	L.push_back(A(1, 1));
	L.push_back(A(2, 2));
	L.push_back(A(3, 3));
	List<A>::iterator it = L.begin();
	
	cout << *it << endl;
	
	cout << it->_a << endl;
	cout << it.operator->()->_a << endl;
}

int main(void)
{

	//test1();
	//test2();
	//test3();
	test4();
	
	return 0;
}