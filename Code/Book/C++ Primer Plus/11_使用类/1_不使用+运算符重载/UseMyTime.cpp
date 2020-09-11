#include<iostream>
#include"MyTime.h"

int main(void)
{
	Time homework(2, 12);
	Time code(3, 55);

	homework.Show();
	code.Show();

	homework.Sum(code).Show();
}