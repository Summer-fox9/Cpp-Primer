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

  // 其形参比操作数数目少1，操作符有一个默认的形参this
  // bool operator==(Date* this, const Date& d);
  bool operator==(const Date& d)
  {
    return _year == d._year &&
           _month == d._month &&
           _day == d._day;
  }

 // 封装不会被打破 
 private:
   int _year;
   int _month;
   int _day;
};


int main(void){

  Date d1;
  Date d2(d1);

  // 两种调用方式效果是一样的
  cout << (d1 == d2) << endl;
  cout << d1.operator==(d2) << endl;

  return 0;
}
