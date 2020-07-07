#pragma once

#include<iostream>

using namespace std;

/**
 * list.h: 双向带头循环链表
 */

/**
 * ListNode: 链表的节点类型
 */
template<class T>
struct ListNode
{
	T _value;
	ListNode* _next;
	ListNode* _prev;

	ListNode(const T& val = T())
		:_value(val)
		,_next(nullptr)
		,_prev(nullptr)
	{}
};


/**
 * ListIterator: 链表的迭代器
 * 类类型的迭代器不是指针，而是一个类。
 * 各种操作其实本质是操作 ListNode 中的某个成员
 */
template<class T, class Ref, class Ptr>
struct ListIterator
{
	typedef ListNode<T> Node;
	typedef ListIterator<T, Ref, Ptr> Self;

	ListIterator(Node* node)
		:_node(node)
	{}

	Ref operator*()
	{
		return _node->_value;
	}
	
	/** 
	 *	-> 当作单目运算符处理
	 *	类类型中的元素访问模式：ListNode->_val->某一个元素
	 *	中间的 ->_val 被编译器优化
	 */
	Ptr operator->()
	{
		return &_node->_value;
	}

	Self& operator++()
	{
		_node = _node->_next;
		return *this;
	}

	Self& operator--()
	{
		_node = _node->_prev;
		return *this;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	Node* _node;
};


template<class T>
class List
{
public:
	
	typedef ListNode<T> Node;
	typedef ListIterator<T, T&, T*> iterator;
	typedef ListIterator<T, const T&, const T*> const_iterator;

	List()
		:_header(new Node)
	{
		_header->_next = _header->_prev = _header;
	}

	List(const List<T>& lst)
		:_header(new Node)
	{
		_header->_next = _header->_prev = _header;
		//深拷贝，插入元素
		for (const auto& e : lst)
			push_back(e);
	}
	
	// 现代写法
	List<T>& operator=(List<T> L)
	{
		swap(_header, L._header);
		return *this;
	}
	
	~List()
	{
		if (_header)
		{
			clear();
			delete _header;
			_header = nullptr;
		}
	}

	/**
	 *	迭代器实现
	 *	begin: _header->next  第一个元素
	 *	end:   _header        最后一个元素的下一个
	 */
	iterator begin()
	{
		return iterator(_header->_next);
	}

	iterator end()
	{
		return iterator(_header);
	}

	const_iterator begin() const
	{
		return const_iterator(_header->_next);
	}

	const_iterator end() const
	{
		return const_iterator(_header);
	}

	iterator insert(iterator pos, const T& val)
	{
		Node* node = new Node(val);
		
		node->_next = pos._node;
		node->_prev = pos._node->_prev;

		node->_next->_prev = node;
		node->_prev->_next = node;

		return iterator(node);
	}

	iterator erase(iterator pos)
	{
		// 不能删除头节点
		if (pos != end())
		{
			Node* del = pos._node;
			Node* next = del->_next;

			del->_prev->_next = del->_next;
			del->_next->_prev = del->_prev;

			delete del;
			return iterator(next);
		}
		return pos;
	}

	void push_back(const T& val)
	{
		insert(end(), val);
	}

	void push_front(const T& val)
	{
		insert(begin(), val);
	}

	void pop_back()
	{
		erase(end()--);
	}

	void pop_front()
	{
		erase(begin());
	}

	size_t size() const
	{
		size_t len;

		for (const auto& it : *this)
			++len;

		return len;
	}

	void clear()
	{
		Node* cur = _header->_next;

		while (cur != _header)
		{
			Node* next = cur->_next;
			delete cur;
			cur = next;
		}
		_header->_next = _header->_prev = _header;
	}

	
private:
	// 头节点
	Node* _header;
};

template<class T>
void printList(const List<T> L)
{
	typename List<T>::const_iterator it = L.begin();
	while (it != L.end())
	{
		cout << it._node->_value << " ";
		++it; // 不能写成 it++
	}
	cout << endl;
}


