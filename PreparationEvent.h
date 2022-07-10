#pragma once
#include"Events.h"
#include"QueueLinkedList.h"
#include"PriorityQueue.h"
class PreparationEvent :public Events
{
private:
    cargoType Type;
    unsigned short loadTime;
    unsigned int deliveryDistance;
    unsigned int cost;
    int id;
public:
    PreparationEvent(cargoType t, unsigned short l, unsigned int d, int c, int i);
    virtual bool execute(PriorityQueue<cargo*>& vip, QueueLinkedList<cargo*>& special, QueueLinkedList<cargo*>& normal);
    ~PreparationEvent();
};

