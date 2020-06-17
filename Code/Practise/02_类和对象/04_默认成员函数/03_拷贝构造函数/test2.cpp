// 如果类中有资源，需要显示定义拷贝构造函数完成清理
//
// 如果使用默认的拷贝构造函数，编译通过但是运行时段错误

#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

class Name
{
public:  
  Name(const char* str)
  {
    this->str = (char*)malloc(strlen(str) + 1);
    strcpy(this->str, str);
    
  }

  // 尝试调用默认拷贝构造

  void print()
  {
    cout << this->str << endl;
  }

  ~Name()
  {
    free(this->str);
    this->str = nullptr;
  }

private:
  char* str;
};


int main(void){

  Name n1("Shepard");
  Name n2(n1); 
  n2.print();

  return 0;
}
