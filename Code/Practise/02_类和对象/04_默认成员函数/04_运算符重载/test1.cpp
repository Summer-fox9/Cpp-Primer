#include<iostream>

using namespace std;

class Date{
 public:
   Date(int year = 2020, int month = 06, int day = 14)
   {
     _year = year;
     _month = month;
     _day = day;
   }

  Date(const Date& date)
  {
    _year = date._year;
    _month = date._month;
    _day = date._day;
  }

   ~Date(){

   }

// 为了在类外进行重载，需要把成员变成共有的
// 这样就违反了我们封装的理念
   int _year;
   int _month;
   int _day;
};

// 类外重载
bool operator==(const Date& d1, const Date& d2)
{
  return d1._year == d2._year &&
         d1._month == d2._month &&
         d1._day == d2._day;
}

int main(void){

  Date d1;
  Date d2(d1);

  // 用括号括起来
  cout << (d1 == d2) << endl;

  cout << (32.5 == 32.5) << endl;

  return 0;
}
