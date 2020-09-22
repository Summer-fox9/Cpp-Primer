#include"student2.h"
#include<iostream>

using std::string;
using std::valarray;

typedef valarray<double> ArrayDb;


double Student::Average() const
{
	// 使用 类名 + :: 访问父类方法 
	if (ArrayDb::size() > 0)
		return ArrayDb::sum() / ArrayDb::size();
	else
		return 0;
}
const std::string& Student::Name() const
{
	return *this;
	//return (const string&)*this;
}

double& Student::operator[](int i)
{
	return ArrayDb::operator[](i);
}

double Student::operator[](int i) const
{
	return  ArrayDb::operator[](i);
}

std::istream& operator>>(std::istream& is, Student& s)
{
	std::cout << "请输入姓名：";
	getline(is, (string&)s);

	std::cout << "请输入 " << ArrayDb(s).size() << " 门成绩: ";
	for (int i = 0; i < s.size(); i++)
	{
		is >> s[i];
	}

	// 读取缓冲区中的剩余字符（包含 \n），如果不读，getline 会有问题
	while (std::cin.get() != '\n')
		;
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << "姓名：" << (const string&)s << std::endl;
	os << "成绩：";
	for (int i = 0; i < ArrayDb(s).size(); i++)
		os << s[i] << " ";
	os << std::endl;

	return os;
}