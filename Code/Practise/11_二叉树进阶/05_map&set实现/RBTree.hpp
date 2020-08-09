#pragma once
#include<iostream>
#include<utility>

using namespace std;

enum Color
{
	RED,
	BLACK,
};

template<class Value>
struct RBNode
{
	typedef RBNode<Value>* Ptr_RBNode;

	Value _data;
	Color _color;
	Ptr_RBNode _left;
	Ptr_RBNode _right;
	Ptr_RBNode _parent;

	RBNode(const Value& data = Value())
		:_data(data)
		,_color(RED) // 节点颜色默认初始化为 red
		,_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
	{}
};

template<class Value>
struct RBIterator
{
	typedef RBNode<Value> Node;
	typedef RBIterator Self;

	Node* _node;

	RBIterator(Node* node)
		:_node(node)
	{}

	Value& operator*()
	{
		return _node->_data;
	}

	Value* operator->()
	{
		return &_node->_data;
	}

	bool operator==(const Self& it)
	{
		return _node == it._node;
	}

	bool operator!=(const Self& it)
	{
		return _node != it._node;
	}

	Self& operator++()
	{
		// 如果当前节点有右节点
		if (_node->_right)
		{
			_node = _node->_right;
			// 让 _node 设为最右节点
			while (_node->_left)
				_node = _node->_left;
		}
		// 向上回溯，如果当前节点为父节点的右节点，继续向上回溯
		else
		{
			Node* parent = _node->_parent;
			while (_node == parent->_right)
			{
				_node = parent;
				parent = parent->_parent;
			}
			// 当 parent 为 _header ,_node 为整个树的根节点时，
			// 一定会退出上面的 while 循环,此时应该将 _node 置为 _header
			// 如果 _node 不在父节点的左侧，也应该单独执行一次，将 _node 指向下一次访问的节点
			/*_node = parent;*/
			// 上面的写法有一个问题，如果整个树只有一个节点。_header->right == _node
			// _node 会走到 _header, parent 走到 _node 此时退出循环
			// _node 再被赋值为 _node , 所以迭代器的遍历会陷入循环
			if (_node->_right != parent)
				_node = parent;
		}

		return *this;
	}
};

// KeyOfValue 仿函数类型用来获取 value 对应的 key
// V 是 pair 类型
template<class K, class V, class KeyOfValue>
class RBTree
{
public:
	typedef RBNode<V> Node;
	typedef RBIterator<V> iterator;

private:
	Node* _header;
	KeyOfValue kov;

public:
	iterator begin()
	{
		return iterator(_header->_left);
	}

	iterator end()
	{
		return iterator(_header);
	}
	
	RBTree()
		:_header(new Node)
	{
		_header->_left = _header->_right = _header;
	}

