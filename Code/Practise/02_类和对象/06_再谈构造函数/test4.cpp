#include<iostream>

using namespace std; 

class Time{
  public:
    Time(int hour)
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
  // 只有单参构造函数才有隐式转换
  // Time t = (10, 20);

  // 首先创建一个匿名对象，匿名对象以 10 为参数调用构造函数
  // 然后调用拷贝构造，完成对 t 的构造
  // 因为我们没有初始化 _min 所以它是一个随机值
  Time t = 10;
  t.print();

  Time t1(0);
  // 10 会转换为 Time 类型，然后再调用赋值运算符重载
  t1 = 10;
  t1.print();

  return 0;
}
