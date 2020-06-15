#include<iostream>

using namespace std; 

class Time{
  public:
    Time(int hour)
      : _hour(hour)
    {
      cout << hour << endl;
    }

  private:
    int _hour;
};


class Date{
  public:
    Date(int year = 2020, int month = 6, int day = 15)
      // 每个成员变量在初始化列表中只能出现一次
      // 尽量使用初始化列表初始化，因为编译器一定会先使用初始化列表初始化
        : _year(year)
        , _month(month)
        , _day(day)
        , _a(_year) // 引用类型初始化
        , _b(20)    // const 类型变量初始化
        , _t(10)    // 自定类型（没有默认构造）初始化
  {
    cout << "_a" << _a << "_b"  <<  _b << endl;
  }    

  void print()
  {
    cout << _year << _month << _day << endl;
  }

  // 变量声明的地方：
  private:
      int _year;
      int _month;
      int _day;
      int& _a; // 引用类型必须在定义时初始化
      const int _b;
      Time _t;
};


int main(void)
{
  Date d;
  d.print();

  return 0;
}
