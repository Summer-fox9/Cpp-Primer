// 实现一个类，计算中程序中创建出了多少个类对象

#include<iostream>

using namespace std; 

class A{
  public:
    A(){cnt++;} // 构造函数
    A(const A& a){cnt++;}
    
    static int countObj()
    {
      return cnt;
    }

  // static 也有访问权限的区别
  private:
    static int cnt;
};

// static 成员变量必须在类外初始化，不需要加 static 
int A::cnt = 0;

int main(void)
{
  A a,b,c;
  A d = a;
  cout << A::countObj() << endl;
  return 0;
}
