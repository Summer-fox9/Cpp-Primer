#include"Date.h"

int main(void)
{
	Date::menu();
	int choice, day;
	Date d1, d2;

	while (1)
	{
		cout << "请输入您的选择：";
		cin >> choice;

		//cout << "*          " << "1. 计算日期差" << endl;
		//cout << "*          " << "2. 推算日期（向后）" << endl;
		//cout << "*          " << "3. 推算日期（向前）" << endl;
		//cout << "*          " << "4. 比较日期大小" << endl;
		//cout << "*          " << "0.     退出" << endl;
		switch(choice)
		{
		case 0: 
			Date::exitDate(); break;

		case 1:			
			d1 = Date::newDate();
			d2 = Date::newDate();

			d1.daysBetweenTwoDates(d2);
			break;

		case 2:
			d1 = Date::newDate();
			cout << "天数" << endl;
			cin >> day;

			d1.inferDateBack(day);
			break;

		case 3:
			d1 = Date::newDate();
			cout << "天数" << endl;
			cin >> day;

			d1.inferDateFront(day);
			break;

		case 4:
			d1 = Date::newDate();
			d2 = Date::newDate();

			d1.compareDate(d2);
			break;
		}
		
	}
	
	return 0;
}