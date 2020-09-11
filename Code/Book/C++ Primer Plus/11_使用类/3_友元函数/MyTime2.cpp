#include<iostream>
#include"MyTime2.h"

Time::Time()
{
	hours = minutes = 0;
}

Time::Time(int h, int m)
{
	if (h < 0 || m < 0)
	{
		std::cerr << "hour or minute used can't be negative"
			<< "set to 0\n";
		h = m = 0;
	}
	hours = h;
	minutes = m;
}

void Time::AddMin(int m)
{
	if (m < 0)
	{
		std::cerr << "minute to add can't be negative"
			<< "set to 0\n";
		m = 0;
	}
	minutes += m;
	hours += minutes / 60;
	minutes %= 60;
}
void Time::AddHr(int h)
{
	if (h < 0)
	{
		std::cerr << "hour to add can't be negative"
			<< "set to 0\n";
		h = 0;
	}
	hours += h;
}
void Time::Reset(int h, int m)
{
	if (h < 0 || m < 0)
	{
		std::cerr << "hour or minute used can't be negative"
			<< "set to 0\n";
		h = m = 0;
	}
	hours = h;
	minutes = m;
}

Time Time::operator+(const Time& t) const
{
	Time add;
	add.minutes = minutes + t.minutes;
	add.hours = hours + t.hours;
	add.hours += add.minutes / 60;
	add.minutes %= 60;

	return add;
}

Time Time::operator-(const Time& t) const
{
	Time minus;
	
	long m1 = minutes + hours * 60;
	long m2 = t.minutes + t.hours * 60;

	minus.hours = (m1 - m2) / 60;
	minus.minutes = (m1 - m2) % 60;

	return minus;
}

Time Time::operator*(double m) const
{
	Time ret;
	ret.hours = hours * m + minutes * m / 60;
	ret.minutes = (long)(minutes * m) % 60;

	return ret;
}

//void Time::Show() const
//{
//	std::cout << "hours: " << hours
//		<< " minutes: " << minutes << std::endl;
//}

std::ostream& operator<<(std::ostream& os, const Time& t)
{
	os << "Hour: " << t.hours << " Minutes: " << t.minutes << std::endl;
	return os;
}

// 这是一种不借助友元的方法：
//Time operator*(double m, const Time& t)
//{
//	return t * m;
//}