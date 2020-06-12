#include<stdio.h>
#include<string.h>

struct Student
{
  char _name[20];
  char _gender[10];
  int _age;

  // 因为 C 语言不能在结构中定义函数，我们使用函数指针来表示学生类中有这么一个函数
  void (*set_student_info)(struct Student* s, const char name[], const char gender[], int age);
  void (*print_student_info)(struct Student* s);

};

void set_student_info(struct Student* s,  const char name[], const char gender[], int age)
{
   strcpy(s->_name, name); 
   strcpy(s->_gender, gender);
   s->_age = age;
}

void print_student_info(struct Student* s){
  printf("学生信息：%s  %s  %d\n", s->_name, s->_gender, s->_age);
}

int main(void){

  struct Student s;

  char name[20], gender[10];
  int age;

  memset(name, 0x0, sizeof(name));
  memset(gender, 0x0, sizeof(gender));

  printf("请输入学生姓名：");
  scanf("%s", name);
  printf("请输入学生性别：");
  scanf("%s", gender);
  printf("请输入学生年龄：");
  scanf("%d", &age);

  // 初始化 s 的函数指针
  s.set_student_info = set_student_info;
  s.print_student_info = print_student_info;
  
  s.set_student_info(&s, name, gender, age);
  s.print_student_info(&s);

  return 0;
}
