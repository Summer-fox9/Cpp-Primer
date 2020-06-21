// 学习 string
// 参考网站：http://cplusplus.com/reference/string/string/?kw=string

#include<iostream>
#include<string>

using namespace std;

// operator[]: Returns a reference to the character at position pos in the string.
// char& operator[] (size_t pos);
// const char& operator[] (size_t pos) const;
// 可读可写
// 无异常 If pos is equal to the string length and the string is const-qualified, the function returns a reference to a null character ('\0').
void test1()
{
	string str("0123456789");
	
	cout << str.operator[](0) << endl;
	cout << str[0] << endl;

	for (int i = 0; i < str.size(); i++)
		cout << str[i] << endl;
}

// at: 和 operator[] 功能类似
// char& at(size_t pos);
// const char& at(size_t pos) const;
// 有异常
void test2()
{
	string str("0123");

	cout << str.at(0) << endl;

}

// 3 种遍历方式：
// 1.迭代器
// 2.operator[](at)
// 3.范围 for
void test3()
{
	string str("0123456789");
	
	// 范围 for 通过迭代器实现，如果自定义类型要使用范围 for ，那么需要实现 begin，end 函数
	// 所以严格来说只有两种遍历方式

	// 不可修改内容
	for (const auto& ch : str)
		cout << ch << " ";
	cout << endl;

	// 可以修改
	for (auto& ch : str) {
		ch = 'x';
		cout << ch << " ";
	}
	cout << endl;
}

// back/front: Returns a reference to the last character of the string.
// This function shall not be called on empty strings. 
void test4()
{
	string str("0123456789");

	cout << str.front() << " " << str.back() << endl; // 0  9
}

// append: Extends the string by appending additional characters at the end of its current value
//string(1)
//string& append(const string& str);
//substring(2)
//string& append(const string& str, size_t subpos, size_t sublen);
//c - string(3)
//string & append(const char* s);
//buffer(4)
//string& append(const char* s, size_t n);
//fill(5)
//string& append(size_t n, char c);
void test5()
{
	string s;

	s.push_back('a');
	s.append(1, 'b');
	s.append("cde");
	
	string s2;
	s2.append(s);

	string s3;
	s3.append(s, 3, 2);

	char str[] = "0123456789";
	s3.append(str, str + 2); // 附加的下标为：[str, str + 2)

	s3.append(s.begin(), s.end());
}

// 用的比较多
// operator+= :Extends the string by appending additional characters at the end of its current value
//string(1)
//string& operator+= (const string& str);
//c - string(2)
//string & operator+= (const char* s);
//character(3)
//string& operator+= (char c);
void test6()
{
	string s;
	
	s += '1';   // "1"
	s += "234"; // "1234"
	s += s;     //"12341234"
}

// insert: Inserts additional characters into the string right before the character indicated by pos (or p):

//string(1)
//string& insert(size_t pos, const string& str);
//substring(2)
//string& insert(size_t pos, const string& str, size_t subpos, size_t sublen);
//c - string(3)
//string & insert(size_t pos, const char* s);
//buffer(4)
//string& insert(size_t pos, const char* s, size_t n);
//fill(5)
//string& insert(size_t pos, size_t n, char c);
//void insert(iterator p, size_t n, char c);
//single character(6)
//iterator insert(iterator p, char c);
//range(7)
//template <class InputIterator>
//void insert(iterator p, InputIterator first, InputIterator last);
void test7()
{
	string s("123");
	string s1("ooo");

	s.insert(1, s);								// s = "112323"
	s.insert(1, s1, 0, 3);						// s = "1ooo12323"
	s.insert(1, "xxx");							// s = "1xxxooo12323"
	s.insert(1, "aaa", 2);						// s = "1aaxxxooo12323"
	s.insert(1, 10, 'm');						// s = "1mmmmmmmmmmaaxxxooo12323"
	s.insert(s.end(), '+');						// s = "1mmmmmmmmmmaaxxxooo12323+"
	s.insert(s.begin(), s1.begin(), s1.end());  // s = "ooo1mmmmmmmmmmaaxxxooo12323+"
}

