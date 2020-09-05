//#include<map>
//#include<unordered_map>
//
//#include<iostream>
//
//#include<set>
//#include<unordered_set>
//
//using namespace std;
//
//void test1()
//{
//	map<int, int> m;
//	unordered_map<int, int> um;
//
//	m.insert(make_pair(1, 1));
//	m.insert(make_pair(2, 2));
//	m.insert(make_pair(4, 4));
//	m.insert(make_pair(5, 5));
//	m.insert(make_pair(3, 3));
//
//	um.insert(make_pair(1, 1));
//	um.insert(make_pair(2, 2));
//	um.insert(make_pair(4, 4));
//	um.insert(make_pair(5, 5));
//	um.insert(make_pair(3, 3));
//
//	// 迭代器按中序遍历
//	cout << "======== map ======== " << endl;
//	map<int, int>::iterator it = m.begin();
//	while (it != m.end())
//	{
//		cout << it->first << " " << it->second << " ";
//		it++;
//	}
//	cout << endl;
//
//	// 迭代器遍历无序,顺序随机（不一定是插入的顺序）
//	cout << "======== unordered_map ======== " << endl;
//	unordered_map<int, int>::iterator uit = um.begin();
//	while (uit != um.end())
//	{
//		cout << uit->first << " " << uit->second << endl;
//		uit++;
//	}
//	
//	// unordered_map 没有反向迭代器
//
//	cout << "======== operator[] & at() ======== " << endl;
//	// operator[] 读写 + 插入
//	um[5] = 6;
//	um[6] = 6;
//
//	// at() 插入
//	um.at(1) = 0;
//	//um.at(7) = 8; // 抛出异常
//
//	uit = um.begin();
//	while (uit != um.end())
//	{
//		cout << uit->first << " " << uit->second << endl;
//		uit++;
//	}
//
//	cout << "======== find() & count() ======== " << endl;
//	// 返回 key 对应的迭代器，如果没有找到返回 end()
//	uit = um.find(6);
//	cout << uit->first << " " << uit->second << endl;
//	uit = um.find(7);
//	cout << (uit == um.end()) << endl;
//	// 返回 key 为 6 总数
//	cout << um.count(6) << endl;
//	
//}
//
///*
// *	测试 insert 如何初始化 value
// */
//void test2()
//{	
//	map<int, int> m;
//	
//
//}
//
//int main(void)
//{	
//	test2();
//
//	return 0;
//}