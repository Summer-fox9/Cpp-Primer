#pragma once
#include"BitMap.hpp"

template<class T, class HF1, class HF2, class HF3>
class BloomFilter
{
public:
	// bit位数量 = 哈希函数个数 * 数据量 / ln2
	BloomFilter(size_t num)
		:_bit(5 * num)
		,_size(5 * num)
	{}

	bool Test(const T& val)
	{
		HF1 hf1;
		HF2 hf2;
		HF3 hf3;
		size_t hashCode1 = hf1(val);
		size_t hashCode2 = hf2(val);
		size_t hashCode3 = hf3(val);

		// 只要一个比特位为 0，则说明该数据不存在
		if (!_bit.Test(hashCode1 % _size))
			return false;
		if (!_bit.Test(hashCode2 % _size))
			return false;
		if (!_bit.Test(hashCode3 % _size))
			return false;

		return true;
	}

	void Set(const T& val)
	{
		HF1 hf1;
		HF2 hf2;
		HF3 hf3;
		size_t hashCode1 = hf1(val);
		size_t hashCode2 = hf2(val);
		size_t hashCode3 = hf3(val);

		_bit.Set(hashCode1 % _size);
		_bit.Set(hashCode2 % _size);
		_bit.Set(hashCode3 % _size);
	}
private:
	BitMap _bit;
	size_t _size;
};

struct StrToInt1
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto& ch : str)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};

struct StrToInt2
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		for (auto& ch : str)
		{
			hash = hash * 65599 + ch;
		}
		return hash;

	}
};

struct StrToInt3
{
	size_t operator()(const string& str)
	{
		size_t hash = 0;
		size_t magic = 63689;
		for (auto& ch : str)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};
