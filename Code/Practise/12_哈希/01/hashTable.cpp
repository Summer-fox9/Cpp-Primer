// 哈希表：线性探测

#include<iostream>
#include<vector>

using namespace std;

enum State
{
	EXIST,
	EMPTY,
	DELETE,
};

template<class K, class V>
struct HashNode
{
	pair<K, V> _value;
	// 数据状态
	State _state;

	HashNode(const pair<K, V>& value = pair<K, V>())
		:_value(value)
		,_state(EMPTY)
	{}
};


template<class K, class V>
class HashTable
{
public:
	HashTable(size_t size = 10)
		:_size(0)
	{
		_table.resize(size);
	}

	// 1. 插入
	bool insert(const pair<K, V>& value)
	{
		checkCapacity();

		int idx = value.first % _table.size();

		while (_table[idx]._state == EXIST)
		{
			// 元素已经存在,插入失败
			if (_table[idx]._value.first == value.first)
				return false;
			idx++;
			if (idx == _table.size()) 
				idx = 0;
		}
		// 找到了合适的位置
		_table[idx]._value = value;
		_table[idx]._state = EXIST;
		++_size;
		
		return true;
	}
	// 2. 查找
	HashNode<K, V>* find(const K& key)
	{
		int idx = key % _table.size();
		// 遇空查找结束
		while (_table[idx]._state != EMPTY)
		{
			// 只有状态为存在的数据有效
			if (_table[idx]._state == EXIST && _table[idx]._value.first == key)
				return &_table[idx];
			idx++;
			if (idx == _table.size())
				idx = 0;
		}
		return nullptr;
	}
	// 3. 删除
	bool erase(const K& key)
	{
		HashNode<K, V>* tar = find(key);

		if (tar == nullptr) return false;

		// 只修改状态
		tar->_state = DELETE;
		_size--;

		return true;
	}
	// 4. 检查容量，增容
	void checkCapacity()
	{
		// 负载因子为 0.7 超过需要增容
		if (_size * 10 / _table.size() >= 7)
		{
			HashTable ht(2 * _table.size());
			// 更新元素在哈希表中的位置
			for (int i = 0; i < _table.size(); i++)
			{
				if (_table[i]._state == EXIST)
					ht.insert(_table[i]._value);
			}
			// 函数推出前 临时变量 ht 会调用析构，进而 vector 会清除原来的 _table 资源  
			swap(ht._table, _table);
		}
	}

private:
	vector<HashNode<K, V>> _table;
	// 已经使用的空间
	size_t _size;
};

int main(void)
{
	HashTable<int, int> ht;

	ht.insert(make_pair(1, 1));
	ht.insert(make_pair(3, 3));
	ht.insert(make_pair(4, 4));
	ht.insert(make_pair(5, 5));
	ht.insert(make_pair(7, 7));

	HashNode<int, int>* p1 =  ht.find(7);
	HashNode<int, int>* p2 = ht.find(8);
	
//	ht.erase(1);

	ht.insert(make_pair(8, 8));
	ht.insert(make_pair(9, 9));
	ht.insert(make_pair(10, 10));


	return 0;
}


