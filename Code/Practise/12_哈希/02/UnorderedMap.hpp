//#include"HashTable.hpp"
//
//template<class K, class V>
//class UnorderedMap
//{
//	// 私有，尽在此类中使用
//	struct MapKeyOfValue
//	{
//		const K& operator()(const pair<K, V>& val)
//		{
//			return val.first;
//		}
//	};
//public:
//	bool insert(const pair<K, V>& val)
//	{
//		return _hashTable.insert(val);
//	}
//private:
//	HashTable<K, pair<K, V>, MapKeyOfValue> _hashTable;
//};