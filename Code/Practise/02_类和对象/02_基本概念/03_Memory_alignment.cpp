#pragma pack(1)

#include<iostream>

using namespace std;

class A{
  char a;
  double b;
  int c;
};

int main(void){

  A a;

  cout << sizeof(a) << endl;

  return 0;
}
