#include<iostream>
#include"Queue.h"

int main(void)
{
	using std::cout;
	using std::endl;

	Queue q;

	q.EnQueue(1);
	q.EnQueue(2);
	q.EnQueue(3);
	q.EnQueue(4);

	q.Show();

	int a;
	q.DeQueue(a);

	cout << a << endl;

	q.Show();

	return 0;
}