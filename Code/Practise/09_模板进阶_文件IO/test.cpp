#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<cstring>

using namespace std;

template<class T>
T Add(T& t1, T& t2)
{
	return t1 + t2;
}

/**
 * 函数模板特化
 * const char*& t1 这个 & 符号必须要写，要和模板保持一致
 */
template<>
char* Add<char*>(char*& t1, char*& t2)
{
	char* ret = new char[strlen(t1) + strlen(t2) + 1];
	strcpy(ret, t1);
	strcat(ret, t2);
	
	return ret;
}

/**
 * 特化写起来很麻烦，我们可以直接定义一个 char* 专属的 Add 函数，
 * 编译器依然优先调用此函数
 */
 char* Add(char* t1, char* t2)
 {
 	char* ret = new char[strlen(t1) + strlen(t2) + 1];
 	strcpy(ret, t1);
 	strcat(ret, t2);
 	
 	return ret;
 }

 /**
 * 模板参数：
 *   - 非类型模板参数
 *      1. 浮点数、类对象以及字符串是不允许作为非类型模板参数的。
 *		2. 非类型的模板参数必须在编译期就能确认结果。
 *   - 类型模板参数
 */

 template<class T, size_t N = 10>
 class Array
 {
 private:
	 T _array[N];
 };

 /**
 * 类模板特化
 * 全特化
 * 偏特化
 */

template<class T1, class T2>
class B
{
public:
	B()
	{
		cout << "<class T1, class T2>" << endl;
	}
};

// 全特化
template<>
class B<int, double>
{
public:
	B()
	{
		cout << "<int, double>" << endl;
	}
};

// 偏特化：部分特化
template<class T1>
class B<T1, double>
{
public:
	B()
	{
		cout << "<T1, double>" << endl;
	}
};

// 偏特化：限制模板
template<class T1, class T2>
class B<T1&, T2&>
{
public:
	B()
	{
		cout << "<T1&, T2&>" << endl;
	}
};

void test1()
{
	int a = 1, b = 2;
	int rst1 = Add(a, b);
	
	char* p1 = new char[7];
	char* p2 = new char[6];
	strcpy(p1, "Hello ");
	strcpy(p2, "World");
	char* rst2 = Add(p1, p2);
}

void test2()
{
	B<char, string> b1;
	B<int, double> b2;
	B<char, double> b3;
	B<char&, string&> b4;
}

/**
 * 问题 √
 * http://cplusplus.com/reference/ostream/ostream/operator%3C%3C/
 * http://cplusplus.com/reference/ostream/ostream/operator-free/
 */
void test3()
{
	// 会输出地址,因为 ostream 中的 operator<< 没有重载 C 串类型
	cout.operator<<("123").operator<<(endl);

	operator<<(cout, "123");
	cout.operator<<(4).operator<<(endl);
	// 等价于
	cout << "123" << 4 << endl;
}

#include<fstream>

