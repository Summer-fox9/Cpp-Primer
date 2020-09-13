#define _CRT_SECURE_NO_WARNINGS

#include<vector>
#include<iostream>
#include<map>

using namespace std;

class A
{
public:
	// A() = default;
	A()
	{
		cout << "A()" << endl;
	}

	// A(const A& a) = default;
	A(const A& a) 
	{
		cout << "A(const A& a)" << endl;
	}

	A(int a, int b)
		:_a(a)
		,_b(b)
	{}

	A(int a)
		:_a(a)
		, _b(0)
	{}
private:
	int _a;
	int _b;
};

template<class T>
class Vector
{
public:
	Vector(size_t n)
		:_array(new T[n])
		,_size(0)
		,_capacity(n)
	{}

	Vector(const initializer_list<T>& ilst)
		:_array(new T[ilst.size()])
		,_size(0)
		,_capacity(ilst.size())
	{
		for (const auto& e : ilst)
		{
			_array[_size++] = e;
		}
	}

private:
	T* _array;
	size_t _size;
	size_t _capacity;
};

// C++ 11 ֧�� �������ͺ��Զ������� ���б��ʼ��
void test1()
{
	// ������ʽ
	vector<int> v1 = { 1, 2, 3 };
	vector<int> v2{ 1, 2, 3 };

	int i1 = { 1 };
	int i2{ 1 };

	pair<int, int> p = { 1, 1 };
	map<int, int> m = { {1, 1}, {2, 2}, };

	// ������������˼�ǵȼ۵�
	A a1{ 1, 2 };
	A a2(1, 2);

	// ���ι��캯������ʽ����ת��
	// 5 �ȹ������������Ȼ�� a3 ���ÿ������캯��
	A a3 = 5; 

	// ��Ҫע����ǣ��Լ�ʵ�ֵ�����ʽ�������������Լ�ʵ��һ�� vector�����޷���Ȼ֧���б��ʼ����
	// ��Ҫ�ṩ����Ϊ initializer_list �Ĺ��캯��
	Vector<int> V{ 1, 2, 3, 4, 5 };
	
}

int func()
{
	return 1;
}

// �����Ƶ�
void test2()
{
	// auto ����ʱ���ݳ�ʼ�����ʽ���������Ƶ�
	map<string, string> m;
	auto it = m.begin();

	// decltype ����ʱ�����Ƶ�
	decltype(2 - 1) d1;

	// ���ݺ�������ֵ�Ƶ�����
	decltype(func()) d2;

	// �����в������Ƶ���������ֵ����
	cout << "d2 type: " << typeid(d2).name() << endl; // int 

	// ����û�в������Ƶ������Ľӿ�����
	cout << "d2 type: " << typeid(decltype(func)).name() << endl;  // int __cdecl(void)
}

class B
{
public:

	//`default`���ñ�������ʾ����һ��Ĭ�Ϻ���

	//`delete`����һ������������ɾ�������������ٱ�ʹ��
	B() = default;

	B(const B& b) = delete; // ������

	B& operator=(const B& b) = delete;
};

void test3()
{
	/* ��ֵ�����Է��� = ��࣬����ȡ��ַ
	 * ��ֵ�����ܷ��� = ��࣬����ȡ��ַ
	 * 
	 * ��������ʱ��������������������ֵ
	 */

	/*
	 * ��ֵ���ã��ȿ���������ֵ��Ҳ����������ֵ
	 */
	
	int a = 3;

	int& ra = a;
	// ��ֵ���ÿ���������ֵ����Ҫ���� const
	const int& rc = 10;

	/*
	 * ��ֵ���ã�ֻ��������ֵ
	 */

	int&& r1 = 10;
	// int&& r2 = a;
	
	// �������������
	A&& a1 = A();

	const A& a2 = A();

}

void test4()
{
	A&& a1 = A();

	const A& a2 = A();

	/*
	 * �����
	 * A()
	 * A()
	 * ˵���������������Ż���ֻ������ a1��a2 �Ĺ��캯��
	 * ���û�н����Ż���������Ӧ�õ��õ��ǣ����캯�� + ��������
	 */
}

class String
{
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
		,_size(strlen(str))
	{
		strcpy(_str, str);
		cout << "String(const char* str = "")" << endl;
	}

