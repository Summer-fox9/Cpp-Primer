#include<iostream>
#include"MyTime1.h"

int main(void)
{
	Time homework(2, 12);
	Time code(3, 55);

	homework.Show();
	code.Show();
	
	std::cout << "====== 方法 1 =======" << std::endl;
	(homework + code).Show();
	std::cout << "====== 方法 2 =======" << std::endl;
	homework.operator+(code).Show();

	return 0;
}