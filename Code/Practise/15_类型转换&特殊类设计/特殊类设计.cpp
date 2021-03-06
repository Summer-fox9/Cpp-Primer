//#include<iostream>
//#include<thread>
//#include<mutex>
//
//using namespace std;
//
///*
// * 只能在堆上创建对象
// */
//class HeapOnly
//{
//public:
//	static HeapOnly* getInstance()
//	{
//		return new HeapOnly;
//	}
//
//private:
//	HeapOnly()
//	{}
//
//	// 拷贝构造应该只声明不实现，避免在类的 public 函数中调用从而在
//	// 函数栈中构造对象
//	HeapOnly(const HeapOnly& hp);
//};
//
//
///*
// * 只能在栈上构造对象
// */
//// 方法 1
////class StackOnly
////{
////private:
////	StackOnly()
////	{}
////public:
////	static StackOnly getInstance()
////	{
////		return StackOnly();
////	}
////};
//class StackOnly
//{
//private:
//	void* operator new(size_t size);
//	// 或者写作：void* operator new(size_t size) = delete;
//
//	// 构造函数必须设为私有，防止用户声明全局变量（数据段）
//	StackOnly()
//	{}
//public:
//	static StackOnly getInstance()
//	{
//		return StackOnly();
//	}
//};
//
//class NoCopy
//{
//public:
//	NoCopy()
//	{}
//	
//	//NoCopy(const NoCopy& nc) = delete;
//	//NoCopy& operator=(const NoCopy& nc) = delete;
//private:
//	// 声明为私有且不实现 或者定义为 delete 函数都可
//	NoCopy(const NoCopy& nc);
//	NoCopy& operator=(const NoCopy& nc);
//};
//
////class NoInhert final{};
////
////class Sub : NoInhert{}; // Error!
//
///*
// * 单例模式
// * 1. 饿汉模式：
// *    1) 构造函数私有
// *	  2) 提供一个静态的方法返回单例
// *	  3) 提供一个静态单例成员
// *    4) 拷贝构造和赋值运算符重载声明为 delete 函数
// *	优势：
// *		实现简单，多线程情况下效率高
// *  缺点：
// *		程序启动慢，多个单例对象的初始化顺序无法控制
// *  
// * 2. 懒汉模式
// *		调用接口时再创建对象，延迟加载（饿汉模式直接先创建对象）
// *  优势：
// *		程序启动快，多个单例对象的的初始化顺序可以控制
// *	缺点：
// *		实现复杂，需要考虑多线程问题
// */
//// 饿汉模式
//class SingleTon1
//{
//private:
//	static SingleTon1 st;
//
//	SingleTon1() {};
//
//	// 禁掉拷贝构造和赋值运算符重载
//	SingleTon1(const SingleTon1& st) = delete;
//	SingleTon1& operator=(const SingleTon1& st) = delete;
//
//public:
//	static SingleTon1* GetInstance()
//	{
//		return &st;
//	}
//};
//
//// 静态成员初始化
//SingleTon1 SingleTon1::st;
//
//// 懒汉模式：需要注意线程安全问题
//class SingleTon2
//{
//private:
//	static SingleTon2* pst;
//	static mutex _mtx;
//
//	SingleTon2() {};
//	
//	SingleTon2(const SingleTon2& st) = delete;
//	SingleTon2& operator=(const SingleTon2& st) = delete;
//
//public:
//	static SingleTon2* GetInstance()
//	{
//		// 因为创建对象仅在第一次，而上锁解锁会严重降低效率,
//		// 所以我们只用在创建对象时上锁即可
//		if (pst == nullptr)
//		{
//			_mtx.lock();
//			if (pst == nullptr)
//			{
//				pst = new SingleTon2;
//			}
//			_mtx.unlock();
//		}
//
//		return pst;
//	}
//};
//
//SingleTon2* SingleTon2::pst = nullptr;
//mutex SingleTon2::_mtx;
//
//void test1()
//{
//	cout << "test 饿汉模式:" << endl;
//	for (int i = 0; i < 10; i++)
//	{
//		cout << (void*)SingleTon1::GetInstance() << endl;
//	}
//
//	cout << "test 懒汉模式：" << endl;
//	for (int i = 0; i < 10; i++)
//	{
//		cout << (void*)SingleTon2::GetInstance() << endl;
//	}
//
//}
//
//int main(void)
//{
//
//	//thread(func1, )
//
//	test1();
//
//	return 0;
//}