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
    cout << this->str << " Name()" << endl;
  }

  Name(const Name& name)
  {
    this->str = (char*)malloc(strlen(name.str) + 1);
    strcpy(this->str, name.str);
    cout << "Name(&)" << endl;
  }

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
