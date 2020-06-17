// 使用匿名对象作为拷贝构造的参数
// 本来应该先构造匿名对象，然后拷贝构造该对象
// 但是编译器可能进行优化，跳过匿名对象的构造，直接用匿名对象的参数构造该对象
#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

class Age 
{
public:  
  Age(int age = 10)
  {
    this->_age = age;
    cout << "Age() " << age  << endl; 
  }

  
  Age(const Age& a)
  {
    _age = a._age;
    cout << "Age(&) " << endl; 
  }

  void print()
  {
    cout << _age << endl;
  }

  ~Age()
  {}

private:
  int _age;
};


int main(void){

  Age n2(Age(20)); 
  
  n2.print();

  return 0;
}
