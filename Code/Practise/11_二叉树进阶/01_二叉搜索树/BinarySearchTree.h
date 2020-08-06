#pragma once

#include<iostream>

using std::cin;
using std::cout;
using std::endl;
using std::swap;

template<class T>
struct BSTNode
{
	T _val;
	BSTNode<T>* _left;
	BSTNode<T>* _right;

	BSTNode(const T& val)
		:_val(val)
		,_left(nullptr)
		,_right(nullptr)
	{}
};

template<class T>
class BSTree
{
	typedef BSTNode<T> Node;
public:
	// 查找
	Node* search(const T& val)
	{
		Node* cur = _root;
		
		while (cur != nullptr)
		{
			if (val == cur->_val)
				return cur;
			else if (val > cur->_val)
				cur = cur->_right;
			else
				cur = cur->_left;
		}
		return nullptr;
	}

	// 插入：如果该元素已经存在，则不做任何操作
	//		 插入的位置为：度为 0 或 1 的节点
	bool insert(const T& val)
	{
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}

		Node* cur = _root;
		Node* parent = cur;
		while (cur != nullptr)
		{
			parent = cur;
			if (val == cur->_val)
				return false;
			else if (val < cur->_val)
				cur = cur->_left;
			else
				cur = cur->_right;
		}
		
		cur = new Node(val);
		if (val < parent->_val)
			parent->_left = cur;
		else
			parent->_right = cur;
		return true;
	}

	// 删除：度为 2 的节点 -> 找左子树最右节点或右子树最左节点 -> 
	// 替换待删除节点（值替换）-> 删除第二步中的节点（度为 0 或 1）
	bool erase(const T& val)
	{
		Node* cur = _root;
		Node* parent = cur;

		while (cur)
		{
			if (cur->_val == val)
				break;
			else if (val < cur->_val) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				parent = cur;
				cur = cur->_right;
			}
		}

		if (cur == nullptr)
			return false;

		// 1. 待删除的节点为叶子
		if (cur->_left == nullptr && cur->_right == nullptr)
		{
			if (_root == cur)
			{
				_root == nullptr;
			}
			else {
				if (parent->_left == cur)
					parent->_left = nullptr;
				else
					parent->_right = nullptr;
			}
			delete cur;

			return true;
		}
		// 2.待删除的节点左子树为空
		else if (cur->_left == nullptr)
		{
			if (_root == cur)
			{
				_root = _root->_right;
			}
			else
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;
			}
			delete cur;

			return true;
		}
		// 3.待删除的节点右子树为空
		else if (cur->_right == nullptr)
		{
			if (_root == cur)
			{
				_root = _root->_left;
			}
			else
			{
				if (parent->_left == cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
			delete cur;

			return true;
		}
		// 4.待删除的节点度为 2
		else
		{
			Node* del = cur->_left;
			Node* pDel = cur;
			// 找到左子树的最右节点（左子树的最大值）
			while (del->_right)
			{
				pDel = del;
				del = del->_right;
			}
			// 替换真正要被删除的节点和原本要删除的节点的值
			cur->_val = del->_val;

			// 修改被删除的节点的父节点的指针域
			if (pDel == cur)
				pDel->_left = del->_left;
			else
				pDel->_right = del->_left;

			// 释放节点
			delete del;

			return true;
		}

	}

	void print()
	{
		cout << "中序遍历" << endl;
		inOrderTraversal(_root);
		cout << endl;
	}

	BSTree()
		:_root(nullptr)
	{}

	BSTree(const BSTree& copy)
	{
		_root = CopyTreePro(copy._root);
	}

	// 现代写法
	BSTree<T>& operator=(BSTree<T> tmp)
	{
		swap(_root, tmp._root);
		return *this;
	}

	// 一般写法
	//BSTree<T>& operator=(const BSTree<T>& bst)
	//{
	//	if (&bst != this)
	//	{
	//		Destory(_root);
	//		_root = CopyTreePro(bst._root);
	//	}
	//	return *this;
	//}

	~BSTree()
	{
		Destory(_root);
		_root = nullptr;
	}

private:
	Node* _root = nullptr;

	void inOrderTraversal(Node* node)
	{
		if (node)
		{
			inOrderTraversal(node->_left);
			cout << node->_val << " ";
			inOrderTraversal(node->_right);
		}
	}

	void Destory(Node* root)
	{
		if (root)
		{
			Destory(root->_left);
			Destory(root->_right);
			delete root;
		}
	}

	void CopyTree(const Node* root)
	{
		if (root)
		{
			insert(root->_val);
			CopyTree(root->_left);
			CopyTree(root->_right);
		}
	}

	Node* CopyTreePro(const Node* root)
	{
		if (root)
		{
			Node* cur = new Node(root->_val);
			cur->_left = CopyTreePro(root->_left);
			cur->_right = CopyTreePro(root->_right);
			return cur;
		}
		return nullptr;
	}
};
