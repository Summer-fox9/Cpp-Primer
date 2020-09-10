#include<iostream>

using namespace std;

void test1()
{
	int x = 3;
	// int& rx = x + 3;

	// double& rd = x;
}

double refcube(const double& ra)
{
	return ra * ra * ra;
}

void test2()
{
	double side = 3.0;
	double* pd = &side;
	double& rd = side;
	long edge = 5L;
	double lens[4] = { 2.0, 5.0, 10.0, 12.0 };

	double c1 = refcube(side);
	double c2 = refcube(rd);
	double c3 = refcube(*pd);
	double c4 = refcube(lens[2]);
	double c5 = refcube(edge);
	double c6 = refcube(7.0);
	double c7 = refcube(side + 10.0);
}

void swapr(int& a, int& b)
{
	int temp;

	temp = a;
	a = b;
	b = a;
}

void test3()
{
	long a = 3, b = 5;
	//swapr(a, b);
}

struct sysop
{
	char name[26];
	char quote[64];
	int used;
};

// 返回值为 const，只能在接口中修改变量的值
const sysop& use(sysop& looper)
{
	cout << looper.name << " " << looper.quote << endl;
	++looper.used;
	return looper;
}

void test4()
{
	sysop looper = {
		"Shepard",
		"I'm handsome",
		0
	};
	
	cout << use(looper).name << endl;

	
	const sysop& rlooper = use(looper);
	cout << rlooper.quote << endl;
}

// 书上说默认参数必须设置在函数原型处
char* left(const char* str, int len = 1);

void test5()
{
	const int size = 20;
	char* p = new char[size];

	cout << "Enter a string" << endl;
	cin.get(p, size);
	
	char* pp = left(p);
	cout << pp << endl;

	delete[] pp;

	pp = left(p, 3);
	cout << pp << endl;

	delete[] pp;
	delete[] p;
}

char* left(const char* str, int len)
{
	if (len < 0)
		len = 0;

	char* p = new char[len + 1];
	int i;
	
	// copy charactors
	for (i = 0; i < len && str[i]; i++)
		p[i] = str[i];
	// set the rest of the string to '\0'
	while (i <= len)
		p[i++] = '\0';

	return p;
}

// This function return the first cnt digits of the number num
unsigned long left(unsigned long num, size_t cnt)
{
	if (cnt == 0 || num == 0)
		return 0;

	// 计算出这个数的位数
	size_t digit = 1;
	unsigned long int n = num;

	while (n /= 10)
		digit++;

	if (digit > cnt)
	{
		// 获取 digit 位数字的前 cnt 位
		cnt = digit - cnt;
		while (cnt--)
			num /= 10;
		return num;
	}
	else
		return num;
}

void test7()
{
	unsigned long int ul = 12345678;
	const char* str = "Shepard";

	for (int i = 0; i < 10; i++)
	{
		cout << left(ul, i) << " ";
		char* p = left(str, i);
		cout << p << endl;

		delete[] p;
	}
}

// 函数重载
double add(double a, int b)
{
	return a + b;
}

double add(int a, double b)
{
	return a + b;
}

double add(const char* str, int size)
{
	return size;
}

void test6()
{
	cout << add("hello", 2.0) << endl;
}

//// 模板原型
//template<class T>
//void Swap(T& a, T& b);
//
//
//// 模板定义
//template<class T>
//void Swap(T& a, T& b)
//{
//	T temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//// 模板函数的重载
//template<class T>
//void swap(T* a, T* b, int n);


// 显示具体化（特化）

//// non-template function prototype
//void swap(job&, job&);
//
//// template prototype
//template<class T>
//void swap(T&, T&);
//
//// explicit specialization for the job type
//template<>
//void swap<job>(job&, job&);
////可写作
//template<>
//void swap(job&, job&);

// 注意：Swap 不要写成 swap 这样就和 std::swap 重名了！！！
struct job
{
	char name[40];
	double salary;
	int floor;
};

template<class T>
void Swap(T& a, T& b);

template<>
void Swap<job>(job& j1, job& j2);

void show(job& j);

void test8()
{
	int a = 5, b = 13;

	Swap(a, b);
	// 显示实例化
	Swap<int>(a, b);

	cout << "a = " << a << " b = " << b << endl;

	job j1 = {
		"programmer",
		20000,
		5
	};

	job j2 = {
		"product manager",
		15000,
		100
	};

	Swap(j1, j2);


	show(j1);
	show(j2);
}

template<class T>
void Swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template<>
void Swap<job>(job& a, job& b)
{
	double d;
	int i;

	d = a.salary;
	a.salary = b.salary;
	b.salary = d;

	i = a.floor;
	a.floor = b.floor;
	b.floor = i;
}

void show(job& j)
{
	cout << j.name << " " << j.salary << " " << j.floor << endl;
}

template<class T>
void recycle(T t);

template<class T>
void recycle(T* t);

int a = 10;
recycle(&a);



int main(void)
{
int rat = 5;

int& rodent = rat;
int* const pr = &rat;

test8();

	return 0;
}