	String(const String& str)
		: _str(new char[strlen(str._str) + 1])
		, _size(str._size)
	{
		strcpy(_str, str._str);
		cout << "String(const String& str)" << endl;
	}
	

	~String()
	{
		if (_str)
		{
			delete[] _str;
		}
	}
private:
	char* _str;
	int _size;
};

String getStr(const char* s)
{
	String str(s);
	return str;
}

void test5()
{
	String str = getStr("Shepard");

	/*
	 * ����� 
	 *  String(const char* str = )
	 *	String(const String& str)
	 * 
	 * ˵����
	 * ���� getStr() �� str �Ĺ��캯�� �� test5() �� str �Ŀ�������
	 * getStr() �з��ص� str ��һ������ֵ����һ����ֵ��
	 * �������������Ż���û�й��췵�ص���ʱ����
	 * 
	 * ���⣺
	 * ���ܱ������������Ż�������Ȼ����һ�����⣺
	 * getStr �з��ص� str ��û������ʹ�ã����Ĵ���ֻ��Ϊ�˹��� test5 �е� str ����
	 * ��ô��Ϊ�俪��Դ��Ȼ����ɾ���ƺ���û��ʲô�����
	 */
}

class String2
{
public:
	String2(const char* str = "")
		:_str(new char[strlen(str) + 1])
		, _size(strlen(str))
	{
		strcpy(_str, str);
		cout << "String2(const char* str = "")" << endl;
	}

	String2(const String2& str)
		: _str(new char[strlen(str._str) + 1])
		, _size(str._size)
	{
		strcpy(_str, str._str);
		cout << "String2(const String& str)" << endl;
	}

	// �ƶ�����
	// ��ֵ����ֻ��ƥ����ֵ
	String2(String2&& str)
		: _str(str._str) // �� str ����Դ�� _str
		, _size(str._size)
	{
		str._str = nullptr; // str ����Դ���� _str ����
		cout << "String2(String2&& str)" << endl;
	}

	~String2()
	{
		if (_str)
		{
			delete[] _str;
		}
	}

	String2& operator=(const String2& str)
	{
		if (&str != this)
		{
			delete[] _str;
			_str = new char[strlen(str._str) + 1];
			_size = str._size;
			strcpy(_str, str._str);
		}

		cout << "String2& operator=(const String2& str)" << endl;
		return *this;
	}

	// �ƶ���ֵ
	String2& operator=(String2&& str)
	{
		if (&str != this)
		{
			swap(str._str, _str);
			_size = str._size;
		}
		cout << "String2& operator=(String2&& str)" << endl;
		return *this;
	}


private:
	char* _str;
	int _size;
};

String2 getStr2(const char* s)
{
	String2 str(s);
	return str;
}

void test6()
{
	String2 str = getStr2("Shepard");

	/*
	 * �����
	 * String2(const char* str = )
	 * String2(String2&& str)
	 * 
	 * ˵����
	 * �ڹ��� test6 �е� str ʱ�����õ��� String2 �Ĳ���Ϊ��ֵ���ÿ������캯��
	 * 
	 * ����������캯���Ĺ��ܣ�
	 * ��ֱ�ӽ���ֵ������ֵ������Դ���� test6 �е� str���Ӷ�������test6 �е� str �ٴ�
	 * ������Դ�����������Ч��
	 */

	// ����������죬��Ϊ str �����ǡ�û���á���ֵ
	String2 str2(str);

	/*
	 * String2("Wang") ��һ����ʱ����������������������ֻ�� 1 ��
	 * ����������俽������ str3 �������� �ƶ�����
	 * ������������������Ż������Ե��õ��� str3 �Ŀ�������
	 */
	String2 str3 = String2("Wang");

	cout << "============ ��ֵ��������غ���1 ============" << endl;

	// ������һ�������������� str3 ��ֵ��һ������ 3 ������
	str3 = getStr2("CET-6");

	cout << "============ ��ֵ��������غ���2 ============" << endl;
	
	// ֱ���ý�������� str3 ��ֵ
	str3 = String2("CET-4");

	/*
	 * �����
	 *
	 * ============ ��ֵ��������غ���1 ============
	 *	String2(const char* str = )
	 * 	String2(String2&& str)
	 *	String2& operator=(String2&& str)
	 *	============ ��ֵ��������غ���2 ============
	 *	String2(const char* str = )
	 *	String2& operator=(String2&& str) 
	 */
}

//int main(void)
//{
//	test6();
//}