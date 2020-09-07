#include<iostream>
#include"UnorderedMap.hpp"
//#include"BitMap.hpp"
#include"BloomFilter.hpp"

using namespace std;

void testMap()
{
	UnorderedMap<int, int, KeyIsInt<int>> um;

	um.insert(make_pair(1, 1));
	um.insert(make_pair(2, 2));
	um.insert(make_pair(3, 3));
	um.insert(make_pair(5, 5));
	um.insert(make_pair(7, 7));
	
	um[7] = 10;

}

void testBitMap()
{
	BitMap bit(100);

	bit.Set(4);
	bit.Set(31);
	bit.Set(48);

	bool ret = bit.Test(4);
	ret = bit.Test(31);
	ret = bit.Test(48);
	ret = bit.Test(25);

	bit.Reset(31);
	bit.Reset(4);
	bit.Reset(48);
}

void testBloomFilter()
{
	BloomFilter<string, StrToInt1, StrToInt2, StrToInt3> bf(300);

	string str1 = "https://docs.microsoft.com/zh-cn/cpp/error-messages/compiler-errors-1/compiler-error-c2440?f1url=%3FappId%3DDev16IDEF1%26l%3DZH-CN%26k%3Dk(C2440)%26rd%3Dtrue&view=vs-2019";
	string str2 = "https://docs.microsoft.com/zh-cn/cpp/error-messages/compiler-errors-1/compiler-error-c2440?f1url=%3FappId%3DDev16IDEF1%26l%3DZH-CN%26k%3Dk(C2440)%26rd%3Dtrue&view=vs-2018";
	string str3 = "https://docs.microsoft.com/zh-cn/cpp/error-messages/compiler-errors-1/compiler-error-c2440?f1url=%3FappId%3DDev16IDEF1%26l%3DZH-CN%26k%3Dk(C2440)%26rd%3Dtrue&view=vs-2017";

	string str4 = "https://docs.microsoft.com/zh-cn/cpp/error-messages/compiler-errors-1/compiler-error-c2440?f1url=%3FappId%3DDev16IDEF1%26l%3DZH-CN%26k%3Dk(C2440)%26rd%3Dtrue&view=vs-2020";
	string str5 = "https://docs.microsoft.com/zh-cn/cpp/error-messages/compiler-errors-1/compiler-error-c2440?f1url=%3FappId%3DDev16IDEF1%26l%3DZH-CN%26k%3Dk(C2440)%26rd%3Dtrue&view=vs-2021";
	

	bf.Set(str1);
	bf.Set(str2);
	bf.Set(str3);

	bool ret = bf.Test(str1);
	ret = bf.Test(str2);
	ret = bf.Test(str3);
	ret = bf.Test(str4);
	ret = bf.Test(str5);
}

void testBit()
{
	int _bit[3] = { 1, 4, 1 };
	int idx = 1;
	int bitIdx = 2;

	int a = _bit[idx] & (1 << bitIdx);
	a = (_bit[idx] >> bitIdx) & 1;
}

int main(void)
{
	//testMap();
	//testBitMap();
	testBloomFilter();
	//testBit();

	return 0;
}