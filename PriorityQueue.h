#pragma once
#include"PriQueueNode.h"
template<class t>
class PriorityQueue
{
private:
	PriQueueNode<t>* front;
	int count;
public:
	PriorityQueue()
	{
		count = 0;
		front = NULL;
	}
	PriorityQueue(const PriorityQueue& p)
	{
		if (p.front == NULL)
			front = NULL;
		else
		{
			front = new PriQueueNode<t>(p.front->getData());
			front->setPriority(p.front->getPriority());
			PriQueueNode<t>* pn1 = p.front;
			PriQueueNode<t>* pn2 = front;
			pn1 = pn1->getNext();
			while (pn1 != NULL)
			{
				pn2->setNext(new PriQueueNode<t>(pn1->getData()));
				pn2 = pn2->getNext();
				pn2->setPriority(pn1->getPriority());
				pn1 = pn1->getNext();

			}
		}
		count = p.count;
	}
	PriorityQueue& operator=(const PriorityQueue& p)
	{
		destroy();
		if (p.front == NULL)
			front = NULL;
		else
		{
			front = new PriQueueNode<t>(p.front->getData());
			front->setPriority(p.front->getPriority());
			PriQueueNode<t>* pn1 = p.front;
			PriQueueNode<t>* pn2 = front;
			pn1 = pn1->getNext();
			while (pn1 != NULL)
			{
				pn2->setNext(new PriQueueNode<t>(pn1->getData()));
				pn2 = pn2->getNext();
				pn2->setPriority(pn1->getPriority());
				pn1 = pn1->getNext();

			}
		}
		count = p.count;
		return*this;
	}

	bool isEmpty()
	{
		return count == 0;
	}
	bool enqueue(t val,int pri)
	{
		PriQueueNode<t>* newPriQueueNode=NULL;
		PriQueueNode<t>* tmp;
		if (newPriQueueNode = new PriQueueNode<t>(pri))
		{
			newPriQueueNode->setData(val);
			if (count == 0)
			{
				front = newPriQueueNode;
				front->setNext(NULL);
			}
			else
			{
				if (front->getPriority() < newPriQueueNode->getPriority())
				{
					newPriQueueNode->setNext(front);
					front = newPriQueueNode;
				}
				else
				{
					tmp = front;
					while (tmp->getNext() && tmp->getNext()->getPriority() > newPriQueueNode->getPriority())
					{
						tmp = tmp->getNext();
					}
					newPriQueueNode->setNext(tmp->getNext());
					tmp->setNext(newPriQueueNode);
				}
			}
			count++;
			return true;
		}
		else
			return false;
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
			return true;
		}
		PriQueueNode<t>* del = front;
		front = front->getNext();
		delete del;
		return true;
	}
	void destroy()
	{
		while (!isEmpty())
			dequeue();
	}
	t peekFront(int &priority)
	{
		priority = front->getPriority();
		return front->getData();
	}
	~PriorityQueue()
	{
		destroy();
	}
	int getCount() const
	{
		return count;
	}
};

