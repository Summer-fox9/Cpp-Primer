#include<iostream>

using namespace std; 

class Time{
  public:
    // 用 `explicit` 修饰构造函数，将会禁止单参构造函数的隐式转换
    explicit Time(int hour)
        : _hour(hour)
    {
      cout << _hour << " " << _min << endl;
    }


    void print()
    {
      cout << _hour << " " << _min << endl;
    }

  private:
    int _hour;
    int _min;
};


int main(void)
{
  Time t = 10;// 报错：no viable conversion from 'int' to 'Time' 
  t.print();

  Time t1(0);// 报错：no viable conversion from 'int' to 'Time' 

  t1 = 10;
  t1.print();

  return 0;
}
