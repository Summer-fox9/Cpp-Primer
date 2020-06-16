#include<iostream>

using namespace std;

enum E{
  BLACK,
  WHITE,
};

class C;
class A{
  public:
    A()
    {}

    class B{
      public:
        void print(const A& a)
        {
          cout << a._a << endl;
          cout << a._e << endl; 

          // 直接访问 static 成员
          cout << _s << endl;

        }

      private:
        int _b;
    };

    void print(const B& b)
    {
      // cout << b._b  << endl;// 报错：'_b' is a private member of 'A::B' 
    }


  private:
    int _a = 10;
    static int _s;
    E _e = WHITE; 
    
};

int A::_s = 0;

int main(void)
{
  A a;
  A::B b;

  b.print(a);

  return 0;
}
