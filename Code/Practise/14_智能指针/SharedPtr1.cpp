//#include<iostream>
//#include<thread>
//using namespace std;
//
///*
// * 线程不安全版 SharedPtr 
// */
//template<class T>
//class SharedPtr
//{
//private:
//	T* _ptr;
//	// 一起引用 _ptr 的对象应该共享引用计数
//	// 不能使用 int 也不能使用 static（所有对象共享）
//	int* _useCnt;
//
//public:
//	SharedPtr(T* ptr)
//		:_ptr(ptr)
//		, _useCnt(new int(1))
//	{}
//
//	SharedPtr(const SharedPtr<T>& sp)
//		:_ptr(sp._ptr)
//		, _useCnt(sp._useCnt)
//	{
//		++(*_useCnt);
//	}
//
//	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
//	{
//		// if(this != &sp)
//
//		// 优化：如果两个引用指向同一个资源，则不进行任何操作
//		if (_ptr != sp._ptr)
//		{
//
//			if (--(*_useCnt) == 0)
//			{
//				delete _ptr;
//				delete _useCnt;
//			}
//			_ptr = sp._ptr;
//			_useCnt = sp._useCnt;
//			++(*_useCnt);
//		}
//
//		return *this;
//	}
//
//	~SharedPtr()
//	{
//		if (--(*_useCnt) == 0)
//		{
//			// 如果要测试线程不安全，先把 delete 注释掉
//			//delete _ptr;
//			//delete _useCnt;
//		}
//	}
//
//	int GetCnt() const
//	{
//		return *_useCnt;
//	}
//};
//
//// 测试线程不安全
//
//void fun(SharedPtr<int> sp, int n)
//{
//	for (int i = 0; i < n; i++)
//	{
//		SharedPtr<int> sp2(sp);
//	}
//}
//
//int main(void)
//{
//	SharedPtr<int> sp(new int(1));
//	int n;
//
//	cout << "请输入线程函数中进行多少次拷贝构造" << " ";
//	cin >> n;
//
//	cout << "线程开始前 sp 的引用计数: " << sp.GetCnt() << endl;
//
//	thread t1(fun, (sp), n);
//	thread t2(fun, (sp), n);
//
//	t1.join();
//	t2.join();
//
//	cout << "线程结束后 sp 的引用计数: " << sp.GetCnt() << endl;
//
//	return 0;
//}
//
