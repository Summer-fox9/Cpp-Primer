#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

class Age 
{
public:  

  Age(int age)
  {
    this->age = age;
  }

  // 调用默认拷贝构造函数

  void print()
  {
    cout << this->age << endl;
  }

  void print_address()
  {
    cout << &this->age << endl;
  }


private:
  int age;
};


int main(void){

  Age n1(20);
  Age n2(n1); 
  n2.print();

  cout << &n1 << endl;
  cout << &n2 << endl;

  n1.print_address();
  n2.print_address();

  return 0;
}
