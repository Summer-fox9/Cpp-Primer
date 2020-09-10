#include<iostream>
#include"namesp.h"

void testPerson()
{
	using pers::Person;

	Person collector = { "Milo", "RightShift" };
	pers::showPerson(collector);

	std::cout << std::endl;
}

void testDebt()
{
	using debts::Debt;

	Debt golf = { {"Benny", "Goatsniff"}, 120.0 };
	debts::showDebt(golf);

	std::cout << std::endl;
}

void testSum()
{
	using std::cout;
	using std::endl;
	using namespace debts;

	Debt zippy[3];

	for (int i = 0; i < 3; i++)
	{
		getDebt(zippy[i]);
	}

	for (int i = 0; i < 3; i++)
	{
		showDebt(zippy[i]);
	}
	cout << "Total debts: $" << sumDebts(zippy, 3) << endl;
}

int main(void)
{
	testPerson();
	testDebt();
	testSum();

	return 0;
}