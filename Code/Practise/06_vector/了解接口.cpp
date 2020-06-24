#include<iostream>
#include<vector>
#include<string>

using namespace std;

// 构造
void test1()
{
	// 这三个都是空的
	vector<int> v1;
	vector<char> v2;
	vector<string> v3;

	// size 为 10，值都是 5
	vector<int> v4(10, 5);

	string s("0123456789");
	// size 为 10，capacity 为 15 代表一个字符串
	string s1(s.begin(), s.end());
	// size，capacity 都是 10，它就是个字符数组
	vector<char> v5(s.begin(), s.end());

	vector<char> v6(v5);
}

// 迭代
void test2()
{
	vector<int> v(10, 6);
	vector<int>::iterator vit = v.begin();

	for (auto& i : v)
	{
		cout << i << " ";
		i = 66;
	}
	cout << endl;

	while (vit != v.end())
	{
		cout << *vit << " ";
		*vit = 666;
		vit++;
	}
	cout << endl;

	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
		v[i] = 0;
	}
	cout << endl;

	for (auto& i : v)
	{
		cout << i << " ";
	}
	cout << endl;
	
	string s("0123456789");
	vector<char> v2(s.begin(), s.end());
	vector<char>::reverse_iterator rvit = v2.rbegin();

	while(rvit != v2.rend())
	{
		cout << *rvit << " ";
		rvit++;
	}
	cout << endl;
}

template<typename T>
void print(const vector<T>& v)
{
	typename vector<T>::const_iterator cit = v.cbegin();
	// 这里原因是vector<T>本身类型就没确定，再给一个迭代器，它就不知道该给迭代器什么类型了，
	// 加上typename表示以后在确定类型，现在先不管
	
	while (cit != v.cend())
	{
		cout << *cit << " ";
		cit++;
	}
	cout << endl;

	typename vector<T>::const_reverse_iterator crit = v.crbegin();

	while (cit != v.cend())
	{
		cout << *crit << " ";
		crit++;
	}
	cout << endl;
}

void test3()
{
	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	char a1[] = "0123456789";

	vector<int> v(a, a + 10);
	vector<char> v1(a1, a1 + 10);

	string a2[] = { "123", "ooo", "xxx" };
	vector<string> v2(a2, a2 + 3);

	print(v);
	print(v1);
	print(v2);

	// resize 如果缺省第二个参数，默认值 value_type() 会根据类型生成
	// 指针就是 nullptr，int 就是 0，类类型就是调用该类的构造

	v.resize(20);
	v1.resize(20);
	v2.resize(20);


}

void test4()
{
	vector<int> v;

	v.at(0);
}

void test5()
{
	vector<int> v(5, 1);
	cout << v.capacity() << endl;
	vector<int>::iterator it = v.begin();
	v.push_back(2);
	cout << v.capacity() << endl;
	// 注释下面这一行，发现 v 的 capacity 发生了变化
	cout << *it << endl; // 程序崩溃
}

void test6()
{
	vector<int> v(5, 1);
	vector<int>::iterator it = v.begin();
	vector<int>::iterator it2 = it + 2;
	// 删除下标的区间 [1, 2]， pos 为 1
	v.erase(it + 1, it + 3);
	// it 指向下标为 0 的位置，在 pos 前，所以迭代器有效
	cout << *it << endl;
	// it2 指向下标为 2 的位置，在 pos 之后，迭代器失效，程序崩溃
	cout << *it2 << endl;
	
}

void test7()
{
	vector<int> v(5, 1);
	cout << v.capacity() << endl;
	v.reserve(7);
	cout << v.capacity() << endl;
	vector<int>::iterator it = v.begin();
	v.push_back(2);
	cout << v.capacity() << endl;
	cout << *it << endl;
}

void test8()
{
	vector<int> v(5, 1);
	vector<int>::iterator it = v.begin();

	while (it != v.end())
	{
		it = v.erase(it);
	}
}

void test9()
{
	vector<int> v(5, 1);
	vector<int>::iterator it = v.begin();

	it = v.insert(it, 2);
	cout << *it << endl;
}

int main(void)
{
	cout << "test vector" << endl;

	test9();

	return 0;
}

