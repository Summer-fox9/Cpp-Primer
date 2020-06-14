#include<iostream>

using namespace std;

class Date
{
public:
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
	{

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
	Date operator+(int day)
	{
		Date ret = *this;
		ret += day;
		return ret;
	}

	// 日期-天数
	Date operator-(int day)
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
	Date operator++(int)
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
	bool operator>(const Date& d)
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
	bool operator==(const Date& d)
	{
		return _year == d._year && _month == d._month && _day == d._day;
	}

	// >=运算符重载
	bool operator >= (const Date& d)
	{
		return (*this == d || *this > d);
	}
	
	// <运算符重载
	bool operator < (const Date& d)
	{
		return !(*this >= d);
	}
	
	// <=运算符重载
	bool operator <= (const Date& d)
	{
		return !(*this > d);
	}
	
	// !=运算符重载
	bool operator != (const Date& d)
	{
		return !(*this == d);
	}
	
	// 日期-日期 返回天数
	int operator-(const Date& d)
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

	Date* operator&()
	{
		return this;
	}

	void print()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

// 需要将类中的成员变量设置为 public 
//ostream& operator<<(ostream& _cout, const Date& date)
//{
//	_cout << date._year << date._month << date._day << endl;
//	return _cout;
//}

int main(void) {

	Date d(2020, 6, 14);
	d.print();
	d += 20;
	d.print();
	d += 365;
	d.print();
	cout << "================" << endl;
	Date d1(2020, 6, 31);
	cout << "================" << endl;
	Date d2(1, 1, 10);
	d2 -= 10;
	d2.print();
	cout << "================" << endl;
	Date d3(2020, 6, 14);
	d3++.print();
	d3--.print();
	d3.print();
	cout << "================" << endl;
	Date d4(2020, 6, 30);
	(++d4).print();
	(--d4).print();
	cout << "================" << endl;
	Date d5(2019, 12, 31);
	Date d6(2019, 12, 30);
	cout << (d5 == d6) << endl;
	cout << (d5 != d6) << endl;
	cout << (d5 > d6) << endl;
	cout << (d5 >= d6) << endl;
	cout << (d5 < d6) << endl;
	cout << (d5 <= d6) << endl;
	cout << "================" << endl;
	Date d7(1, 2, 15);
	cout << &d7 << endl;
	(d7 + 31).print();
	d7.print();
	(d7 - 31).print();
	d7.print();
	cout << "========看看放了多少天假了========" << endl;
	Date d8(2020, 1, 7);
	Date d9(2020, 6, 14);
	cout << (d9 - d8) << endl;
	cout << (d8 - d9) << endl;

	return 0;
}
