#include "PrompteEvent.h"
bool PrompteEvent::execute(PriorityQueue<cargo*>& vip, QueueLinkedList<cargo*>& special, QueueLinkedList<cargo*>& normal)
{
	cargo* promote = nullptr;
	cargo* tmp = nullptr;
	QueueLinkedList<cargo*>temp;
	while (!normal.isEmpty())
	{
		tmp = normal.peekFront();
		normal.dequeue();
		if (tmp->getId() == id)
		{
			promote = tmp;
		}
		else
			temp.enqueue(tmp);
	}
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront();
		temp.dequeue();
		normal.enqueue(tmp);
	}
	if (promote)
	{
		promote->setCargoType(VIP);
		vip.enqueue(promote, getVipPriority(promote));
		promote->setCost(promote->getCost() + extraMoney);
	}
	return true;
}
PrompteEvent::PrompteEvent(int Id, int m)
	:id(Id), extraMoney(m)
{

}
int PrompteEvent::getVipPriority(cargo* vipCargo)
{
	int cost = vipCargo->getCost();
	int dist = vipCargo->getDeliveryDistance();
	int days;
	int hours;
	vipCargo->getTime(days, hours);
	int eq = 1000 * cost + 100 * dist + (24 * days + hours);
	return eq;
}
