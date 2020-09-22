#include"student.h"
#include<iostream>

double Student::Average() const
{
	if (_scores.size() > 0)
		return _scores.sum() / _scores.size();
	else
		return 0;
}
const std::string& Student::Name() const
{
	return _name;
}

double& Student::operator[](int i)
{
	return _scores[i];
}

double Student::operator[](int i) const
{
	return _scores[i];
}

std::istream& operator>>(std::istream& is, Student& s)
{
	std::cout << "请输入姓名：";
	getline(is, s._name);

	std::cout << "请输入 " << s._scores.size() << " 门成绩: ";
	for (int i = 0; i < s._scores.size(); i++)
	{
		is >> s._scores[i];
	}

	// 读取缓冲区中的剩余字符（包含 \n），如果不读，getline 会有问题
	while (std::cin.get() != '\n')
		;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << "姓名：" << s._name << std::endl;
	os << "成绩：";
	for (int i = 0; i < s._scores.size(); i++)
		os << s._scores[i] << " ";
	os << std::endl;

	return os;
}