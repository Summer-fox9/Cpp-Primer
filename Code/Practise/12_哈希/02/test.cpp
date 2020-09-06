#include"UnorderedMap.hpp"
#include"UnorderedSet.hpp"

#include<iostream>

using namespace std;

void testMap()
{
	//UnorderedMap<int, int> um;

	//um.insert(make_pair(1, 1));
	//um.insert(make_pair(2, 1));
	//um.insert(make_pair(3, 1));
	//um.insert(make_pair(4, 1));
	//um.insert(make_pair(5, 1));
}

void testSet()
{
	UnorderedSet<int, KeyIsInt<int>> us;

	us.insert(1);
	us.insert(2);
	us.insert(3);
	us.insert(4);
	us.insert(5);

	UnorderedSet<int, KeyIsInt<int>>::iterator it = us.begin();

	while (it != us.end())
	{
		cout << *it << endl;
		++it;
	}

}

// 如果 key 为 string 非整数类型，比如 string 
// 我们需要将其转换为整数，再进行映射
void testSet2()
{
	UnorderedSet<string, StrToInt> us;

	us.insert("123");
	us.insert("1234");
	us.insert("323");
	us.insert("423");
	us.insert("223");

	UnorderedSet<string, StrToInt>::iterator it = us.begin();

	while (it != us.end())
	{
		cout << *it << endl;
		++it;
	}
}


int main(void)
{
	//testMap();
	testSet2();

	return 0;
}