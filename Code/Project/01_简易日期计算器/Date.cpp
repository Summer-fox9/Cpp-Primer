/***********************************************
 *	Date.cpp:
 *		实现输入输出流重载，接口函数实现
 *
 **********************************************/


#include"Date.h"
#include<math.h>


// 重载输入输出流

ostream& operator<<(ostream& _cout, const Date& date)
{
	_cout << date._year << "-" << date._month << "-" << date._day;
	return _cout;
}

istream& operator>>(istream& _cin, Date& date)
{
	cout << "请输入：年 月 日" << endl;
	_cin >> date._year >> date._month >> date._day;
	return _cin;
}


void Date::menu()
{
	cout << endl;
	cout << "         VX公众号：不会编程的程序圆 " << endl;
	cout << endl;
	cout << "**********************************************" << endl;
	cout << "*   " << "菜单：请输入序号完成对应的操作"		 << endl;
	cout << "*          " << "1. 计算日期差"				 << endl;
	cout << "*          " << "2. 推算日期（向后）"			 << endl;
	cout << "*          " << "3. 推算日期（向前）"			 << endl;
	cout << "*          " << "4. 比较日期大小"				 << endl;
	cout << "*          " << "0.     退出"					 << endl;
	cout << "**********************************************" << endl;
}

Date Date::newDate()
{
	int year, month, day;

	cout << "请输入：年 月 日" << endl;
	cin >> year >> month >> day;
	
	Date d1(year, month, day);

	return d1;
}


void Date::daysBetweenTwoDates(const Date& d2)
{
	cout << "两日差：" << abs((*this - d2)) << "天" << endl;
}

void Date::inferDateBack(int day)
{
	cout << day << " 天后的日期为：" << (*this + day) << endl;
}

void Date::inferDateFront(int day)
{
	cout << day << " 天前的日期为：" << (*this - day) << endl;
}


void Date::compareDate(const Date& d2)
{
	if (*this == d2)
		cout << "日期相等" << endl;
	else if (*this > d2)
		cout << *this << " 大于 " << d2 << endl;
	else 
		cout << *this << " 小于 " << d2 << endl;

}

void Date::exitDate()
{

	cout << "感谢支持，再见！" << endl;
	exit(EXIT_SUCCESS);
}
