#include<iostream>
#include<string>

using namespace std;

// 构造
void test1()
{
/*
default (1)
string();

copy (2)
string (const string& str);

substring (3)
string (const string& str, size_t pos, size_t len = npos);

from c-string (4)
string (const char* s);

from sequence (5)
string (const char* s, size_t n);

fill (6)
string (size_t n, char c);
*/

	string s1;

	string s2("123");
	string s3 = "123"; // 单参构造函数

	string s4("0123456789", 5); // "01234"

	string s5(s4);

	// 索引为 2 取 2 个字符
	string s6(s4, 2, 2); // "23"

	string s7(10, 'a'); // 十个 'a'
}

// 赋值重载
void test2() 
{
	/*
string (1)
string& operator= (const string& str);
c-string (2)
string& operator= (const char* s);
character (3)
string& operator= (char c);
	*/
	
	string s = "123";
	string s2 = "bbb";

	s = "aaa";
	s = s2;
	s = 'a';
}

// 迭代器
void test3()
{
	string str("0123456789");
	
	// 可读可写迭代器
	// iterator
	// begin 指向字符串第一个元素
	// end 指向最后一个元素的下一个
	// [begin(), end()) 左闭右开
	for (string::iterator it = str.begin(); it != str.end(); it++)
	{
		cout << *it << endl;
		// *it = ' ';
	}

	// 反向迭代器
	// reverse_iterator
	// [rend(), rbegin()) 左闭右开
	// rbegin() 指向最后一个元素的下一个位置。先解引用前一个元素，再++
	for(string::reverse_iterator it = str.rbegin(); it != str.rend(); it++)
		cout << *it << endl;

	// 只读迭代器
	// const_iterator

	for (string::const_iterator cit = str.cbegin(); cit != str.cend(); cit++)
	{
		// *cit = ' '; // error 不可修改
	}

	// 只读反向迭代器
	// string::const_reverse_iterator
	// 可以使用 auto
	for (auto crit = str.crbegin(); crit != str.crend(); crit++)
		;
}

void printString(const string& str)
{
	// const 类型的对象只能调用 const 接口
	string::const_iterator cit = str.cbegin();
}

// Capacity
void test4()
{
	string str("0123456789");

	// size/lenth: 返回有效字符个数
	cout << str.size() << endl;
	cout << str.length() << endl;
	
	// capacity 可以存放的最大有效字符个数
	cout << str.capacity() << endl;
	
	// max_size: Returns the maximum length the string can reach.
	cout << str.max_size() << endl;
	
	// clear: Erases the contents of the string, which becomes an empty string
	// str.clear();
	

	// resize:Resizes the string to a length of n characters. 
	// void resize (size_t n); 
	// If n is smaller than the current string length, the current value is shortened to its first n character, removing the characters beyond the nth.
	// void resize(size_t n, char c);
	// If n is greater than the current string length, the current content is extended by inserting at the end as many characters as needed to reach a size of n. If c is specified, the new elements are initialized as copies of c, otherwise, they are value-initialized characters (null characters).
	
	// n > size, size 增加，
	// 如果 size > capacity, 扩容（类似 realloc）
	// 如果 size < capacity, 只修改 size 
	// 多余空间用 第二个参数表示的字符替代；如果缺省第二个参数，用 NUL（ASCII 为 0）替代
	str.resize(str.size() + 10, 'a');
	cout << str << endl;
	cout << str.size() << endl;
	cout << str.capacity() << endl;

	// n < size ，只修改 size，截断字符串
	str.resize(str.size() - 10);
	cout << str << endl;
	cout << str.size() << endl;
	cout << str.capacity() << endl;


	// reserve 
	// void reserve (size_t n = 0)
	// PJ 版 string 第一次增容 2 倍，之后 1.5 增容

	cout << str << endl;
	cout << str.size() << endl;
	cout << str.capacity() << endl;

	str.reserve(40);
	cout << str << endl;
	cout << str.size() << endl;
	cout << str.capacity() << endl;
	
	str.reserve(5);
	cout << str << endl;
	cout << str.size() << endl;
	cout << str.capacity() << endl;

	// Note that the resulting string capacity may be equal or greater than n.

	// Shrink to fit: Requests the string to reduce its capacity to fit its size.
	// void shrink_to_fit()
	// 如果 capacity 远大于 size 可以减小空间，避免浪费
	cout << "=========================" << endl;
	str.shrink_to_fit();
	cout << str.size() << endl;
	cout << str.capacity() << endl;

	// empty
	// bool empty() const;
	cout << str.empty() << endl;	
}

int main(void)
{
	//test3();
	test4();
}