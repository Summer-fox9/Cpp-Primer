#include"student2.h"
#include<iostream>

using std::string;
using std::valarray;

typedef valarray<double> ArrayDb;


double Student::Average() const
{
	// ʹ�� ���� + :: ���ʸ��෽�� 
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
	std::cout << "������������";
	getline(is, (string&)s);

	std::cout << "������ " << ArrayDb(s).size() << " �ųɼ�: ";
	for (int i = 0; i < s.size(); i++)
	{
		is >> s[i];
	}

	// ��ȡ�������е�ʣ���ַ������� \n�������������getline ��������
	while (std::cin.get() != '\n')
		;
	
	return is;
}

std::ostream& operator<<(std::ostream& os, const Student& s)
{
	os << "������" << (const string&)s << std::endl;
	os << "�ɼ���";
	for (int i = 0; i < ArrayDb(s).size(); i++)
		os << s[i] << " ";
	os << std::endl;

	return os;
}