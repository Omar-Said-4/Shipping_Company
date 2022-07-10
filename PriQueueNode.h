#pragma once
template<class t>
class PriQueueNode
{
private:
	int priority;
	t data;
	PriQueueNode<t>* next;
public:
	PriQueueNode(int a=0)
	{
		priority = a;
	}
	PriQueueNode(t dat)
	{
		data = dat;
		next = NULL;
	}
	void setData(t val) { data = val; }
	t getData() { return data; }
	void setNext(PriQueueNode<t>* nxt) { next = nxt; }
	void setPriority(int a) { priority = a; }
	int getPriority() { return priority; }
	PriQueueNode<t>* getNext() { return next; }

};

