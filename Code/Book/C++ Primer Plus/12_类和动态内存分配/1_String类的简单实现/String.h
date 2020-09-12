#ifndef STRING_H_
#define STRING_H_

class String
{
private:
	char* str;
	int len;
	static int num_strings;
	static const int CINLIM = 80;

public:
	String();
	String(const char* s);
	String(const String& s);
	~String();

	String& operator=(const String& s);
	String& operator=(const char* s);

	/*
	 * 这些函数定义为友元是因为：
	 * 如果这样调用函数： "love" < s1 -> operator<("love", s1)
	 * 将被隐式转换为：operator<(String("love"), s1)
	 */
	friend bool operator<(const String& s1, const String& s2);
	friend bool operator>(const String& s1, const String& s2);
	friend bool operator==(const String& s1, const String& s2);
	
	char& operator[](int n);
	const char& operator[](int n) const;

	static int HowMany(){return num_strings;}
	
	int length() const { return len; }

	friend std::ostream& operator<<(std::ostream& os, const String& s);
	friend std::istream& operator>>(std::istream& is,  String& s);
};

#endif 