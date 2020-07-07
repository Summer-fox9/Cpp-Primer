#include<iostream>
#include<stack>
#include<queue>
#include<List>
#include"Stack.h"
#include"Queue.h"
#include"Priority_Queue.h"

using namespace std;

void test1()
{
	stack<int> S;

	S.push(1);
	S.push(2);
	S.push(3);

	while (!S.empty())
	{
		cout << S.top() << endl;
		S.pop();
	}
}

/**
 * 仿函数类
 */
//template<class T>
//struct Less
//{
//	// () 运算符重载
//	bool operator()(const T& t1, const T& t2)
//	{
//		return t1 < t2;
//	}
//};
//
//template<class T>
//struct Greater
//{
//	// () 运算符重载
//	bool operator()(const T& t1, const T& t2)
//	{
//		return t1 > t2;
//	}
//};

void test2()
{
	// 优先队列默认为大根堆
	priority_queue<int> pq;

	pq.push(9);
	pq.push(5);
	pq.push(2);
	pq.push(7);
	
	while (!pq.empty())
	{
		cout << pq.top() << endl;
		pq.pop();
	}

	// 使用仿函数类将堆改为小根堆
	priority_queue<int, vector<int>, Greater<int>> PQ;
	PQ.push(9);
	PQ.push(5);
	PQ.push(2);
	PQ.push(7);

	while (!PQ.empty())
	{
		cout << PQ.top() << endl;
		PQ.pop();
	}
}

template<class T>
void print(T t)
{
	while (!t.empty())
	{
		cout << t.top() << " ";
		t.pop();
	}
	cout << endl;
}

void test3()
{
	//Stack<int, deque<int>> S; // ok
	//Stack<int, vector<int>> S;// ok
	Stack<int, list<int>> S;// ok

	S.push(1);
	S.push(2);
	S.push(3);

	print(S);

	cout << S.top() << endl;
	S.pop();
	cout << S.top() << endl;
	S.pop();

	cout << S.size() << endl;
}

void test4()
{
	//Queue<int, deque<int>> S;// ok
	//Queue<int, vector<int>> S; // error
	Queue<int, list<int>> S;// ok

	S.push(1);
	S.push(2);
	S.push(3);

	//print(S);

	cout << S.front() << endl;
	S.pop();
	cout << S.front() << endl;
	S.pop();

	cout << S.size() << endl;
}

void test5()
{
	Priority_Queue<int, vector<int>> PQ; // ok
	//Priority_Queue<int, deque<int>> PQ; // ok
	//Priority_Queue<int, list<int>> PQ; //error

	PQ.push(9);
	PQ.push(5);
	PQ.push(2);
	PQ.push(7);

	print(PQ);

	cout << PQ.size() << " " << PQ.empty() << endl;
}

class Date 
{
public:
	int _year;
	int _month;
	int _day;
	
	Date(int year = 2020, int month = 7, int day = 7)
		:_year(year)
		,_month(month)
		,_day(day)
	{}

	bool operator>(const Date& d) const
	{
		return ((d._year < _year) ||
			(d._year == _year && d._month < _month) ||
			(d._year == _year && d._month == _month && d._day < _day));
	}

	bool operator<(const Date& d) const
	{
		return ((d._year > _year) ||
			(d._year == _year && d._month > _month) ||
			(d._year == _year && d._month == _month && d._day > _day));
	}
};

ostream& operator<<(ostream& _o, const Date& d)
{
	_o << d._year << "-" << d._month << "-" << d._day << endl;
	return _o;
}

void test6()
{
	Priority_Queue<Date, vector<Date>, Greater<Date>> PQ;

	PQ.push(Date(2020, 7, 7));
	PQ.push(Date(2020, 7, 5));
	PQ.push(Date(2020, 7, 9));
	PQ.push(Date(2020, 7, 8));
	PQ.push(Date(2020, 7, 6));

	print(PQ);
}

int main(void)
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();

	return 0;
}

