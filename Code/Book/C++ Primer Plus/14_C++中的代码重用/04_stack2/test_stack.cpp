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
		// ���ջΪ�գ���ջ
		if (st.IsEmpty())
			st.push(in[nextin++]);
		// ���ջΪ�գ���ջ
		else if (st.IsFull())
		{
			out[processed++] = st.top();
			st.pop();
		}
		// ջ�ǿգ����������ִ����ջ��ջ����
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

