#pragma once
#include"QueueLinkedList.h"
#include"PriorityQueue.h"
#include"Events.h"
class CancelEvent :public Events
{
	int id;
public:
	CancelEvent(int Id);
	virtual bool execute(PriorityQueue<cargo*>& vip, QueueLinkedList<cargo*>& special, QueueLinkedList<cargo*>& normal);
};