// 读文件
void test4()
{
	ifstream ifs("./text.txt");
	if (!ifs.is_open())
	{
		cout << "文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	
	/**
	 *  文件中的内容是 Hello World！，而 >> 从文件中读取的是 Hello
	 *	>> 在遇到空字符时会结束读取
	 */
	char str1[100];
	ifs >> str1;
	cout << str1 << endl;

	/**
	 *	getline 函数可以读取整行。第二个参数制定最大读取的字节数
	 *	getline 会给读出的字符串加上空字符，空字符算在读入的总的字符数中
	 */
	ifstream ifs2("./text.txt");
	char str2[100];
	// 注意最后一个 ！没有读入，因为空字符占用了 1 个字节
	ifs2.getline(str2, 12); 
	cout << str2 << endl;
}

// 写文件
void test5()
{
	// 如果文件不存在，新建一个文件
	ofstream ofs("read.txt");
	if (!ofs.is_open())
	{
		cout << "ofs 文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	ofs << "Hello " << "World!" << endl;
	// 读文件前先关闭文件
	ofs.close();

	// 重新打开文件
	ifstream ifs("read.txt");
	if (!ifs.is_open())
	{
		cout << "ifs 文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	char str[100];

	ifs >> str;
	// Hello 遇到空格停止
	cout << str << endl;

	// 这里也可以不显示调用 close 因为 ifs 销毁时会调用析构，其中会调用 close 
	ifs.close();
}

struct Student
{
	char name[20];
	int age;
	char gender[5];
};

// 二进制读写文件：效率高，可读性差
void test6()
{
	ofstream ofs("binary.txt");
	if (!ofs.is_open())
	{
		cout << "ofs 文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	struct Student s = { "Shepard Wang", 20, "man" };
	// 注意类型转换，参数要求是 char* 类型
	ofs.write((char*)&s, sizeof(s));
	ofs.close();

	ifstream ifs("binary.txt");
	if (!ifs.is_open())
	{
		cout << "ifs 文件打开失败" << endl;
		exit(EXIT_FAILURE);
	}
	struct Student s2;
	ifs.read((char*)&s2, sizeof(s2));
	cout << s2.name << " " << s2.age << " " << s2.gender << endl;
	ifs.close();
}

// C++ 文本文件
void test6p()
{
	// 文本格式写文件
	ofstream text("text.cpp.txt");
	
	struct Student s = { "Shepard_Wang", 20, "man" };

	text << s.name << " " << s.age << " " << s.gender << endl;

	text.close();

	ifstream text2("text.cpp.txt");
	
	struct Student s2;

	text2 >> s2.name >> s2.age >> s2.gender;

	text2.close();
}

void test6cpppp()
{
	ofstream text("binary.cpp.txt");

	struct Student s = { "Shepard_Wang", 20, "man" };

	text.write((char*)&s, sizeof(s));

	text.close();

	ifstream text2("binary.cpp.txt");

	struct Student s2;

	text2.read((char*)&s2, sizeof(s2));

	text2.close();
}

// C 语言版文本文件
void test6pp()
{
	FILE* fp = fopen("text.c.txt", "w+");

	struct Student s = { "ShepardWang", 20, "man" };

	fprintf(fp, "%s %d %s", s.name, s.age, s.gender);

	fclose(fp);

	FILE* fp2 = fopen("text.c.txt", "r");

	struct Student s2;
	
	// 读取出现错误
	// s2.name 是 Shepard，遇到空格结束读取
	fscanf(fp2, "%s%d%s", s2.name, &s2.age, s2.gender);

	fclose(fp2);
}

// C 语言版二进制文件
void test6ppp()
{
	FILE* fp = fopen("binary.c.txt", "w+");

	struct Student s = { "ShepardWang", 20, "man" };

	fwrite(&s, sizeof(s), 1, fp);

	fclose(fp);

	FILE* fp2 = fopen("binary.c.txt", "r");

	struct Student s2;

	fread(&s2, sizeof(s2), 1, fp2);

	fclose(fp2);
}

#include<sstream>
#include<stdlib.h>

// stingstream: 把非字符串数据转成字符串形式的数据
void test7()
{
	/**
	 *	C 语言将非字符串转换为字符串的方法
	 *	1. 使用itoa()函数
	 *	2. 使用sprintf()函数
	 */
	
	int x = 2;
	char str1[10], str2[10];
	// 第三个参数是将 x 以十进制的形式转换为字符串
	_itoa(x, str1, 10);
	sprintf(str2, "%d", x);
	cout << str1 << " " << str2 << endl;

	stringstream ss;
	ss << x;
	string str = ss.str();
	cout << str << endl;
	ss.str("");
	ss.clear(); // 清空状态位
	double y = 2.5;
	ss << y;
	cout << ss.str() << endl;
}

int main(void)
{
	test6cpppp();

	return 0;
}