// assign: Assigns a new value to the string, replacing its current contents.
//string(1)
//string& assign(const string& str);
//substring(2)
//string& assign(const string& str, size_t subpos, size_t sublen);
//c - string(3)
//string & assign(const char* s);
//buffer(4)
//string& assign(const char* s, size_t n);
//fill(5)
//string& assign(size_t n, char c);
//range(6)
//template <class InputIterator>
//string& assign(InputIterator first, InputIterator last);
void test8()
{
	string str;
	// 类似于 str = "123";
	str.assign("123"); // str = "123"
	
	string str2;
	str2.assign(str);  // str2 = "123"

}

// erase: Erases part of the string, reducing its length:
//sequence(1)
//string& erase(size_t pos = 0, size_t len = npos);
//character(2)
//iterator erase(iterator p);
//range(3)
//iterator erase(iterator first, iterator last);
void test9()
{
	string str("0123456789");

	str.erase(str.begin());				// str = "123456789"
	str.erase(3, 5);					// str = "1239"
	str.erase(str.begin(), str.end());  //str = ""
}

// pop_back Delete last character


// replace: Replaces the portion of the string that begins at character pos and spans len characters (or the part of the string in the range between [i1,i2)) by new contents:
//string(1)
//string& replace(size_t pos, size_t len, const string& str);
//string& replace(iterator i1, iterator i2, const string& str);
//substring(2)
//string& replace(size_t pos, size_t len, const string& str,
//	size_t subpos, size_t sublen);
//c - string(3)
//string & replace(size_t pos, size_t len, const char* s);
//string& replace(iterator i1, iterator i2, const char* s);
//buffer(4)
//string& replace(size_t pos, size_t len, const char* s, size_t n);
//string& replace(iterator i1, iterator i2, const char* s, size_t n);
//fill(5)
//string& replace(size_t pos, size_t len, size_t n, char c);
//string& replace(iterator i1, iterator i2, size_t n, char c);
//range(6)
//template <class InputIterator>
//string& replace(iterator i1, iterator i2,
//	InputIterator first, InputIterator last);
void test10()
{
	string str("0123456789");

	str.replace(3, 5, "aa"); // str = "012aa89"

	str.assign("0123456789");
	str.replace(str.begin() + 3, str.begin() + 5, "xx"); // str = "012xx56789"

	string str1("ooo");
	str.replace(0, 5, str1); // str = "ooo56789"
}

// swap: Exchanges the content of the container by the content of str, which is another string object. Lengths may differ.
// void swap (string& str);
void test11()
{
	string str("0123456789");
	string str1("oooo");

	str.swap(str1);
	// str:  "oooo"
	// str1: "0123456789"
	
	// 调用的不是成员函数, 是全局函数，实现还是调用成员函数 swap
	swap(str, str1); 

	int a = 3, b = 2;

	swap(a, b);
}

// string 类的大小比较：和 C 语言一样，比较字符的 ASCII 值大小

#define ISALPHA(c) ( ((c) >= 'A' && (c) <= 'Z') || ((c) >= 'a' && (c) <= 'z') )
#define ISSAMEALPHA(a, b) ( ((a) == (b)) || ((a + 32) == (b)) || ((a - 32) == (b)) )

bool isPalindrome(string s) {

	int begin = 0;
	int end = s.size() - 1;

	while (begin < end)
	{
		while (begin < end && !ISALPHA(s[begin]))
			begin++;
		while (begin < end && !ISALPHA(s[end]))
			end--;
		if (!ISSAMEALPHA(s[begin], s[end]))
			return false;

		begin++;
		end--;
	}

	return true;
}

int main(void)
{
	isPalindrome("OP");

	string a;

	delete a;

	return 0;
}