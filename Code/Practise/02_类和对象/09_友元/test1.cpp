#include<iostream>

using namespace std; 

class Date{
  // friend + 函数原型
  // 写在类中的任何位置都可以
  friend ostream& operator<<(ostream& _cout, const Date& d);
  friend istream& operator>>(istream& _cin, Date& d);

  public:
    Date(int year = 2020, int month = 6, int day = 15)
        : _year(year)
        , _month(month)
        , _day(day)
    {}

  private:
    int _year;
    int _month;
    int _day;
};

// 在类外定义
ostream& operator<<(ostream& _cout, const Date& d)
{
  _cout << d._year << " " << d._month << " " << d._day;  
  return _cout;
} 

istream& operator>>(istream& _cin, Date& d)
{
  _cin >> d._year >> d._month >> d._day; 
  return _cin;
}

int main(void)
{
  Date d; 

  cin >> d;
  cout << d << endl;
  

  return 0;
}
