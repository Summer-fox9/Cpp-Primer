#include<iostream>
#include"BinarySearchTree.h"

using namespace std;

void test1()
{
	BSTree<int> T;

	T.insert(5);
	T.insert(3);
	T.insert(1);
	T.insert(4);
	T.insert(0);
	T.insert(2);
	T.insert(7);
	T.insert(6);
	T.insert(8);
	T.insert(9);
	T.print();

	T.erase(3);
	T.print();

	T.erase(3);
	T.print();

	T.erase(8);
	T.print();

	T.erase(9);
	T.print();

	BSTree<int> T2(T);

	T2.print();

	T2.erase(5);
	T2.print();

	T = T2;
	T.print();
}

int main(void)
{
	test1();

	return 0;
}