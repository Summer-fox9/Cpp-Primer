#include<iostream>
#include<string>
#include<string.h>
#include "String.h"

using namespace std;


// 以下是对 STL 中的 string 和我实现的 String 做出的对比
// 如果我没有 cout 显式的输出，就是在调试中对比两个类的实例的区别
// 我也推荐你用调试去观测，因为十分方便，毕竟这是 VS 的优势
int main(void)
{
	string str;
	String Str;

	cout << "========            无参构造           ========" << endl;

	cout << "========          c string 构造        ========" << endl;
	string str1("123");
	String Str1("123");

	cout << "========            拷贝构造           ========" << endl;
	string str2(str1);
	String Str2(Str1);

	cout << "========        赋值运算符重载         ========" << endl;

	str = str2;
	Str = Str2;

	cout << "========             迭代器            ========" << endl;

	for (auto& c : str1)
	{
		c = 'a';
		cout << c << " ";
	}
	cout << endl;

	for (const auto& c : str1)
	{
		cout << c << " ";
	}
	cout << endl;

	for (auto& c : Str1)
	{
		c = 'a';
		cout << c << " ";
	}
	cout << endl;

	for (const auto& c : Str1)
	{
		cout << c << " ";
	}
	cout << endl;

	cout << "========        resize，reserve       ========" << endl;

	str1.resize(5);
	str1.resize(30, 'x');
	str1.reserve(50);

	Str1.resize(5);
	Str1.resize(30, 'x');
	Str1.reserve(50);

	getchar();
	return 0;

}

// cout << "======== 无参构造 ========" << endl;