#include<iostream>

using namespace std; 

class Date{
  public:
    Date(int year = 2020, int month = 6, int day = 15)
      // 初始化列表，用 : 开始 用 , 分隔成员
      : _year(year)
      , _month(month)
      , _day(day)
    {}   

  void print()
  {
    cout << _year << _month << _day << endl;
  }

  private:
      int _year;
      int _month;
      int _day;
};


int main(void)
{
  Date d;
  d.print();

  return 0;
}
