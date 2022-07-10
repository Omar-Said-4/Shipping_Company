#include "PreparationEvent.h"
PreparationEvent::PreparationEvent(cargoType t, unsigned short l, unsigned int d, int c, int i)
	:Type(t), loadTime(l), deliveryDistance(d), cost(c), id(i)
{

}
bool PreparationEvent::execute(PriorityQueue<cargo*>& vip, QueueLinkedList<cargo*>& special, QueueLinkedList<cargo*>& normal)
{
	cargo* evcargo;
	evcargo = new cargo(id);
	evcargo->setCargoType(Type);
	evcargo->setCost(cost);
	evcargo->setLoadTime(loadTime);
	evcargo->setDeliveryDistance(deliveryDistance);
	evcargo->setTime(getDay(), getTime());
	switch (Type)
	{
	case NORMAL:
		normal.enqueue(evcargo);
		break;
	case VIP:
		vip.enqueue(evcargo, 0);
		break;
	case SPECIAL:
		special.enqueue(evcargo);
		break;
	}
	return true;
}
PreparationEvent::~PreparationEvent()
{

}