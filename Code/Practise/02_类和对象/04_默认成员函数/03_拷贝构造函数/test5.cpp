// 理解什么是浅拷贝
// 浅拷贝指的是在我们复制一个对象时，对象内的资源并没有同时复制一份，只是简单的让新的指针指向了旧的内容
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

class Age 
{
public:  

  Age(const char* name, int age)
  {
    _age = age;
    // 申请资源
    _name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(_name, name);
  }

  Age(const Age& a)
  {
     _name = (char*)malloc(sizeof(char) * (strlen(a._name) + 1));
     strcpy(_name, a._name);
  }
  
  // 我们先把我们写的拷贝构造函数注释起来，调用系统默认的拷贝构造函数
  // 发现：两个对象的成员 _name 指向的内容是一样的
  // 然后取消注释
  // 发现：两个对象的成员 _name 指像了不同的内容，这就说明，对象 1 中的资源也被对象 2 拷贝了一份
  // 这就是深拷贝

  void print()
  {
    cout << _name << " " << _age  << endl;
  }

  void print_address()
  {
    printf("%p\n", _name);
  }


private:
  char* _name;
  int _age;
};


int main(void){

  Age n1("Shepard", 20);
  Age n2(n1); 
  n2.print();

  n1.print_address();
  n2.print_address();

  return 0;
}
