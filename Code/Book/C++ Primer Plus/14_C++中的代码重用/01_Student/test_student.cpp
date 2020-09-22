#include"student.h"
#include<iostream>

#define STUDENT_NUM 3
#define QUIZZES 3

int main(void)
{
	Student stu[STUDENT_NUM]{Student(QUIZZES), Student(QUIZZES), Student(QUIZZES)};

	std::cin >> stu[0] >> stu[1] >> stu[2];

	for (int i = 0; i < STUDENT_NUM; i++)
	{
		std::cout << stu[i];
		std::cout << stu[i].Average() << std::endl;
	}

	return 0;
}