#include<iostream>
#include"MyTime.h"

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
Time Time::Sum(const Time& t) const
{
	Time add;
	add.minutes = minutes + t.minutes;
	add.hours = hours + t.hours;
	add.hours += add.minutes / 60;
	add.minutes %= 60;

	return add;
}
void Time::Show() const
{
	std::cout << "hours: " << hours
		<< " minutes: " << minutes << std::endl;
}