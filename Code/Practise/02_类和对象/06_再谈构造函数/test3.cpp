#include<iostream>

using namespace std; 

class Time{
  public:
    // 成员变量在初始化列表中的初始化顺序只和声明时的顺序有关
    Time(int hour)
        : _min(hour)  // 报错：field '_min' will be initialized after field '_hour'  
        , _hour(_min) // 报错：field '_min' is uninitialized when used here
    {
    }

  private:
    int _hour;
    int _min;
};


int main(void)
{

  return 0;
}
