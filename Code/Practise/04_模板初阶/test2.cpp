#include<iostream>
using namespace std;

template<class T1, class T2, class T3>
class Date
{
  public:
    Date(T1 year, T2 month, T3 day)
        :_year(year)
        ,_month(month)
        ,_day(day)
  {}

    void print();

  private:
    T1 _year;
    T2 _month;
    T3 _day;
};

template<class T1, class T2, class T3>  // 类外实现类的成员函数需要加上泛型的声明，相当于一个模板函数
void Date<T1, T2, T3>::print() // 作用域为 类型+泛型名 
{
  cout << _year << _month << _day << endl;
}


int main(void)
{

  // 模板类不能隐式实例化
  // Date d;// use of class template 'Date' requires template arguments

  Date<int, int, int>d(2020, 6, 20);

  d.print();

  return 0;
}
