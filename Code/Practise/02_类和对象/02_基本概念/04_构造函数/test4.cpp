
// 默认构造函数：1）无参的构造函数
//               2）全缺省的构造函数
// 默认构造函数只能有一个

#include<iostream>

using namespace std;

class Date{
public: 
  Date(){
    cout << "Date" << endl;
  }

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

int main(void){
  
  Date d1;// 报错：call to constructor of 'Date' is ambiguous   

  return 0;
}
