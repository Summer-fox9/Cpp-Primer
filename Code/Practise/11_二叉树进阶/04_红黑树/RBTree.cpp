#include<iostream>
#include"RBTree.h"

using namespace std;

int main(void)
{
	RBTree<int, int> rbt;

	rbt.insert(make_pair(1, 1));
	rbt.insert(make_pair(2, 1));
	rbt.insert(make_pair(3, 3));
	rbt.insert(make_pair(4, 4));
	rbt.insert(make_pair(5, 5));
	rbt.insert(make_pair(0, 0));
	rbt.insert(make_pair(9, 9));
	rbt.insert(make_pair(8, 8));
	rbt.insert(make_pair(7, 7));
	//rbt.insert(make_pair(6, 6));

	rbt.print();

	cout << rbt.isRBTree() << endl;
}