#include<iostream>

using namespace std;

class Time
{
  friend class Date;
  
  public:
    Time(int hour = 1, int min = 1, int sec = 1)
        : _hour(hour)
        , _min(min)
        , _sec(sec)
    {}

  private:
    int _hour;
    int _min;
    int _sec;
};

class Date
{
  public:
    Date(int year = 2020, int month = 6, int day = 15)
        : _year(year)
        , _month(month)
        , _day(day)
    {}

    void setTimeOfDate(int hour, int min, int sec)
    {
      // 直接访问 Time 类中的 private 成员
      _t._hour = hour;
      _t._min = min;
      _t._sec = sec;
    }

    void print()
    {
      cout << _year << "-" << _month << "-" << _day << " " 
        << _t._hour << ":" << _t._min << ":" << _t._sec << endl; 
    }

  private:
    int _year;
    int _month;
    int _day;
    Time _t;
};


int main(void)
{
  Date d; 

  d.setTimeOfDate(15, 35, 30);
  d.print();

  return 0;
}
