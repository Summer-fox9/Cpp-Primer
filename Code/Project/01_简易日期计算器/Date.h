/***********************************************
 *	Date.h:
 *		Date 类。先理解日期类的其他函数，
 *		然后再去看接口函数，接口函数你可以自己实现		
 *		
 **********************************************/


#pragma once

#include<iostream>
#include<stdlib.h>

using namespace std;

class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& date);
	friend istream& operator>>(istream& _cin, Date& date);

public:
	
	//  接口函数
	static void menu();
	
	// 创建一个新的对象，由用户输入初始化
	static Date newDate();

	// 计算日期差
	void daysBetweenTwoDates(const Date& d2);

	// 推算日期（向后）
	void inferDateBack(int day);

	// 推算日期（向前）
	void inferDateFront(int day);

	//比较日期大小
	void compareDate(const Date& d2);

	// 推出程序
	static void exitDate();

	// 全缺省的构造函数
	Date(int year = 1900, int month = 1, int day = 1)
	{
		if (year > 0 && month > 0 && month < 13 && day > 0 && day <= getMonthDay(year, month))
		{
			_year = year;
			_month = month;
			_day = day;
		}
		else
		{
			cout << "日期输入非法：" << year << "-" << month << "-" << day << endl;
			cout << "日期重置为：1970-1-1" << endl;
			_year = 1970;
			_month = 1;
			_day = 1;
		}
	}

	// 拷贝构造函数
	// d2(d1)
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	}


	// 赋值运算符重载
	// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	// 析构函数
	~Date()
	{}
	
	// 取地址

	Date* operator&()
	{
		return this;
	}

	const Date* operator&() const
	{
		return this;
	}
	
	// 下面的这些函数你也可以设置为 public
private:
	// 获取某年某月的天数
	int getMonthDay(int year, int month)
	{
		static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		int day = days[month];

		// 判断是否为闰年
		if (month == 2 && ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
			day++;

		return day;
	}



	// 日期+=天数
	Date& operator+=(int day)
	{
		// 日期 += -天数 也就等于 日期 -= 天数
		if (day < 0)
			return *this -= day;

		_day += day;

		// 天数大于当月天数
		while (_day > getMonthDay(_year, _month))
		{
			// 天数减去当月天数
			_day -= getMonthDay(_year, _month);
			_month++;
			// 月份大于 12
			if (_month > 12)
			{
				_month = 1;
				_year++;
			}
		}

		return *this;
	}

	// 日期+天数
	// 不能修改当前的对象
	Date operator+(int day) const
	{
		Date ret = *this;
		ret += day;
		return ret;
	}

	// 日期-天数
	Date operator-(int day) const
	{
		Date ret = *this;
		ret -= day;
		return ret;
	}


	// 日期-=天数
	Date& operator-=(int day)
	{
		if (day < 0)
			return *this += day;

		_day -= day;

		// 如果日期小于零，每轮循环应该加上上一个月的天数
		// 但是上一个月有可能小于等于 0，所以不能直接加上一个月的天数，应该先推出合法的上个月1
		while (_day <= 0)
		{
			_month--;
			if (_month <= 0)
			{
				_month = 12;
				_year--;
				if (_year <= 0)
				{
					cout << "天数过大，日期重置为：1-1-1" << endl;
					_year = 1;
					_month = 1;
					_day = 1;
					return *this;
				}
			}
			_day += getMonthDay(_year, _month);
		}

		return *this;
	}

	// 前置++
	Date& operator++()
	{
		return *this += 1;
	}

	// 后置++
	Date& operator++(int)
	{
		// 调用拷贝构造
		// 先保存当前的状态
		Date ret(*this);
		*this += 1;
		// 返回自增前的状态
		return ret;
	}

	// 前置--
	Date& operator--()
	{
		return *this -= 1;
	}

	// 后置--
	Date operator--(int)
	{
		Date ret(*this);
		*this -= 1;
		return ret;
	}



	// >运算符重载
	bool operator>(const Date& d) const
	{
		if (_year > d._year)
			return true;
		else if (_year == d._year && _month > d._month)
			return true;
		else if (_year == d._year && _month == d._month && _day > d._day)
			return true;
		else
			return false;

	}

	// ==运算符重载
	bool operator==(const Date& d) const
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	// >=运算符重载
	bool operator >= (const Date& d) const
	{
		return (*this == d || *this > d);
	}

	// <运算符重载
	bool operator < (const Date& d) const
	{
		return !(*this >= d);
	}

	// <=运算符重载
	bool operator <= (const Date& d) const
	{
		return !(*this > d);
	}

	// !=运算符重载
	bool operator != (const Date& d) const
	{
		return !(*this == d);
	}

	// 日期-日期 返回天数
	int operator-(const Date& d) const
	{
		Date d1(*this);
		int num = 0;
		if (d1 < d)
		{
			while (d1 < d)
			{
				d1++;
				num--;
			}
		}
		else
		{
			// 如果 d1 == d 那么不会进入循环 num 为 0
			while (d1 > d)
			{
				d1--;
				num++;
			}
		}

		return num;
	}


private:
	// 成员变量
	int _year;
	int _month;
	int _day;
};






