///*
// * 解决循环引用
// */
//#include<iostream>
//#include<memory>
//
//using namespace std;
//
//template<class T>
//class ListNode
//{
//public:
//	//shared_ptr<ListNode<T>> _prev;
//	//shared_ptr<ListNode<T>> _next;
//
//	weak_ptr<ListNode<T>> _prev;
//	weak_ptr<ListNode<T>> _next;
//
//	// 当 sp1，sp2 调用析构时，引用计数为 0，才会 delete ListNode，此时才会调用 ListNode 的析构
//	// 如果 ListNode 析构被调用，说明 sp1，sp2 的资源被释放
//	~ListNode()
//	{
//		cout << "ListNode 被释放" << endl;
//	}
//};
//
//int main(void)
//{
//	shared_ptr<ListNode<int>> sp1(new ListNode<int>);
//	shared_ptr<ListNode<int>> sp2(new ListNode<int>);
//
//	cout << "sp1: " << sp1.use_count()
//		<< " sp2: " << sp2.use_count() << endl;
//
//	sp1->_next = sp2;
//	sp2->_prev = sp1;
//
//	cout << "sp1: " << sp1.use_count()
//		<< " sp2: " << sp2.use_count() << endl;
//
//	// 资源没有被释放
//
//	return 0;
//}