#include<iostream>

using namespace std;

int main(void){
  const int a = 10;
  // int& ra = a; // 不报错，类型不兼容
  const int& ra = a;
  const float& rra = a;

  const double b = 3.14;
  const int& rb = b;

  double c = 10;
  // int& rc = c;
  // int& d = 10;
  double& rc = c;
  const int& rrc = c;

  cout << ra << endl;// 10
  cout << rra << endl;// 10 
  cout << rb << endl; // 3 
  cout << rrc << endl; // 10 
}
