#include<iostream>
#include"String.h"

void test1()
{
	String s1;
	String s2("Shepard");
	String s3(s2);
	String s4 = String(s2);

	s1 = s2;

	std::cout << s1 << s2 << std::endl;
}

void test2()
{
	String s1("heap");
	const String s2("sea");

	s1[0] = 'b';
	std::cout << s1 << " " << s2[2] << std::endl;
}


// 下面是一个可以收集谚语然后计算最短的谚语和字母序最小的谚语的程序
const int ArSize = 10;
const int MaxLen = 81;

void test3()
{
	using std::cin;
	using std::cout;
	using std::endl;

	String name;
	cout << "What's your name?" << endl;
	cin >> name;
	cout << "Hello! " << name << " Please enter " 
		<<  ArSize << "short sayings<empty line to quit>" << endl;

	String sayings[ArSize];
	char temp[MaxLen];

	int i;
	for (i = 0; i < ArSize; i++)
	{
		cout << i + 1 << ": ";
		cin.get(temp, MaxLen);
		while (cin && cin.get() != '\n') 
			;
		if (!cin || temp[0] == '\0') // error & empty line
			break;
		else
			sayings[i] = temp; // overloaded assignment
	}
	int total = i;

	cout << "\n Here are your sayings: " << endl;
	for (i = 0; i < total; i++)
	{
		cout << sayings[i][0] << ": " << sayings[i] << endl;
	}

	int shortest = 0;
	int first = 0;
	for (int i = 1; i < total; i++)
	{
		if (sayings[i].length() < sayings[shortest].length())
			shortest = i;
		if (sayings[i] < sayings[first])
			first = i;
	}
	
	cout << "shortest saying: " << sayings[shortest] << endl;
	cout << "first saying: " << sayings[first] << endl;
	cout << String::HowMany() << " object used" << endl;
}

int main(void)
{
	test3();
}