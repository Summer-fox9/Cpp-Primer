#include<iostream>
#include"AVLTree.h"

using namespace std;

void testAVLT()
{
	int array[] = { 0, 9, 1, 4, 3, 5, 6, 8, 7, 2 };

	AVLTree<int> T;

	// 如果你的 AVL Tree 实现正确，打印出来的结果应该和我的一样
	for (const auto& e : array)
	{
		T.insert(e);
	}

	T.print();
}

void testDoubleRotateBF()
{
	AVLTree<int> T1, T2;

	int array1[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	for (const auto& e : array1)
	{
		T1.insert(e);
	}
	cout << T1.isAVLT() << endl;

	int array2[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	for (const auto& e : array2)
	{
		T2.insert(e);
	}
	cout << T2.isAVLT() << endl;
}

int main(void)
{
	// testAVLT();

	testDoubleRotateBF();

	return 0;
}
