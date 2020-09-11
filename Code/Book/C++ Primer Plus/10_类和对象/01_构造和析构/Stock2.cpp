#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include"Stock1.h"

// default constructor
Stock::Stock()
{
	// 打印提示并不是构造和析构的常规功能，这里有助于初学者直观的看到构造和析构的调用
	std::cout << "default constructor called" << std::endl;
	std::strcpy(company, "no name");
	shares = 0;
	share_val = 0;
	total_val = 0;
}

Stock::Stock(const char* co, int n, double pr)
{
	std::cout << "constructor called" << std::endl;
	std::strncpy(company, co, 29);
	company[29] = '\0';

	if (n < 0)
	{
		std::cerr << "Number of shares can't be negative " <<  company << " shares set to 0" <<std::endl;
		shares = 0;

	}
	shares = n;
	share_val = pr;
	set_tot();
}

// destructor
Stock::~Stock()
{
	std::cout << "Bye, " << company << "!\n";
}

void Stock::buy(int num, double price)
{
	if (num < 0)
	{
		std::cerr << "Number of share purchase can't be negative ! "
			<< "Transaction is aborted.\n";
	}
	else
	{
		shares += num;
		share_val = price;
		set_tot();
	}
}
void Stock::sell(int num, double price)
{
	using std::cerr;
	if (num < 0)
	{
		cerr << "Number of share sold can't be negative ! "
			<< "Transaction is aborted.\n";
	}
	else if (num > shares)
	{
		cerr << "You can't sell more than you have !" 
			<< "Transaction is aborted.\n";
	}
	else
	{
		shares -= num;
		share_val = price;
		set_tot();
	}

}
void Stock::update(double price)
{
	share_val = price;
	set_tot();
}
void Stock::show()
{
	std::cout << "Company: " << company
		<< " Shares: " << shares
		<< " Share Price: " << share_val
		<< " Total Worth: " << total_val << std::endl;
}