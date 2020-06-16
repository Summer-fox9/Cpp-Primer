#include<iostream>
#include<stdlib.h>

using namespace std;

class Time{
  public:
    Time(int hour)
      : _hour(hour)
    {
      cout << "Time() " << _hour << endl;
    }

  int getHour()
  {
    return _hour;
  }

  private:
    int _hour;
};

class A{
  public:
    A(Time& t)
      : _t(t)
    {
      cout << "A() "  << _a << " " << _t.getHour() << endl;
    }

  // 声明成员变量时设置缺省
  private:
    int _a = 10;
    int* _arr = (int*)malloc(sizeof(int) * 4);
    Time _t = 12; // _t._hour 缺省设置为 12
};

int main(void)
{
  Time t(20);

  A a(t);

  return 0;
}
