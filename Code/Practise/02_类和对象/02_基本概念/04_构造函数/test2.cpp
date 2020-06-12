
// 构造函数可以重载

#include<iostream>

using namespace std;

class Date{
public: 
  Date(int day){
    this->_day = day;
    cout << this->_day << endl;
  }

  Date(){
    cout << "Date()" << endl;
  }

private:
  int _year;
  int _month;
  int _day;
};

int main(void){
  
  // Date d1();// empty parentheses interpreted as a function declaration

  Date d2;
  Date d3(01);

  return 0;
}
