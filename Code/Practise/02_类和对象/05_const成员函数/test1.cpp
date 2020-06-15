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

    Date* operator&()
    {
      return this;
    }

    // 后面的 const 表示参数 this 指向的对象为 const
    // 前面的 const 表示返回的指针指向的是 const 类型的对象
    const Date* operator&() const 
    {
      return this; 
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
