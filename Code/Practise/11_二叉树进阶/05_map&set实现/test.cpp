#include<iostream>
#include"map.hpp"
#include"set.hpp"

using namespace std;

int main(void)
{
	Map<int, int> M;

	M.insert(make_pair(1, 1));
	M.insert(make_pair(3, 3));
	M.insert(make_pair(2, 2));
	M.insert(make_pair(5, 5));
	M.insert(make_pair(4, 4));

	M[3] = 100;
	M[0] = 0;

	Map<int, int>::iterator it = M.begin();

	while (it != M.end())
	{
		cout << it->first << " " << it->second << endl;
		// 注意这里 -> 其实有两个，编译器优化了一个。相当于：
		// cout << it.operator->()->first;
		++it;
	}
}