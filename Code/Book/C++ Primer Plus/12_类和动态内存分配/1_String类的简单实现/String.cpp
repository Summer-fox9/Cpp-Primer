#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include"String.h"

int String::num_strings = 0;

String::String()
{
	len = 1;
	str = new char[len];
	/*
	 *	str = new char[1] 为和不写成 str = new char
	 *  这个目的是为了让 new[] 与 delete[] 匹配
	 *  在析构函数中，我们使用的是 delete[] ，如果是其他形式会不匹配
	 */
	str[0] = '\0';
	// 上面的代码也可以改为 str = 0; // sets str to null pointer
	num_strings++;

	//std::cout << "String() invoked: " << num_strings << " "
	//	<< str << std::endl;
}

String::String(const char* s)
{
	len = std::strlen(s);
	str = new char[len + 1];
	std::strcpy(str, s);
	num_strings++;

	//std::cout << "String(const char* s) invoked: " << num_strings << " "
	//	<< str << std::endl;
}

String::String(const String& s)
{
	len = s.len;
	num_strings++;
	str = new char[len + 1];
	std::strcpy(str, s.str);

	//std::cout << "String(const String& s) invoked: " << num_strings << " "
	//	<< str << std::endl;
}

String::~String()
{
	if (str)
	{
		len = 0;
		num_strings--;
		delete[] str;

		//std::cout << "~String() invoked: " << num_strings << " "
		//	<< std::endl;
	}
}

String& String::operator=(const String& s)
{
	if (&s != this)
	{
		delete[] str;
		len = s.len;
		str = new char[len + 1];
		std::strcpy(str, s.str);
	/*	std::cout << "operator=(const String& s) invoked: " << num_strings << " "
			<< std::endl;*/
	}
	return *this;
}

String& String::operator=(const char* s)
{
	delete[] str;
	
	len = std::strlen(s);
	str = new char[len + 1];
	str = std::strcpy(str, s);

	return *this;
}

bool operator<(const String& s1, const String& s2)
{
	// 如果第一个字符串的字符在第二个字符串的字符之前，返回负值
	// 相等，返回 0
	return (std::strcmp(s1.str, s2.str) < 0);
}

bool operator>(const String& s1, const String& s2)
{
	return (std::strcmp(s1.str, s2.str) > 0);
}

bool operator==(const String& s1, const String& s2)
{
	return (std::strcmp(s1.str, s2.str) == 0);
}

char& String::operator[](int n)
{
	return str[n];
}

/*
 * const String s("Shepard");
 * cout << s[1]; // 要确保 s[1] 不被改变 
 */
const char& String::operator[](int n) const
{
	return str[n];
}


std::ostream& operator<<(std::ostream& os, const String& s)
{
	os << s.str;
	return os;
}

/*
 * if判断：如果因为某种原因（到达文件尾，或者读取到了空行）导致输入失败，is 的值为置为 false
 * while 循环：读取多余的输入
 */
std::istream& operator>>(std::istream& is, String& s)
{
	char buffer[String::CINLIM];
	is.get(buffer, String::CINLIM);
	if (is)
		s = buffer;
	while (is && is.get() != '\n')
		;
	return is;
}
