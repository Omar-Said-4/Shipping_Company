#include "CancelEvent.h"
bool CancelEvent::execute(PriorityQueue<cargo*>& vip, QueueLinkedList<cargo*>& special, QueueLinkedList<cargo*>& normal)
{
	cargo* cancel = nullptr;
	cargo* tmp;
	QueueLinkedList<cargo*>temp;
	while (!normal.isEmpty())
	{
		tmp = normal.peekFront();
		normal.dequeue();
		if (tmp->getId() == id)
		{
			cancel = tmp;
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
	if (cancel)
	{
		delete cancel;
		cancel = nullptr;
		return true;
	}
	return false;
}
CancelEvent::CancelEvent(int Id)
	:id(Id)
{
}
