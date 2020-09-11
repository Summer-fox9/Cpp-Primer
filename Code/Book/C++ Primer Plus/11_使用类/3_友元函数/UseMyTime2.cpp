#include<iostream>
#include"MyTime2.h"

int main(void)
{
	Time homework(2, 12);
	Time code(3, 55);

	//homework.Show();
	//code.Show();
	//
	//(homework - code).Show();
	//(homework * 2).Show();

	// (2 * homework).Show(); // ÓÑÔªÒýÈë
	
	std::cout << (2 * homework) << std::endl;
	std::cout << (homework * 2) << std::endl;
	std::cout << (homework + code) << std::endl;

	return 0;
}