// 1. const对象可以调用非const成员函数吗？
// 2. 非const对象可以调用const成员函数吗？
// 3. const成员函数内可以调用其它的非const成员函数吗？
// 4. 非const成员函数内可以调用其它的const成员函数吗？ 

#include<iostream>

using namespace std;

class Date{
  public:
    Date(int year, int month, int day)
    {
      _year = year;
      _month = month;
      _day = day;
    }

  // 等价于：print(Date* const this);
  void print()
  {
    cout << _year << _month << _day << endl;
    fun1();
  }

  // 等价于 print1(const Date* const this);
  void print1() const 
  {
    cout <<  _year << _month << _day << endl;
    //fun();
  }

  void fun()
  {
    cout << "func()" << endl;
  }

  void fun1() const 
  {
    cout << "func() const" << endl; 
  }

  private:
    int _year;
    int _month;
    int _day;
};


int main(void)
{
  const Date d1(2020, 6, 15);

  return 0;
}
