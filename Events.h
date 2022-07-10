#pragma once
#include"cargo.h"
#include"QueueLinkedList.h"
#include"PriorityQueue.h"
class Events
{
private:
	unsigned int day;
	unsigned int time;
protected:
public:
	Events();
	void setDay(int d);
	void setTime(int t);
	unsigned int getDay() const;
	unsigned int getTime()const;
	virtual bool execute(PriorityQueue<cargo*>& vip, QueueLinkedList<cargo*>& special, QueueLinkedList<cargo*>& normal) = 0;
	~Events();
};
// Adapt time function