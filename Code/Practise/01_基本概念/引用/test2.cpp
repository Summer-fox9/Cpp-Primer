#include<iostream>

using namespace std;

void add(int& a, int& b, int& c){

  c = a + b;
}

int main(void){
  
  int a = 3;
  int b = 2;
  int c;

  add(a, b, c);

  cout << c << endl;

  return 0;
}