	pair<iterator, bool> insert(const V& data)
	{
		cout << "插入 " << data.first << "  :";

		if (_header->_parent == nullptr)
		{
			Node* node = new Node(data);

			node->_color = BLACK;
			_header->_parent = node;
			node->_parent = _header;

			_header->_left = node;
			_header->_right = node;

			return make_pair(iterator(node), true);
		}

		Node* cur = _header->_parent;
		Node* parent = nullptr;

		// 搜索
		while (cur)
		{
			parent = cur;
			if (kov(data) == kov(cur->_data))
				return make_pair(iterator(cur), false);
			else if (kov(data) > kov(cur->_data))
				cur = cur->_right;
			else 
				cur = cur->_left;
		}
		cur = new Node(data);

		// 插入
		if (kov(parent->_data) > kov(data))
			parent->_left = cur;
		else
			parent->_right = cur;

		cur->_parent = parent;
		
		// 保存一下返回时新插入的节点的指针
		Node* ret = cur;
		
		// 调整：修改颜色 旋转
		while(cur != _header->_parent && cur->_parent->_color == RED)
		{ 
			Node* p = cur->_parent;
			Node* pp = p->_parent;
			
			// 1. 插入位置在祖父节点的左子树上
			if (pp->_left == p)
			{
				Node* u = pp->_right;
				// 情况一：如果叔叔节点 存在且为红
				if (u && u->_color == RED)
				{
					u->_color = p->_color = BLACK;
					pp->_color = RED;
					
					// 继续向上查看祖父节点的父节点是否为红色
					cur = pp;

				}								
				// 如果叔叔节点 不存在 或 存在且为黑
				else
				{
					// 情况 二：cur 在 p 的右侧，双旋
					if (cur == p->_right)
					{
						// 先进行左旋，转换为上一种情况
						_rotateL(p);
						swap(cur, p);
					}
					
					// 情况 三：cur 在 p 的左侧，单旋
					// 右旋
					_rotateR(pp);
					p->_color = BLACK;
					pp->_color = RED;
					

					// 此时 p 为子树（树）的根，且 p 为黑色 。可以结束调整
					break;
				}
			}

			// 2. 插入位置在祖父节点的右子树上
			else
			{
				Node* u = pp->_left;
				// 如果叔叔节点 存在且为红
				if (u && u->_color == RED)
				{
					u->_color = p->_color = BLACK;
					pp->_color = RED;

					// 继续向上查看祖父节点的父节点是否为红色
					cur = pp;

				}
				// 如果叔叔节点 不存在 或 存在且为黑
				else
				{
					if (cur == p->_left)
					{
						// 先进行右旋，转换为上一种情况
						_rotateR(p);
						swap(cur, p);

					}

					// 左旋
					_rotateL(pp);
					p->_color = BLACK;
					pp->_color = RED;

					// 此时 p 为子树（树）的根，且 p 为黑色 。可以结束调整
					break;
				}
			}
			
		}	
		// 根设置为黑
		_header->_parent->_color = BLACK;
		_header->_left = _leftMost();
		_header->_right = _rightMost();

		return make_pair(iterator(ret), true);
	}

	void print()
	{
		_inOrderTraversal(_header->_parent);
	}

	bool isRBTree()
	{
		Node* root = _header->_parent;
		Node* cur = root;
		int blackCount = 0;

		if (root == nullptr) return true;

		// 1. 根节点是否为黑
		if (root->_color != BLACK) return false;

		// 先遍历一条路径，算出黑色节点的个数
		while (cur)
		{
			if (cur->_color == BLACK) 
				blackCount++;
			cur = cur->_left;
		}
		
		int curCount = 0;

		return _isRBTree(root, blackCount, curCount);
	}

private:

	void _rotateR(Node* parent)
	{
		Node* pp = parent->_parent; // grandparent
		Node* p = parent;           // parent
		Node* sL = parent->_left;   // left son of parent
		Node* sLR = sL->_right;     // right son of sL 不一定存在

		// 修改 pp 的孩子节点，和 sL 的父节点
		// p 是整个树的根
		if (p == _header->_parent)
		{
			_header->_parent = sL;
			sL->_parent = _header;
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
	}

	void _rotateL(Node* parent)
	{
		Node* pp = parent->_parent; // grandparent
		Node* p = parent;           // parent
		Node* sR = parent->_right;   // right son of parent
		Node* sRL = sR->_left;     // left son of sR 不一定存在

		// 修改 pp 的孩子节点，和 sR 的父节点
		// p 是整个树的根
		if (p == _header->_parent)
		{
			_header->_parent = sR;
			sR->_parent = _header;
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
	}

	Node* _leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node* _rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}

	void _inOrderTraversal(Node* root)
	{
		if (root)
		{
			_inOrderTraversal(root->_left);
			cout << "key: " << root->_data.first << " ";
			if (root->_color == RED)
				cout << "红色" << endl;
			else
				cout << "黑色" << endl;
			_inOrderTraversal(root->_right);
		}
	}

	bool _isRBTree(Node* root, const int blackCount, int curCount)
	{
		// 一条路径遍历完, 黑色节点的总数与基准值不同，不是红黑树
		if (root == nullptr)
		{
			return (curCount == blackCount) ? true : false;
		}

		if (root->_color == BLACK)
			curCount++;

		// 判断红色节点是否连续
		Node* parent = root->_parent;

		if (parent && parent->_color == RED && root->_color == RED)
		{
			cout << "红色节点重复" << endl;
			return false;
		}

		return _isRBTree(root->_left, blackCount, curCount)
			&& _isRBTree(root->_right, blackCount, curCount);
	}
};
