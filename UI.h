#pragma once
#include"trucks.h"
#include<iostream>
#include"PriorityQueue.h"
#include"QueueLinkedList.h"
#include"cargo.h"
#include"Events.h"
#include<fstream>
using namespace std;
class UI
{
	void printTime(int day, int hour);
	void printWaitingCargos(QueueLinkedList<cargo*>& normal, QueueLinkedList<cargo*>& special, PriorityQueue<cargo*>& vip);
	void printLoadingTrucks(PriorityQueue<trucks*>& normal, PriorityQueue<trucks*>& special, PriorityQueue<trucks*>& vip);
	void printEmptyTrucks(QueueLinkedList<trucks*>& normal, QueueLinkedList<trucks*>& special, QueueLinkedList<trucks*>& vip);
	void printMovingCargos(PriorityQueue<trucks*>& normal, PriorityQueue<trucks*>& special, PriorityQueue<trucks*>& vip);
	void printIncheckupTrucks(PriorityQueue<trucks*>& normal, PriorityQueue<trucks*>& special, PriorityQueue<trucks*>& vip);
	void printDeliveredCargos(QueueLinkedList<cargo*>& cargos);
public:
	void printAll(int day, int hour,
		QueueLinkedList<cargo*>& wcnormal, QueueLinkedList<cargo*>& wcspecial, PriorityQueue<cargo*>& wcvip,
		PriorityQueue<trucks*>& ltnormal, PriorityQueue<trucks*>& ltspecial, PriorityQueue<trucks*>& ltvip,
		QueueLinkedList<trucks*>& etnormal, QueueLinkedList<trucks*>& etspecial, QueueLinkedList<trucks*>& etvip,
		PriorityQueue<trucks*>& mcnormal, PriorityQueue<trucks*>& mcspecial, PriorityQueue<trucks*>& mcvip,
		PriorityQueue<trucks*>& incnormal, PriorityQueue<trucks*>& incspecial, PriorityQueue<trucks*>& incvip,
		QueueLinkedList<cargo*>& dc
	);
	void output(QueueLinkedList<cargo*>& wcnormal, QueueLinkedList<cargo*>& wcspecial, PriorityQueue<cargo*>& wcvip,
		PriorityQueue<trucks*>& ltnormal, PriorityQueue<trucks*>& ltspecial, PriorityQueue<trucks*>& ltvip,
		QueueLinkedList<trucks*>& etnormal, QueueLinkedList<trucks*>& etspecial, QueueLinkedList<trucks*>& etvip,
		PriorityQueue<trucks*>& mcnormal, PriorityQueue<trucks*>& mcspecial, PriorityQueue<trucks*>& mcvip,
		PriorityQueue<trucks*>& incnormal, PriorityQueue<trucks*>& incspecial, PriorityQueue<trucks*>& incvip, QueueLinkedList<cargo*>& dc,
		unsigned int cDay, unsigned int cHour);
	int getMode();
	void space();
	void Off();
	UI();
};

