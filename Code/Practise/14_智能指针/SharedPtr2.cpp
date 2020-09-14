///*
// * �̰߳�ȫ�汾
// */
//
//#include<iostream>
//#include<thread>
//#include<mutex>
//
//using namespace std;
//
//template<class T>
//class SharedPtr
//{
//private:
//	T* _ptr;
//	// һ������ _ptr �Ķ���Ӧ�ù������ü���
//	// ����ʹ�� int Ҳ����ʹ�� static�����ж�����
//	int* _useCnt;
//	mutex* _mtx;
//
//public:
//	SharedPtr(T* ptr)
//		:_ptr(ptr)
//		, _useCnt(new int(1))
//		,_mtx(new mutex)
//	{}
//
//	SharedPtr(const SharedPtr<T>& sp)
//		:_ptr(sp._ptr)
//		, _useCnt(sp._useCnt)
//		,_mtx(sp._mtx)
//	{
//		addCnt();
//	}
//
//	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
//	{
//		// if(this != &sp)
//
//		// �Ż��������������ָ��ͬһ����Դ���򲻽����κβ���
//		if (_ptr != sp._ptr)
//		{
//			subCnt();
//			if (*_useCnt == 0)
//			{
//				delete _ptr;
//				delete _useCnt;
//				delete _mtx;
//			}
//			_ptr = sp._ptr;
//			_useCnt = sp._useCnt;
//			_mtx = sp._mtx;
//			addCnt();
//		}
//
//		return *this;
//	}
//
//	~SharedPtr()
//	{
//		subCnt();
//		if (*_useCnt == 0)
//		{
//			delete _ptr;
//			delete _useCnt;
//			delete _mtx;
//		}
//	}
//
//	int GetCnt() const
//	{
//		return *_useCnt;
//	}
//
//private:
//	void addCnt()
//	{
//		_mtx->lock();
//		++(*_useCnt);
//		_mtx->unlock();
//	}
//
//	void subCnt()
//	{
//		_mtx->lock();
//		--(*_useCnt);
//		_mtx->unlock();
//	}
//};
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
//	cout << "�������̺߳����н��ж��ٴο�������" << " ";
//	cin >> n;
//
//	cout << "�߳̿�ʼǰ sp �����ü���: " << sp.GetCnt() << endl;
//
//	thread t1(fun, (sp), n);
//	thread t2(fun, (sp), n);
//
//	t1.join();
//	t2.join();
//
//	cout << "�߳̽����� sp �����ü���: " << sp.GetCnt() << endl;
//
//	return 0;
//}