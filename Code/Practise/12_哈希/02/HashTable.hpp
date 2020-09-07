#include<iostream>
#include<vector>

using namespace std;

/*
 * 开散列：指针数组 + 单链表
 */

// 仿函数
template<class K>
struct KeyOfValue
{
	const K& operator()(const K& key)
	{
		return key;
	}
};

template<class V>
struct HashNode
{
	V _value;
	HashNode<V>* _next;

	HashNode(const V& value)
		:_value(value)
		,_next(nullptr)
	{}
};

// 前置声明
template<class K, class V, class keyOfValue, class HashFun>
class HashTable;

template<class K, class V, class keyOfValue, class HashFun>
struct HashIterator
{
	typedef HashNode<V> Node;
	typedef HashTable<K, V, keyOfValue, HashFun> _HashTable;
	typedef HashIterator<K, V, keyOfValue, HashFun> Self;

	Node* _node;
	_HashTable* _ht;

	HashIterator( Node* node,  _HashTable* ht)
		:_node(node)
		,_ht(ht)
	{}

	V& operator*() const 
	{
		return _node->_value;
	}

	V* operator->() const
	{
		return &_node->_value;
	}

	bool operator!=(const Self& it) const
	{
		return _node != it._node;
	}

	Self& operator++()  
	{
		// 如果 _node._next 存在
		if (_node->_next != nullptr)
		{
			_node = _node->_next;
		}
		// 在哈希表中向后寻找非空链表
		else
		{
			keyOfValue kov;
			HashFun hf;

			int idx = hf(kov(_node->_value)) % _ht->_table.size();

			idx++;
			for (; idx < _ht->_table.size(); idx++)
			{
				if (_ht->_table[idx])
				{
					_node = _ht->_table[idx];
					break;
				}
			}
			// 哈希表已遍历完
			if (idx == _ht->_table.size())
			 _node = nullptr;

			return *this;
		}
	}
};

struct StrToInt
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (const auto& ch : str)
		{
			hash = hash * 131 + ch;
		}

		return hash;
	}
};

template<class V>
struct KeyIsInt
{
	size_t operator()(const V& val)
	{
		return val;
	}
};

template<class K, class V, class keyOfValue, class HashFun>
class HashTable
{

public:
	// 将 HashIterator 声明为 HashTable 的友元类
	template<class K, class V, class keyOfValue, class HashFun>
	friend struct HashIterator;

	typedef HashNode<V> Node;
	typedef HashTable<K, V, keyOfValue, HashFun> Self;
	typedef HashIterator<K, V, keyOfValue, HashFun> Iterator;

	Iterator begin()
	{
		for (int i = 0; i < _table.size(); i++)
		{
			if (_table[i])
				return Iterator(_table[i], this);
		}
		return Iterator(nullptr, this);
	}

	Iterator end()
	{
		return Iterator(nullptr, this);
	}
	
	pair<Iterator, bool> insert(const V& value)
	{
		// 1. 检查容量
		checkCapacity();

		// 2. 由哈希函数计算位置
		//      1) kov 计算 key 值
		//      2) hf 将 key 值转换为整数
		keyOfValue kov;
		HashFun hf;

		int idx = hf(kov(value)) % _table.size();

		// 3. 查看 key 是否已经存在
		Node* cur = _table[idx];
		while (cur)
		{
			// key 已经存在
			if (hf(kov(value)) == hf(kov(cur->_value)))
				return make_pair(Iterator(cur, this), false);
			cur = cur->_next;
		}

		// 4. 插入：头插
		Node* node = new Node(value);
		node->_next = _table[idx];
		_table[idx] = node;
		_size++;

		return make_pair(Iterator(node, this), true);
	}

	// 获取素数表中的素数
	size_t getNewSize()
	{
		const int PRIMECOUNT = 28;
		const size_t primeList[PRIMECOUNT] =
		{ 53ul, 97ul, 193ul, 389ul, 769ul, 1543ul,
			3079ul, 6151ul, 12289ul, 24593ul, 49157ul,
			98317ul, 196613ul, 393241ul, 786433ul, 1572869ul,
			3145739ul, 6291469ul, 12582917ul, 25165843ul, 50331653ul,
			100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul,3221225473ul, 4294967291ul,
		};

		for (int i = 0; i < PRIMECOUNT; i++)
		{
			if (primeList[i] > _size)
				return primeList[i];
		}
		
		return primeList[PRIMECOUNT - 1];
	}

	void checkCapacity()
	{
		keyOfValue kov;
		HashFun hf;

		// 如果顺序表的大小和当前元素个数相同，则需要增容
		if (_size == _table.size())
		{			
			vector<Node*> newTable;
			
			//newTable.resize((_size == 0) ? 5 : 2 * _size);
			
			// 使用素数表作为增容后数组的大小，这样可以减少哈希冲突
			size_t newSize = getNewSize();
			newTable.resize(newSize);

			// 转移旧表中的节点
			for (int i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					// 计算新的位置
					int idx = hf(kov(cur->_value)) % newTable.size();
					// 保留下一个节点
					Node* next = cur->_next;
					// 头插
					cur->_next = newTable[idx];
					newTable[idx] = cur;
					// 处理下一个节点
					cur = next;
				}
				_table[i] = nullptr;
			}
			swap(_table, newTable);
		}
	}

	Node* find(const K& key)
	{
		if (_table.size() == 0) return nullptr;
		
		int idx = key % _table.size();
		
		keyOfValue kov;
		HashFun hf;

		Node* cur = _table[idx];

		while (cur)
		{
			if (hf(kov(cur->_value)) == key)
				return cur;
			cur = cur->_next;
		}

		return nullptr;
	}

	bool erase(const K& key)
	{
		if (_table.size() == 0) return false;
		
		HashFun hf;
		int idx = hf(key) % _table.size();
		keyOfValue kov;
		Node* cur = _table[idx];
		Node* parent = cur;

		while (cur)
		{
			if (hf(kov(cur->_value)) == key)
			{
				// 目标节点为表头
				if (cur == _table[idx])
				{
					_table[idx] = cur->_next;
				}
				else
				{
					parent->_next = cur->_next;
				}

				delete cur;
				--_size;
				return true;
			}

			parent = cur;
			cur = cur->_next;
		}
		return false;
	}

private:
	vector<HashNode<V>*> _table;
	size_t _size = 0;
};



//int main(void)
//{
//	HashTable<int, int, KeyOfValue<int>> ht;
//
//	ht.insert(4);
//	ht.insert(3);
//	ht.insert(2);
//	ht.insert(1);
//	ht.insert(6);
//	ht.insert(11);
//
//	HashNode<int>* p = ht.find(11);
//
//	p = ht.find(12);
//
//	ht.erase(1);
//
//	return 0;
//}