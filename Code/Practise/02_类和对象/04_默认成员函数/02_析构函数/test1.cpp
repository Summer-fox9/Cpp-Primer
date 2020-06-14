#include<iostream>
#include<cstring>
#include<stdlib.h>
 using namespace std; 

class String{
public:
  String(const char* str)
  {
    this->str = (char*)malloc(strlen(str) + 1);
    strcpy(this->str, str);
  }

  ~String()
  {
    if(this->str)
    {
      free(this->str);
      this->str = nullptr;
    }
    cout << "~String()" << endl;
  }

  void print()
  {
    cout << this->str << endl;
  }

private:
  char* str;
 };


 int main(void){

  const char* str = "hello";
  String s(str);

  s.print();

   return 0;
 }
