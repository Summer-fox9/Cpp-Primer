
// 自定义类型的构造函数总会被调用

#include<iostream>

using namespace std;

class Date{
public: 

  Date(int year = 2020, int month = 06, int day = 12){
    this->_year = year;
    this->_month = month;
    this->_day = day;
    cout << this->_year << " " << this->_month << " " << this->_day << endl;
  }


private:
  int _year;
  int _month;
  int _day;
};

class Time{
public: 
  Time(){
    cout << "Time()" << endl;
  }

  Date d;
};

int main(void){
  
  Time T;

  return 0;
}
