#include<iostream>

using namespace std;

template<class T>
class Beta
{
private:
	// ÉùÃ÷
	template<class V>
	class Hold;

	Hold<T> q;
	Hold<int> n;

public:
	Beta(T t, int i)
		:q(t)
		,n(i)
	{}

	template<class U>
	U blab(U u, T t);


	void Show() const
	{
		q.show();
		n.show();
	}
};

template<class T>
template<class V>
class Beta<T>::Hold
{
	private:
		V val;
	public:
		Hold(V v = 0)
			:val(v)
		{}
		void show() const
		{
			cout << val << endl;
		}
		V Value() const
		{
			return val;
		}

};

template<class T>
template<class U>
U Beta<T>::blab(U u, T t)
{
	return (n.Value() + q.Value()) / t;
}

int main(void)
{
	Beta<double> guy(3.5, 3);

	guy.Show();

	cout << guy.blab(10.0, 2.3) << endl;
}