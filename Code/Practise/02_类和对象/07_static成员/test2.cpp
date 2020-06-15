
#include<iostream>

using namespace std; 

class A{
  public:
    A(){_cnt++;} // 构造函数
    A(const A& a){_cnt++;}
    
    static int countObj()
    {
      // 静态函数不能访问非静态的成员变量和函数，因为 static 内没有 this 指针
      // cout << _a << endl;
      // print();
      return _cnt;
    }

    void print()
    {
      // 非静态函数可以访问静态的成员变量和函数
      cout << _cnt << endl;
      countObj();
    }

  // static 也有访问权限的区别
  private:
    static int _cnt;
    int _a;
};

// static 成员变量必须在类外初始化，不需要加 static 
int A::_cnt = 0;

int main(void)
{
  A a, b;

  cout << a.countObj() << endl;
  cout << A::countObj() << endl;

  return 0;
}
