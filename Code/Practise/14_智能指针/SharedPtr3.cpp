///*
// * ���ѭ������
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
//	// �� sp1��sp2 ��������ʱ�����ü���Ϊ 0���Ż� delete ListNode����ʱ�Ż���� ListNode ������
//	// ��� ListNode ���������ã�˵�� sp1��sp2 ����Դ���ͷ�
//	~ListNode()
//	{
//		cout << "ListNode ���ͷ�" << endl;
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
//	// ��Դû�б��ͷ�
//
//	return 0;
//}