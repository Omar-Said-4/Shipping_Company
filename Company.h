#pragma once
#include"Node.h"
#include "cargo.h"
#include "trucks.h"
#include "QueueLinkedList.h"
#include "PriorityQueue.h"
#include "Events.h"
#include<fstream>
#include<iostream>
#include"Events.h"
#include"PreparationEvent.h"
#include"CancelEvent.h"
#include"PrompteEvent.h"
#include<string>
#include"UI.h"
#include <math.h>
using namespace std;
class Company
{

private:
	ifstream file;
	bool LoadTrucks(QueueLinkedList<trucks*>& normal, QueueLinkedList<trucks*>& special, QueueLinkedList<trucks*>& vip);
	bool LoadEvents(QueueLinkedList<Events*>& events);
	bool LoadMaxw_Autop(int& MaxW, int& AutoP);
	int MaxW;
	int AutoP;
	int assignmentCounter;
	bool assignedVip;
	bool assignedNormal;
	bool assignedSpecial;
	int hour;
	int day;
	UI Interface;
	// time setters

	QueueLinkedList<trucks*>VIP_trucks; //
	QueueLinkedList<trucks*>NORMAL_trucks;
	QueueLinkedList<trucks*>SPECIAL_trucks;
	QueueLinkedList<Events*>events;

	//trucks
	PriorityQueue<trucks*>MOVINGVIP_trucks;
	PriorityQueue<trucks*>LOADINGVIP_trucks;
	PriorityQueue<trucks*>CHECKUPVIP_trucks;

	PriorityQueue<trucks*>MOVINGSPECIAL_trucks;
	PriorityQueue<trucks*>LOADINGSPECIAL_trucks;
	PriorityQueue<trucks*>CHECKUPSPECIAL_trucks;

	PriorityQueue<trucks*>MOVINGNORMAL_trucks;
	PriorityQueue<trucks*>LOADINGNORMAL_trucks;
	PriorityQueue<trucks*>CHECKUPNORMAL_trucks;
	//end trucks

	//CARGOS
	PriorityQueue<cargo*>MOVINGVIP_cargos;

	PriorityQueue<cargo*>MOVINGSPECIAL_cargos;

	PriorityQueue<cargo*>MOVINGNORMAL_cargos;

	QueueLinkedList<cargo*>DELIVERED_cargos;
	// END CARGOS


	PriorityQueue<cargo*>VIP_cargos;
	QueueLinkedList<cargo*>NORMAL_cargos;
	QueueLinkedList<cargo*>SPECIAL_cargos;

	QueueLinkedList<cargo*>* waitCargos[2] = { &SPECIAL_cargos,&NORMAL_cargos };
	PriorityQueue<cargo*>* moveCargos[3] = { &MOVINGVIP_cargos,&MOVINGSPECIAL_cargos,&MOVINGNORMAL_cargos };

	QueueLinkedList<trucks*>* waitTrucks[3] = { &NORMAL_trucks,&SPECIAL_trucks,&VIP_trucks };
	PriorityQueue<trucks*>* loadTrucks[3] = { &LOADINGNORMAL_trucks,&LOADINGSPECIAL_trucks,&LOADINGVIP_trucks };
	PriorityQueue<trucks*>* moveTrucks[3] = { &MOVINGNORMAL_trucks,&MOVINGSPECIAL_trucks,&MOVINGVIP_trucks };
	PriorityQueue<trucks*>* checkupTrucks[3] = { &CHECKUPNORMAL_trucks,&CHECKUPSPECIAL_trucks,&CHECKUPVIP_trucks };


	void extractDateTime(string x, Events* curEv);
	void augmentHour();
	void Work();
	void executeEvent();
	void CargoToLoading(int curType);
	void vipCargoToLoading(int priority);
	void CargoToMoving(trucks* curTruck, int priority);
	void CargoToDelivered(int curType);

	//phase 1 functions
	void CargoToDelivered_ph1();

	void TruckToLoading(int curType,int priority);
	void TruckToMoving(int curType);
	void TruckToCheckup(int curType);
	void TruckToAvailable(trucks* curTruck, LinkedList<trucks*>& ptrCheckOrMoving);
	void loadall(QueueLinkedList<trucks*>& normal, QueueLinkedList<trucks*>& special, QueueLinkedList<trucks*>& vip, QueueLinkedList<Events*>& events, int& MaxW, int& AutoP);



	template<class t>
	void delQueue(QueueLinkedList<t>& x);

	template<class t>
	void delPQueue(PriorityQueue<t>& x);


	//PRIORITIES
	int getVipPriority(cargo* vipCargo);
	int getLoadingPriority(trucks* Truck,int loadTime);
	int getCargoMovingPriority(trucks* Truck, cargo* Cargo,int accLoadTime);
	int getTruckMovingPriority(trucks* Truck);
	int getTruckCheckUpPriority(trucks* Truck);
	int getMax(int x, int y);

	bool workingHours();
	void assign();
	void Moving();
	void Deliver();
	void Returntrucks();
	void backFromCheckup();
public:
	Company(string name);
	~Company();
	void Update();// Test Function

};

template<class t>
inline void Company::delQueue(QueueLinkedList<t>& x)
{
	while (!x.isEmpty())
	{
		auto tmp = x.peekFront();
		delete tmp;
		x.dequeue();
	}
}

template<class t>
inline void Company::delPQueue(PriorityQueue<t>& x)
{
	int garb;
	while (!x.isEmpty())
	{
		auto tmp = x.peekFront(garb);
		delete tmp;
		x.dequeue();
	}
}
