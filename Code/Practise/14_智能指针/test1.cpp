#include<iostream>
#include<memory>

using namespace std;

struct Date
{
	int _year = 2020;
	int _month = 9;
};

template<class T>
class SmartPtr
{
public:
	SmartPtr(T* ptr)
		:_ptr(ptr)
	{}

	~SmartPtr()
	{
		delete _ptr;
		cout << "�ͷ���Դ" << endl;
	}

	T& operator*() const 
	{
		return *_ptr;
	}

	T* operator->() const
	{
		return _ptr;
	}
	
	// ����Ȩת��
	SmartPtr(SmartPtr<T>& sp)
		:_ptr(sp._ptr)
	{
		sp._ptr = nullptr;
	}

	SmartPtr& operator=( SmartPtr<T>& sp)
	{
		if (this != &sp)
		{
			delete _ptr;
			_ptr = sp._ptr;
			sp._ptr = nullptr;
		}
		return *this;
	}
private:
	T* _ptr;
};

void func1()
{
	char* ptr = new char[100];
	// ʹ�� RAII ��˼��������
	SmartPtr<char> sp(ptr);

	throw 1;
	
	// ��Ϊ���ͷ���Դǰ�׳����쳣������������䲻��ִ��
	delete ptr;
}

void test1()
{
	while (1) 
	{
		try
		{
			func1();
		}
		catch (int i)
		{

		}
	}
}

void test2()
{
	// ��Դ��ȡ������ʼ��
	SmartPtr<int> sp(new int);

	*sp = 10;

	cout << *sp << endl;

	SmartPtr<Date> sp2(new Date);

	(*sp2)._year = 1;
	sp2->_year = 2;

	cout << sp2->_year << " " << sp2->_month << endl; // 2 9
}

void testAutoPtr()
{
	auto_ptr<Date> ap(new Date);
	cout << ap->_month << endl;

	auto_ptr<Date> ap2 = ap;
	// ���� ap ���ܽ�����
	// ������Ϊ�ڸ��Ƶ�ʱ�����˹���Ȩת�ƣ�ap �е� _ptr ����Ϊ��
	// cout << ap->_month << endl; // Error!
	cout << ap2->_month << endl; // Ok!
}

/*
 * shared_ptr ��ʵ��
 */
#include<mutex>

template<class T>
class SharedPtr
{
private:
	T* _ptr;
	// һ������ _ptr �Ķ���Ӧ�ù������ü���
	// ����ʹ�� int Ҳ����ʹ�� static�����ж�����
	int* _useCnt;
	mutex* _pmutex;

public:
	SharedPtr(T* ptr)
		:_ptr(ptr)
		, _useCnt(new int(1))
	{}

	SharedPtr(const SharedPtr<T>& sp)
		:_ptr(sp._ptr)
		,_useCnt(sp._useCnt)
	{
		++(*_useCnt);
	}

	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		// if(this != &sp)

		// �Ż��������������ָ��ͬһ����Դ���򲻽����κβ���
		if (_ptr != sp._ptr) 
		{

			if (--(*_useCnt) == 0)
			{
				delete _ptr;
				delete _useCnt;
			}
			_ptr = sp._ptr;
			_useCnt = sp._useCnt;
			++(*_useCnt);
		}

		return *this;
	}

	~SharedPtr()
	{
		if (--(*_useCnt) == 0)
		{
			delete _ptr;
			delete _useCnt;
		}
	}

	int GetCnt() const
	{
		return *_useCnt;
	}
};

void testSharedPtr()
{
	SharedPtr<Date> sp(new Date);
	cout << sp.GetCnt() << endl;

	SharedPtr<Date> copy = sp;
	cout << sp.GetCnt() << endl;
	
	SharedPtr<Date> sp2(new Date);
	sp2 = sp;
	cout << sp.GetCnt() << endl;
}

class A
{
public:
	~A()
	{
		cout << "~A()" << endl;
	}
};

template<class T>
struct DeleteArray
{
	void operator()(T* ptr)
	{
		cout << " DeleteArray " << endl;
		delete[] ptr;
	}
};

template<class T>
struct Free
{
	void operator()(T* ptr)
	{
		cout << " Free " << endl;
		free(ptr);
	}
};

void test3()
{
	shared_ptr<A> sp(new A); // ok
	
	// Error! shared_ptr Ĭ��ʹ�� delete ��ɾ������new[] �� delete ��ƥ��
	shared_ptr<A> sp2(new A[10]);
}

void test4()
{
	shared_ptr<A> sp(new A[10], DeleteArray<A>());	// ok

	shared_ptr<A> sp2((A*)malloc(sizeof(A) * 3), Free<A>());
}

int main(void)
{
	test4();

	return 0;
}