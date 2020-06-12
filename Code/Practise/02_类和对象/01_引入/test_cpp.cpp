#include<iostream>
#include<cstring>

using namespace std;

struct Student{
  char _name[20];
  char _gender[10];
  int _age;

  void set_student_info(const char name[], const char gender[], int age)
  {
       strcpy(_name, name); 
       strcpy(_gender, gender);
      _age = age;

  }

  void print_student_info(){
    cout << "学生信息："  << _name << " " << _gender << " " << _age << endl;
  }
};

int main(void){
  
  struct Student s;

  char name[20], gender[10];
  int age;

  memset(name, 0x0, sizeof(name));
  memset(gender, 0x0, sizeof(gender));

  cout << "请输入学生姓名：" << endl;
  cin >> name ;
  cout << "请输入学生性别：" << endl;
  cin >> gender;
  cout << "请输入学生年龄：" << endl;
  cin >> age;


  s.set_student_info(name, gender, age);
  s.print_student_info();

  return 0;
}
