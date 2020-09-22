#include<iostream>
#include<string>

template<class T1, class T2>
class Pair
{
private:
	T1 _a;
	T2 _b;
public:
	T1& first();
	T2& second();
	T1 first() const { return _a; }
	T2 second() const { return _b; }
	Pair(){}
	Pair(const T1& a, const T2& b )
		:_a(a)
		,_b(b)
	{}
};

template<class T1, class T2>
T1& Pair<T1, T2>::first()
{
	return _a;
}

template<class T1, class T2>
T2& Pair<T1, T2>::second()
{
	return _b;
}

int main(void)
{
	Pair<std::string, int> p("Shepard", 10);

	std::cout << p.first() << " " << p.second() << std::endl;

	return 0;
}
