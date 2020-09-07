#include<iostream>
#include<vector>

using namespace std;

class BitMap
{
public:
	BitMap(size_t range)
	{
		// 如果范围小于 32，range / 32 为 0 
		_bit.resize(range / 32 + 1);
	}

	// 查找
	bool Test(size_t n)
	{
		// 整数的位置
		int idx = n / 32;
		// 在整数中的比特位
		int bitIdx = n % 32;

		// 下面两种写法都可以
		if ((_bit[idx] & (1 << bitIdx))) // 不要写 == 1，因为 & 的结果不一定等于 1
		//if( ( (_bit[idx] >> bitIdx) & 1) == 1 )
			return true;
		else
			return false;
	}

	// 设置
	void Set(size_t n)
	{
		int idx = n / 32;
		int bitIdx = n % 32;

		_bit[idx] |= (1 << bitIdx);
	}

	// 删除
	void Reset(size_t n)
	{
		int idx = n / 32;
		int bitIdx = n % 32;

		_bit[idx] &= ~(1 << bitIdx);
	}
private:
	vector<int> _bit;
};