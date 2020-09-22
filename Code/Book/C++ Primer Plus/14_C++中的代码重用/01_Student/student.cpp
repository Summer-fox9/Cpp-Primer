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
	std::cout << "������������";
	getline(is, s._name);

	std::cout << "������ " << s._scores.size() << " �ųɼ�: ";
	for (int i = 0; i < s._scores.size(); i++)
	{
		is >> s._scores[i];
	}

	// ��ȡ�������е�ʣ���ַ������� \n�������������getline ��������
	while (std::cin.get() != '\n')
		;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << "������" << s._name << std::endl;
	os << "�ɼ���";
	for (int i = 0; i < s._scores.size(); i++)
		os << s._scores[i] << " ";
	os << std::endl;

	return os;
}