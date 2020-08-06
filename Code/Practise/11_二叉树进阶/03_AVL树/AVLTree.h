#pragma once
#include<iostream>

using namespace std;

template<class T>
struct AVLNode
{
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;
	T _data;
	int _bf;

	AVLNode(T data)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_data(data)
		,_bf(0)
	{}
};

template<class T>
class AVLTree
{
	typedef AVLNode<T> Node;
public:
	AVLTree()
		:_root(nullptr)
	{}

	bool insert(const T& data)
	{
		Node* node = new Node(data);
		if (_root == nullptr)
		{
			_root = node;
			return true;
		}

		Node* cur = _root;
		Node* parent = _root;
		while (cur)
		{
			parent = cur;
			if (cur->_data < data)
			{
				cur = cur->_right;
			}
			else if (cur->_data > data)
			{
				cur = cur->_left;
			}
			else 
			{
				delete node;
				return false;
			}
		}
		if (parent->_data < data)
			parent->_right = node;
		else
			parent->_left = node;
		
		node->_parent = parent;
		
		cur = node;
		// 更新平衡因子 + 调整
		while (parent)
		{
			if (parent->_left == cur)
				--parent->_bf;
			else
				++parent->_bf;

			// 判断是否需要继续向上更新祖先节点

			// 子树的整体高度没有变化，不需要更新
			if (parent->_bf == 0)
				break;
			// 继续更新
			else if (parent->_bf == -1 || parent->_bf == 1)
			{
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// 调整
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					cout << "插入 " << data << " 左左右旋 " << endl;
					_rotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					cout << "插入 " << data << " 右右左旋 " << endl;
					_rotateL(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					cout << "插入 " << data << " 左右 左右旋 " << endl;
					_rotateLR(parent);
				}
				else
				{
					cout << "插入 " << data << " 右左 右左旋 " << endl;
					_rotateRL(parent);
				}
				break;
			}
		}
		return true;
	}

	bool isAVLT()
	{
		return _isAVLT(_root);
	}


	void print()
	{
		_inordertraversal(_root);
		cout << endl;
	}

private:
	Node* _root;
	
	/*
	 * 左左 右单旋
	 * 1. 改变节点的指向（父父，父，父左子，子右子）
	 * 2. 改变平衡因子
	 */
	void _rotateR(Node* parent)
	{
		Node* pp = parent->_parent; // grandparent
		Node* p = parent;           // parent
		Node* sL = parent->_left;   // left son of parent
		Node* sLR = sL->_right;     // right son of sL 不一定存在

		// 修改 pp 的孩子节点，和 sL 的父节点
		// p 是整个树的根
		if (pp == nullptr)
		{
			_root = sL;
			sL->_parent = nullptr;
		}
		// p 上面还有祖先节点
		else
		{
			if (pp->_left == p)
			{
				pp->_left = sL;
			}
			else
			{
				pp->_right = sL;
			}
			sL->_parent = pp;
		}

		// 修改 p 的父节点 和 sL 的子节点
		sL->_right = p;
		p->_parent = sL;

		// 修改 p 的子节点 和 sLR 的父节点
		p->_left = sLR;
		// 如果 sLR 存在，改变他的父亲节点
		if (sLR)
		{
			sLR->_parent = p;
		}
		// 更新平衡因子
		p->_bf = sL->_bf = 0;
	}

	/*
	 * 右右 左单旋
	 * 1. 改变节点的指向（父父，父，父右子，子左子）
	 * 2. 改变平衡因子
	 */
	void _rotateL(Node* parent)
	{
		Node* pp = parent->_parent; // grandparent
		Node* p = parent;           // parent
		Node* sR = parent->_right;   // right son of parent
		Node* sRL = sR->_left;     // left son of sR 不一定存在

		// 修改 pp 的孩子节点，和 sR 的父节点
		// p 是整个树的根
		if (pp == nullptr)
		{
			_root = sR;
			sR->_parent = nullptr;
		}
		// p 上面还有祖先节点
		else
		{
			if (pp->_left == p)
			{
				pp->_left = sR;
			}
			else
			{
				pp->_right = sR;
			}
			sR->_parent = pp;
		}

		// 修改 p 的父节点 和 sR 的子节点
		sR->_left = p;
		p->_parent = sR;

		// 修改 p 的子节点 和 sRL 的父节点
		p->_right = sRL;
		// 如果 sRL 存在，改变他的父亲节点
		if (sRL)
		{
			sRL->_parent = p;
		}
		// 更新平衡因子
		p->_bf = sR->_bf = 0;
	}
	
	/*
	 * 左右 左单旋 + 右单旋
	 * 1. 改变节点的指向（父父，父，父右子，子左子）
	 * 2. 改变平衡因子
	 */
	void _rotateLR(Node* parent)
	{
		Node* fir = parent->_left;
		Node* sec = parent;

		int bf = fir->_right->_bf;

		_rotateL(fir);
		_rotateR(sec);

		if (bf == -1)
			sec->_bf = 1;
		else if(bf == 1)
			fir->_bf = -1;
	}

	/*
	 * 右左 右单旋 + 左单旋
	 * 1. 改变节点的指向（父父，父，父右子，子左子， 子左子子）
	 * 2. 改变平衡因子
	 */
	void _rotateRL(Node* parent)
	{
		Node* fir = parent->_right;
		Node* sec = parent;

		int bf = fir->_left->_bf;

		_rotateR(fir);
		_rotateL(sec);

		if (bf == -1)
			fir->_bf = 1;
		else if(bf == 1)
			sec->_bf = -1;
	}

	void _inordertraversal(Node* root)
	{
		if (root)
		{
			_inordertraversal(root->_left);
			cout << root->_data << " ";
			_inordertraversal(root->_right);
		}
	}

	bool _isAVLT(Node* root)
	{
		if (root == nullptr)
			return true;

		// 左右子树高度差和平衡因子相等
		int subL = _Height(root->_left);
		int subR = _Height(root->_right);
		if (root->_bf != subR - subL)
		{
			cout << "节点：" << root->_data << "bf 异常：" << root->_bf << " != " << subR - subL;
			return false;
		}

		return abs(root->_bf) <= 1 &&
			_isAVLT(root->_left) &&
			_isAVLT(root->_right);
	}

	int _Height(Node* root)
	{
		if (root == nullptr)
			return 0;

		int left = _Height(root->_left);
		int right = _Height(root->_right);

		return left > right ? left + 1 : right + 1;
	}
};



