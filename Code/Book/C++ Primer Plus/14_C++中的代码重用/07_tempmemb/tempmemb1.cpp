#include<iostream>

using namespace std;

template<class T>
class Beta
{
private:
	template<class V>
	class Hold
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
	Hold<T> q;
	Hold<int> n;

public:
	Beta(T t, int i)
		:q(t)
		,n(i)
	{}

	template<class U>
	U blab(U u, T t)
	{
		return (n.Value() + q.Value()) / t;
	}

	void Show() const
	{
		q.show();
		n.show();
	}
};

int main(void)
{
	Beta<double> guy(3.5, 3);

	guy.Show();

	cout << guy.blab(10.0, 2.3) << endl;
}