#include<set>
#include<map>
#include<iostream>

using namespace std;

void test1()
{
	multiset<int> ms;

	ms.insert(-1);
	ms.insert(0);
	ms.insert(1);
	ms.insert(1);
	ms.insert(-1);

	for (const auto& e : ms)
	{
		cout << &e  << " " << e << endl;
	}
	
	// find 返回找到的第一个 key 的迭代器
	multiset<int>::iterator it = ms.find(1);

	cout << &*it << endl;

	cout << ms.count(-1) << endl;
	
}

// multimap 没有 operator[] 和 at() 接口，因为同一个 key 可能对应不同的 value
void test2()
{
	multimap<string, int> mm;

	mm.insert(make_pair("8.1", 0));
	mm.insert(make_pair("8.2", 0));
	mm.insert(make_pair("8.3", 0));
	mm.insert(make_pair("8.4", 1));
	mm.insert(make_pair("8.1", 0));
	mm.insert(make_pair("8.2", 0));
	mm.insert(make_pair("8.3", 0));

	for (const auto& e : mm)
	{
		cout << &e << " " << e.first << " " << e.second << endl;
	}

	multimap<string, int>::iterator it = mm.find("8.3");

	cout << &*it << endl;
}

void test3()
{
	multimap<string, int> mm;

	mm.insert(make_pair("8.1", 0));
	mm.insert(make_pair("8.2", 0));
	mm.insert(make_pair("8.3", 0));
	mm.insert(make_pair("8.4", 1));
	mm.insert(make_pair("8.1", -1));
	mm.insert(make_pair("8.1", -2));
	mm.insert(make_pair("8.1", -3));
	mm.insert(make_pair("8.1", -4));

	pair<multimap<string, int>::iterator, multimap<string, int>::iterator> Range = mm.equal_range("8.1");

	multimap<string, int>::iterator it = Range.first;
	while (it != Range.second)
	{
		cout << it->first << " " << it->second << endl;
		++it;
	}
}

int main(void)
{
	test3();

	return 0;
}