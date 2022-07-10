#pragma once
#include"Events.h"
#include"QueueLinkedList.h"
#include"PriorityQueue.h"
class PrompteEvent :public Events
{
	int extraMoney;
	int id;
	int getVipPriority(cargo* vipCargo);
public:
	virtual bool execute(PriorityQueue<cargo*>& vip, QueueLinkedList<cargo*>& special, QueueLinkedList<cargo*>& normal);
	PrompteEvent(int Id, int m);

};

