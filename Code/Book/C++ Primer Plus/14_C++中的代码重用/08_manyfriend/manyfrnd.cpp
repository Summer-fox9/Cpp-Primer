#include<iostream>

using namespace std;

template<class T>
class ManyFriend
{
private:
	T _item;
public:
	ManyFriend(const T& i)
		:_item(i)
	{}
	template<class C, class D> friend void show(C&, D&);
};

template<class C, class D>
void show(C& c, D& d)
{
	cout << c._item << " " << d._item << endl;
}

int main(void)
{
	ManyFriend<int> m1(10);
	ManyFriend<int> m2(20);
	ManyFriend<double> m3(30.5);

	show(m1, m2);
	//  void show<ManyFriend<int>, ManyFriend<int>>(ManyFriend<int> & c, ManyFriend<int> & d)
	show(m2, m3);
	//  void show<ManyFriend<int>, ManyFriend<double>>(ManyFriend<int> & c, ManyFriend<double> & d)
	return 0;
}