#include<iostream>
#include"Queue.h"

Queue::Queue(int qs)
	:front(nullptr)
	,rear(nullptr)
	,cnt(0)
	,qsize(qs)
{}

Queue::~Queue()
{
	Node* cur = front;
	while (cur != nullptr)
	{
		Node* next = cur->next;
		delete cur;
		cur = next;
	}
	front = rear = nullptr;
	cnt = 0;
}

bool Queue::IsEmpty() const
{
	return cnt == 0;
}

bool Queue::IsFull() const
{
	return cnt == qsize;
}

int Queue::QueueCount() const
{
	return cnt;
}

bool Queue::EnQueue(const Item& it)
{
	if (!IsFull())
	{
		Node* add = new Node;
		add->item = it;
		add->next = nullptr;
		
		// 空表，第一次插入
		if (cnt == 0)
		{
			front = rear = add;
		}
		else
		{
			rear->next = add;
			rear = add;
		}
		cnt++;
		return true;
	}
	return false;
}

bool Queue::DeQueue(Item& it)
{
	if (!IsEmpty())
	{
		Node* del = front;
		cnt--;
		if (qsize == 1)
		{
			delete del;
			front = rear = nullptr;
		}
		else
		{
			it = del->item;
			
			front = del->next;
			delete del;
		}

		return true;
	}
	return false;
}

void Queue::Show() const
{
	Node* cur = front;
	while (cur != nullptr)
	{
		std::cout << cur->item << " ";
		cur = cur->next;
	}
	std::cout << std::endl;
}

