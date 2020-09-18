//#include<iostream>
//#include<thread>
//#include<mutex>
//
//using namespace std;
//
///*
// * ֻ���ڶ��ϴ�������
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
//	// ��������Ӧ��ֻ������ʵ�֣���������� public �����е��ôӶ���
//	// ����ջ�й������
//	HeapOnly(const HeapOnly& hp);
//};
//
//
///*
// * ֻ����ջ�Ϲ������
// */
//// ���� 1
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
//	// ����д����void* operator new(size_t size) = delete;
//
//	// ���캯��������Ϊ˽�У���ֹ�û�����ȫ�ֱ��������ݶΣ�
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
//	// ����Ϊ˽���Ҳ�ʵ�� ���߶���Ϊ delete ��������
//	NoCopy(const NoCopy& nc);
//	NoCopy& operator=(const NoCopy& nc);
//};
//
////class NoInhert final{};
////
////class Sub : NoInhert{}; // Error!
//
///*
// * ����ģʽ
// * 1. ����ģʽ��
// *    1) ���캯��˽��
// *	  2) �ṩһ����̬�ķ������ص���
// *	  3) �ṩһ����̬������Ա
// *    4) ��������͸�ֵ�������������Ϊ delete ����
// *	���ƣ�
// *		ʵ�ּ򵥣����߳������Ч�ʸ�
// *  ȱ�㣺
// *		�����������������������ĳ�ʼ��˳���޷�����
// *  
// * 2. ����ģʽ
// *		���ýӿ�ʱ�ٴ��������ӳټ��أ�����ģʽֱ���ȴ�������
// *  ���ƣ�
// *		���������죬�����������ĵĳ�ʼ��˳����Կ���
// *	ȱ�㣺
// *		ʵ�ָ��ӣ���Ҫ���Ƕ��߳�����
// */
//// ����ģʽ
//class SingleTon1
//{
//private:
//	static SingleTon1 st;
//
//	SingleTon1() {};
//
//	// ������������͸�ֵ���������
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
//// ��̬��Ա��ʼ��
//SingleTon1 SingleTon1::st;
//
//// ����ģʽ����Ҫע���̰߳�ȫ����
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
//		// ��Ϊ����������ڵ�һ�Σ����������������ؽ���Ч��,
//		// ��������ֻ���ڴ�������ʱ��������
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
//	cout << "test ����ģʽ:" << endl;
//	for (int i = 0; i < 10; i++)
//	{
//		cout << (void*)SingleTon1::GetInstance() << endl;
//	}
//
//	cout << "test ����ģʽ��" << endl;
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