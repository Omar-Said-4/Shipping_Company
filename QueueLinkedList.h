#pragma once
#include<iostream>
using namespace std;
#include"Node.h"
template<class t>
class QueueLinkedList
{
private:
	Node<t>* front;
	Node<t>* rear;
	int count;
public:
	QueueLinkedList(const QueueLinkedList& q)
	{
		if (q.front == NULL)
		{
			front = NULL;
			rear = NULL;
		}
		else
		{
			front = new Node<t>(q.front->getData());
			rear = front;
			Node<t>* pn1 = q.front;
			pn1 = pn1->getNext();
			while (pn1 != NULL)
			{
				rear->setNext(new Node<t>(pn1->getData()));
				rear = rear->getNext();
				pn1 = pn1->getNext();
			}
		}
		count = q.count;
	}
	QueueLinkedList& operator=(const QueueLinkedList& q)
	{
		destroy();
		count = q.count;
		if (q.front == NULL)
		{
			front = NULL;
			rear = NULL;
		}
		else
		{
			front = new Node<t>(q.front->getData());
			rear = front;
			Node<t>* pn1 = q.front;
			pn1 = pn1->getNext();
			while (pn1 != NULL)
			{
				rear->setNext(new Node<t>(pn1->getData()));
				rear = rear->getNext();
				pn1 = pn1->getNext();
			}
		}
		return*this;
	}
	QueueLinkedList()
	{
		count = 0;
		front = NULL;
		rear = NULL;
	}
	bool isEmpty()
	{
		return count == 0;
	}
	bool enqueue(t val)
	{
		Node<t>* newnode = new Node<t>;
		newnode->setData(val);
		newnode->setNext(NULL);
		if (newnode)
		{
			if (count == 0)
				rear = front = newnode;
			else
			{
				rear->setNext(newnode);
				rear = newnode;
			}
			count++;
			return true;
		}
		else return false;

	}
	bool dequeue()
	{
		if (isEmpty())
			return false;
		count--;
		if (count == 0)
		{
			delete front;
			front = NULL;
			rear = NULL;
			return true;
		}
		Node<t>* del = front;
		front = front->getNext();
		delete del;
		return true;
	}
	void destroy()
	{
		while (!isEmpty())
			dequeue();
	}
	t peekFront()
	{
		//ADDED 5/25
	//	if (!isEmpty())
			return front->getData();
	}
	~QueueLinkedList()
	{
		destroy();
	}
	int getCount()
	{
		return count;
	}
};

