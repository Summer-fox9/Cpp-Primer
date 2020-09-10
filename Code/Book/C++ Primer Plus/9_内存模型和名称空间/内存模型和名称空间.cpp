#include<new>
#include<iostream>
#include<stdio.h>

using namespace std;

const int N = 5;

void test1()
{
	char* buffer = new char[256];

	double* p = new(buffer) double[N];

	cout << "&buffer = " << (void*)buffer << endl;

	cout << "-------------------" << endl;

	for (int i = 0; i < N; i++)
	{
		p[i] = 1000 + i * 20;
		cout << "p[" << i << "] = " << p[i] << "µØÖ·£º" << &p[i] << endl;
	}

	cout << "-------------------" << endl;

	double* p1 = new(buffer) double[N];
	for (int i = 0; i < N; i++)
	{
		p1[i] = 2000 + i * 20;
		cout << "p1[" << i << "] = " << p1[i] << "µØÖ·£º" << &p1[i] << endl;
	}
	
	cout << "-------------------" << endl;

	double* p2 = new(buffer + N * sizeof(double)) double[N];
	for (int i = 0; i < N; i++)
	{
		p2[i] = 3000 + i * 20;
		cout << "p2[" << i << "] = " << p2[i] << " µØÖ·£º" << &p2[i] << endl;
	}
	

	delete[] buffer;
}

extern "C" void test2()
{
	char* buffer = (char*)malloc(sizeof(char) * 256);

	printf("buffer = %p &buffer =  %p\n", buffer, &buffer);
	
	int a = 10;

	printf("&a = %p\n", &a);

	char buffer2[256] = "Hello World";

	printf("buffer2 = %p &buffer2 =  %p\n", buffer2, &buffer2);

	free(buffer);
}

extern "C" void test3()
{
	int array[10] = { 0 };

	printf("array = %p, &array = %p\n", array, &array);

	//printf("array: %s\n", typeid(array).name());
	//printf("&array: %s\n", typeid(&array).name());

	printf("array + 1 = %p, &array + 1 = %p\n", array + 1, &array + 1);
}
	
//namespace Jill
//{
//	double fetch;
//	double bucket(double n){}
//}
//char fetch;
//void test4()
//{
//	using Jill::fetch; // put fetch into local namespace
//	// int fetch;	   // Error! Already have a local fetch
//	cin >> fetch;	   // read a value into Jill::fetch;
//	cin >> ::fetch;     // read a value into global fetch
//}

namespace Jill
{
	double fetch;
	double bucket(double n) { cout << n << endl; }
	struct Hill { int a; };
}

char fetch;
void test5()
{
	using namespace Jill;	// import all namespace names
	Hill Thrill;			// create a type Jill::Hill structure
	double water = bucket(2);
	double fetch;			// not an error ! hides Jill::fetch
	cin >> fetch;			// local fetch
	cin >> ::fetch;	   	    // global fetch
	cin >> Jill::fetch;		// Jill::fetch
}

//int foom()
//{
//	Hill top; // Error!
//	Jill::Hill creat;// valid
//}

int main(void)
{
	test5();

	return 0;
}