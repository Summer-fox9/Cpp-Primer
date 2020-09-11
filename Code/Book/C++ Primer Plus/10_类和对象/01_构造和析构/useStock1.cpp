#include<iostream>
#include"Stock1.h"

int main(void)
{
	using std::cout;
	using std::ios_base;
	// #.## format
	cout.precision(2);
	cout.setf(ios_base::fixed, ios_base::floatfield);
	cout.setf(ios_base::showpoint);

	cout << "====== Use constructor to create new objects ======= \n ";
	Stock stock1("doudou", 12, 20.0);
	stock1.show();
	/*
	 * 下面的语句看似是赋值，实际上是构造
	 * 如果既可以通过初始化也可以通过赋值来设置对象的值，则应该采用初始化
	 * 通常这种方式效率更高
	 */
	Stock stock2 = Stock("diandian", 20, 13);
	stock2.show();

	cout << "\n====== Assigning stock1 to stock2 ======= \n";
	stock2 = stock1;
	stock1.show();
	stock2.show();
	
	/*
	 * 先用构造函数来创建一个匿名的临时对象，然后将该临时对象复制到 stock1 中去
	 * 临时对象可能会被立即删除，也可能会等一段时间（析构函数也会过一段时间才调用）
	 */
	cout << "\n===== Using a constructor to reset an object ====== \n";
	stock1 = Stock("Shepard", 10, 50.0);
	stock1.show();
	
	/*
	 * 注意到 stock2 的析构函数先被调用。
	 * 这是由于自动变量存放在栈中，因此最后创建的对象会最先被删除。
	 */
	return 0;
}

/*  
输出：
====== Use constructor to create new objects ====== =
constructor called
Company : doudou Shares : 12 Share Price : 20.00 Total Worth : 240.00
constructor called
Company : diandian Shares : 20 Share Price : 13.00 Total Worth : 260.00

====== Assigning stock1 to stock2 ====== =
Company : doudou Shares : 12 Share Price : 20.00 Total Worth : 240.00
Company : doudou Shares : 12 Share Price : 20.00 Total Worth : 240.00

==== = Using a constructor to reset an object ======
constructor called
Bye, Shepard!
Company : Shepard Shares : 10 Share Price : 50.00 Total Worth : 500.00
Bye, doudou!
Bye, Shepard!
*/