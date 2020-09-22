#include"stack.h"
#include<iostream>
#include<ctime>
#include<cstdlib>

const int NUM = 5;

int main()
{
	std::srand(std::time(0));

	Stack<const char*> st;

	const char* in[NUM] = {
		"1. He who has health has hope",
		"2. A rolling stone gathers no moss",
		"3. It never rains but pours",
		"4. Look before you leap",
		"5. Habit is second nature",
	};
	
	const char* out[NUM];

	int processed = 0;
	int nextin = 0;

	while (processed < NUM)
	{
		// 如果栈为空，入栈
		if (st.IsEmpty())
			st.push(in[nextin++]);
		// 如果栈为空，出栈
		else if (st.IsFull())
		{
			out[processed++] = st.top();
			st.pop();
		}
		// 栈非空，非满。随机执行入栈出栈操作
		else if (std::rand() % 2 && nextin < NUM)
			st.push(in[nextin++]);
		else
		{
			out[processed++] = st.top();
			st.pop();
		}
	}

	for (int i = 0; i < NUM; i++)
		std::cout << out[i] << std::endl;

	return 0;
}

