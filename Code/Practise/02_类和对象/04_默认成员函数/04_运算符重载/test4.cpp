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


  void print()
  {
    cout << _year << _month << _day << endl;
  }

 private:
   int _year;
   int _month;
   int _day;
};


int main(void){

  Date d1(1010, 10, 01);
  Date d2;

  d2 = d1;

  d2.print();

  return 0;
}
