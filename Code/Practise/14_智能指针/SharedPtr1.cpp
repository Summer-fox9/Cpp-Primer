//#include<iostream>
//#include<thread>
//using namespace std;
//
///*
// * �̲߳���ȫ�� SharedPtr 
// */
//template<class T>
//class SharedPtr
//{
//private:
//	T* _ptr;
//	// һ������ _ptr �Ķ���Ӧ�ù������ü���
//	// ����ʹ�� int Ҳ����ʹ�� static�����ж�����
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
//		// �Ż��������������ָ��ͬһ����Դ���򲻽����κβ���
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
//			// ���Ҫ�����̲߳���ȫ���Ȱ� delete ע�͵�
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
//// �����̲߳���ȫ
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
//
