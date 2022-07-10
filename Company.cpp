#include "Company.h"
#include <chrono>
#include <thread>
void Company::extractDateTime(string x, Events* curEv)
{
	int i = 0;
	string tmp = "";
	while (x[i] != ':')
	{
		tmp += x[i];
		i++;
	}
	curEv->setDay(stoi(tmp));
	tmp = "";
	i++;
	while (x[i] != '\0')
	{
		tmp += x[i];
		i++;
	}
	curEv->setTime(stoi(tmp));
}

void Company::augmentHour()
{
	hour++;
	if (hour == 24)
	{
		day++; hour = 0;
	}
}



bool Company::workingHours()
{
	return (hour >= 5 && hour <= 23);
}


int Company::getVipPriority(cargo* vipCargo)
{
	int cost = vipCargo->getCost();
	int dist = vipCargo->getDeliveryDistance();
	int days;
	int hours;
	vipCargo->getTime(days, hours);
	int eq = 100 * cost + 10 * dist + (24 * days + hours);
	return eq;
}

int Company::getLoadingPriority(trucks* Truck, int loadStartHours)
{
	PriorityQueue<cargo*> tmpCargos = Truck->getCarriedCargos();
	int maxLT = 0;
	while (!tmpCargos.isEmpty())
	{
		int val;
		Truck->addcargosNumber();
		maxLT = getMax(maxLT, tmpCargos.peekFront(val)->getLoadTime());
		tmpCargos.dequeue();
		//if (loadStartHours >= 0 && loadStartHours < 5)
			//maxLT += loadStartHours;
	}
	Truck->setActiveTime(maxLT);
	int eq = (loadStartHours + maxLT);
	//int rem = eq;
	//rem%24
	//while (rem 2> 4)
	//{
	//	rem -= 24;
	//}
	//if (rem < 5)
	//	{rem = 6 - rem;
	//eq += rem;}
	if (eq % 24 < 5)
		eq += 6;
	Truck->setLoadedtime(eq);
	tmpCargos = Truck->getCarriedCargos();
	while (!tmpCargos.isEmpty())
	{
		int val;
		tmpCargos.peekFront(val)->setloadedtime(eq);
		int cargD = 0, cargH = 0;
		tmpCargos.peekFront(val)->getTime(cargD, cargH);
		tmpCargos.peekFront(val)->setWaitedTime(loadStartHours - cargD * 24 - cargH);
		tmpCargos.dequeue();
	}

	return -eq;
}

int Company::getCargoMovingPriority(trucks* Truck, cargo* Cargo, int accLoadTime)
{
	int days;
	int hours;
	Truck->getLoadedTime(days, hours);
	int eq = (days * 24 + hours + ceil((double)Cargo->getDeliveryDistance() / Truck->getSpeed()) + Cargo->getLoadTime() + accLoadTime);

	Cargo->setDeliverytime(eq);

	return -eq;
}

int Company::getTruckMovingPriority(trucks* Truck)

{
	int days;
	int hours;
	Truck->getLoadedTime(days, hours);
	PriorityQueue<cargo*> tmpCargos = Truck->getCarriedCargos();
	int moveStart = days * 24 + hours;
	int maxDist = INT_MIN;
	int tmpval;
	int loadTimeSum = 0;
	while (!tmpCargos.isEmpty())
	{
		maxDist = getMax(maxDist, tmpCargos.peekFront(tmpval)->getDeliveryDistance());
		tmpCargos.dequeue();
	}
	int t = maxDist / Truck->getSpeed();
	Truck->setActiveTime(t);
	tmpCargos = Truck->getCarriedCargos();
	while (!tmpCargos.isEmpty())
	{
		loadTimeSum += tmpCargos.peekFront(tmpval)->getLoadTime();
		tmpCargos.dequeue();
	}
	int eq = (2 * ceil(((double)maxDist / Truck->getSpeed())) + loadTimeSum + moveStart);
	Truck->setDeliveredTime(eq);
	return -eq;
}

int Company::getTruckCheckUpPriority(trucks* Truck)
{
	int returnTime = Truck->getDeliveredTime();
	int mntTime = Truck->getMt();
	int eq = -(returnTime + mntTime);
	return eq;
}

int Company::getMax(int x, int y)
{
	return (x > y ? x : y);
}

Company::Company(string name)
{

	day = 1;
	hour = 0;
	int assignmentCounter = 0;
	assignedVip = false;
	assignedNormal = false;
	assignedSpecial = false;
	file.open(name);
	if (!file.is_open()) {
		cout << "Failed to open file" << endl;
	}
	else
		loadall(NORMAL_trucks, SPECIAL_trucks, VIP_trucks, events, MaxW, AutoP);
}

Company::~Company()
{
	delQueue(*waitCargos[0]);
	delQueue(*waitCargos[1]);
	delPQueue(VIP_cargos);
	delQueue(events);
	delQueue(DELIVERED_cargos);

	for (int i = 0; i < 3; i++)
	{
		delQueue(*waitTrucks[i]);
		delPQueue(*moveCargos[i]);
		delPQueue(*moveTrucks[i]);
		delPQueue(*checkupTrucks[i]);
		delPQueue(*loadTrucks[i]);
	}

}

void Company::Work()
{
	while (!events.isEmpty()) {
		executeEvent();
		//augmentHour();
	}
	return;
}

void Company::executeEvent()
{
	if (!events.isEmpty()) {
		Events* ev = events.peekFront();
		//>=
		while (ev->getDay() == day && ev->getTime() == hour)
		{
			ev->execute(VIP_cargos, SPECIAL_cargos, NORMAL_cargos);
			events.dequeue();
			if (!events.isEmpty())
				ev = events.peekFront();
			else break;
		}
	}
}

void Company::vipCargoToLoading(int priority)
{
	//0 vip
	int tmp;
	cargo* curCargo = VIP_cargos.peekFront(tmp);
	VIP_cargos.dequeue();
}
void Company::CargoToLoading(int curType)
{
	//0 vip
	cargo* curCargo = waitCargos[curType - 1]->peekFront();
	waitCargos[curType]->dequeue();
}

void Company::CargoToMoving(trucks* curTruck, int priority)
{
	//PriorityQueue<cargo*>tmppq = curTruck->getCarriedCargos();
	int val;
	int curType = curTruck->PeekCargo(val)->getCargoType();
	cargo* curCargo = curTruck->PeekCargo(val);
	moveCargos[curType]->enqueue(curCargo, priority);
	return;
}
/*void Company::CargoToDelivered_ph1()
{
	int whours, wdays;
	cargo* curCargo = nullptr;
	if (!NORMAL_cargos.isEmpty())
	{
		curCargo = NORMAL_cargos.peekFront();
		curCargo->getWaitingTime(hour, day, whours, wdays);
		if (whours == 5) {
			NORMAL_cargos.dequeue();
			DELIVERED_cargos.enqueue(curCargo);
		}
	}
	if (!SPECIAL_cargos.isEmpty())
	{
		curCargo = SPECIAL_cargos.peekFront();
		curCargo->getWaitingTime(hour, day, whours, wdays);
		if (whours == 5) {
			SPECIAL_cargos.dequeue();
			DELIVERED_cargos.enqueue(curCargo);
		}
	}
	if (!VIP_cargos.isEmpty())
	{
		int tmp;
		curCargo = VIP_cargos.peekFront(tmp);
		curCargo->getWaitingTime(hour, day, whours, wdays);
		if (whours == 5) {
			VIP_cargos.dequeue();
			DELIVERED_cargos.enqueue(curCargo);
		}
	}
}*/
void Company::CargoToDelivered(int curType)
{
	int tmp;
	if (!moveCargos[curType]->isEmpty()) {
		cargo* curCargo = moveCargos[curType]->peekFront(tmp);
		moveCargos[curType]->dequeue();
		DELIVERED_cargos.enqueue(curCargo);
	}
	return;
}

void Company::TruckToLoading(int curType, int priority)
{
	trucks* tmp = waitTrucks[curType]->peekFront();
	waitTrucks[curType]->dequeue();
	loadTrucks[curType]->enqueue(tmp, priority);
}

void Company::TruckToMoving(int curType)
{
	int k;
	trucks* tmp = loadTrucks[curType]->peekFront(k);
	loadTrucks[curType]->dequeue();
	moveTrucks[curType]->enqueue(tmp, 0);
	return;
}

void Company::TruckToCheckup(int curType)
{
	int tmp;
	trucks* curTruck = moveTrucks[curType]->peekFront(tmp);
	moveTrucks[curType]->dequeue();
	checkupTrucks[curType]->enqueue(curTruck, 0);
	return;

}

void Company::TruckToAvailable(trucks* curTruck, LinkedList<trucks*>& ptrCheckOrMoving)
{
	int curType = curTruck->getType();
	ptrCheckOrMoving.del(curTruck);
	waitTrucks[curType]->enqueue(curTruck);
}

bool Company::LoadTrucks(QueueLinkedList<trucks*>& normal, QueueLinkedList<trucks*>& special, QueueLinkedList<trucks*>& vip)
{
	QueueLinkedList<trucks*>* truckTypes[3]{ &normal,&special,&vip };
	if (file.is_open())
	{
		unsigned int ntrucks[3];
		unsigned int speed[3];
		unsigned int capacity[3];
		int nj;
		unsigned int checkupDuration[3];
		for (int i = 0; i < 3; i++)
		{
			file >> ntrucks[i];
		}
		for (int i = 0; i < 3; i++)
		{
			file >> speed[i];
		}
		for (int i = 0; i < 3; i++)
		{
			file >> capacity[i];
		}
		file >> nj;
		for (int i = 0; i < 3; i++)
		{
			file >> checkupDuration[i];
		}

		for (int typeInd = 0; typeInd < 3; typeInd++)
		{
			for (int i = 0; i < ntrucks[typeInd]; i++)
			{
				trucks* newtruck = new trucks(capacity[typeInd], speed[typeInd], nj, checkupDuration[typeInd]);
				newtruck->setTruckType(typeInd);
				truckTypes[typeInd]->enqueue(newtruck);
			}
		}
		return true;
	}
	return false;
}
bool Company::LoadEvents(QueueLinkedList<Events*>& events)
{
	int n;
	int extramoney;
	char evt, type;
	cargoType tp;
	file >> n;
	unsigned short loadTime;
	unsigned int deliveryDistance;
	unsigned int cost;
	int id;
	string time;
	while (n--)
	{
		file >> evt;
		if (evt == 'R')
		{
			file >> type;
			if (type == 'N')
				tp = NORMAL;
			else if (type == 'S')
				tp = SPECIAL;
			else
				tp = VIP;
			file >> time;
			file >> id;
			file >> deliveryDistance;
			file >> loadTime;
			file >> cost;
			PreparationEvent* ev = new PreparationEvent(tp, loadTime, deliveryDistance, cost, id);
			extractDateTime(time, ev);
			events.enqueue(ev);
		}
		else if (evt == 'X')
		{
			file >> time;
			file >> id;
			CancelEvent* ev = new CancelEvent(id);
			extractDateTime(time, ev);
			events.enqueue(ev);
		}
		else if (evt == 'P')
		{
			file >> time;
			file >> id;
			file >> extramoney;
			PrompteEvent* ev = new PrompteEvent(id, extramoney);
			string tmp;
			extractDateTime(time, ev);
			events.enqueue(ev);
		}
	}
	return true;
}
bool Company::LoadMaxw_Autop(int& MaxW, int& AutoP)
{
	if (file.is_open())
	{
		file >> AutoP;
		file >> MaxW;
		return true;
	}
	return false;
}
void Company::loadall(QueueLinkedList<trucks*>& normal, QueueLinkedList<trucks*>& special, QueueLinkedList<trucks*>& vip, QueueLinkedList<Events*>& events, int& MaxW, int& AutoP)
{
	LoadTrucks(normal, special, vip);
	LoadMaxw_Autop(MaxW, AutoP);
	LoadEvents(events);
}


//void Company::Update()
//{
//	cargo* tempCargo;
//	int i = 0;
//	while (!events.isEmpty() || !VIP_cargos.isEmpty() || !SPECIAL_cargos.isEmpty() || !NORMAL_cargos.isEmpty() || !VIP_cargos.isEmpty())
//	{
//		//system("cls");
//		i++;
//		executeEvent();
//		CargoToDelivered_ph1();
//		/*Interface.printAll(day, hour, NORMAL_cargos, SPECIAL_cargos, VIP_cargos, LOADINGNORMAL_trucks, LOADINGSPECIAL_trucks, LOADINGVIP_trucks, NORMAL_trucks, SPECIAL_trucks,
//			VIP_trucks, MOVINGNORMAL_trucks, MOVINGSPECIAL_trucks, MOVINGVIP_trucks, CHECKUPNORMAL_trucks, CHECKUPSPECIAL_trucks, CHECKUPVIP_trucks, DELIVEREDNORMAL_cargos
//			, DELIVEREDSPECIAL_cargos, DELIVEREDVIP_cargos);*/
//		augmentHour();
//		using namespace std::this_thread;
//		using namespace std::chrono;
//		sleep_until(system_clock::now() + milliseconds(1000));
//	}
//} 
void Company::assign()
{
	if (!workingHours())
		return;
	int vipCapacity = 0;
	int specialCapacity = 0;
	int normalCapacity = 0;
	if (!VIP_trucks.isEmpty())
		vipCapacity = VIP_trucks.peekFront()->getTc();
	if (!SPECIAL_trucks.isEmpty())
		specialCapacity = SPECIAL_trucks.peekFront()->getTc();
	if (!NORMAL_trucks.isEmpty())
		normalCapacity = NORMAL_trucks.peekFront()->getTc();
	cargo* tmpc;
	trucks* tmpt;
	int priority;
	int h = 0, d = 0;
	// Checking For AutoP
	if (!NORMAL_cargos.isEmpty())
		NORMAL_cargos.peekFront()->getWaitingTime(hour, day, h, d);
	while (d > AutoP)
	{

		cargo* promote = NORMAL_cargos.peekFront();
		NORMAL_cargos.dequeue();
		int pri = getVipPriority(promote);
		promote->setCargoType(VIP);
		promote->promote();
		VIP_cargos.enqueue(promote, pri);
		if (!NORMAL_cargos.isEmpty())
			NORMAL_cargos.peekFront()->getWaitingTime(hour, day, h, d);
		else
			break;
	}
	// Checking for MaxW in Normal and Special and VIP
	tmpt = nullptr;
	if (!NORMAL_cargos.isEmpty())
		NORMAL_cargos.peekFront()->getWaitingTime(hour, day, h, d);
	while (h + d * 24 >= MaxW)
	{
		tmpc = NORMAL_cargos.peekFront();
		if (tmpt && tmpt->getCarriedCargos().getCount() < tmpt->getTc())
		{
			NORMAL_cargos.dequeue();
			int p = tmpc->getDeliveryDistance();
			tmpt->addCargo(tmpc,p);
			tmpc->setCurrTruck(tmpt);
	    }
		else {
			if (!NORMAL_trucks.isEmpty())
			{
				tmpt = NORMAL_trucks.peekFront();
				NORMAL_trucks.dequeue();

				int p = tmpc->getDeliveryDistance();
				tmpt->addCargo(tmpc, -p);
				tmpc->setCurrTruck(tmpt);
				priority = getLoadingPriority(tmpt, hour + 24 * day);
				LOADINGNORMAL_trucks.enqueue(tmpt, priority);

				NORMAL_cargos.dequeue();
			}
			else if (!VIP_trucks.isEmpty())
			{

				tmpt = VIP_trucks.peekFront();
				VIP_trucks.dequeue();
				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
				priority = getLoadingPriority(tmpt, hour + 24 * day);
				LOADINGVIP_trucks.enqueue(tmpt, priority);

				NORMAL_cargos.dequeue();
			}
			else break;
		}
		h = 0;
		d = 0;
		if (!NORMAL_cargos.isEmpty())
			NORMAL_cargos.peekFront()->getWaitingTime(hour, day, h, d);
		
	}
	h = 0;
	d = 0;
	tmpt = nullptr;
	if (!SPECIAL_cargos.isEmpty())
		SPECIAL_cargos.peekFront()->getWaitingTime(hour, day, h, d);
	while (h + d * 24 >= MaxW)
	{
		tmpc = SPECIAL_cargos.peekFront();
		if (tmpt && tmpt->getCarriedCargos().getCount() < tmpt->getTc())
		{
			SPECIAL_cargos.dequeue();
			int p = tmpc->getDeliveryDistance();
			tmpt->addCargo(tmpc, p);
			tmpc->setCurrTruck(tmpt);
		}
		else {
			if (!SPECIAL_trucks.isEmpty())
			{
				tmpt = SPECIAL_trucks.peekFront();
				SPECIAL_trucks.dequeue();

				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
				priority = getLoadingPriority(tmpt, hour + 24 * day);
				LOADINGSPECIAL_trucks.enqueue(tmpt, priority);

				SPECIAL_cargos.dequeue();
			}
			else break;
		}
		h = 0;
		d = 0;
		if (!SPECIAL_cargos.isEmpty())
			SPECIAL_cargos.peekFront()->getWaitingTime(hour, day, h, d);
	}
	h = 0;
	d = 0;
	tmpt = nullptr;
	if (!VIP_cargos.isEmpty())
		VIP_cargos.peekFront(priority)->getWaitingTime(hour, day, h, d);
	while (h + d * 24 >= MaxW)
	{
		tmpc = VIP_cargos.peekFront(priority);
		if (tmpt && tmpt->getCarriedCargos().getCount() < tmpt->getTc())
		{
			VIP_cargos.dequeue();
			int p = tmpc->getDeliveryDistance();
			tmpt->addCargo(tmpc, p);
			tmpc->setCurrTruck(tmpt);
		}
		else {
			if (!VIP_trucks.isEmpty())
			{
				tmpt = VIP_trucks.peekFront();
				VIP_trucks.dequeue();

				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
				priority = getLoadingPriority(tmpt, hour + 24 * day);
				LOADINGVIP_trucks.enqueue(tmpt, priority);
				VIP_cargos.dequeue();
			}
			else if (!NORMAL_trucks.isEmpty())
			{
				tmpt = NORMAL_trucks.peekFront();
				NORMAL_trucks.dequeue();

				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
				priority = getLoadingPriority(tmpt, hour + 24 * day);
				LOADINGNORMAL_trucks.enqueue(tmpt, priority);

				VIP_cargos.dequeue();
			}
			else if (!SPECIAL_trucks.isEmpty())
			{
				tmpt = SPECIAL_trucks.peekFront();
				SPECIAL_trucks.dequeue();

				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
				priority = getLoadingPriority(tmpt, hour + 24 * day);
				LOADINGSPECIAL_trucks.enqueue(tmpt, priority);

				VIP_cargos.dequeue();
			}
			else break;
		}
		h = 0;
		d = 0;
		if (!VIP_cargos.isEmpty())
			VIP_cargos.peekFront(priority)->getWaitingTime(hour, day, h, d);
	}
	// Normal Assignment
	if (!VIP_trucks.isEmpty() && assignmentCounter < 3 && !assignedVip)
	{
		if (VIP_cargos.getCount() >= vipCapacity)
		{
			tmpt = VIP_trucks.peekFront();
			VIP_trucks.dequeue();
			for (int i = 0; i < vipCapacity; i++)
			{
				tmpc = VIP_cargos.peekFront(priority);
				VIP_cargos.dequeue();
				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
			}
			//ADDED 5/26 +24*day
			priority = getLoadingPriority(tmpt, hour + 24 * day);
			LOADINGVIP_trucks.enqueue(tmpt, priority);
			assignedVip = true;
			assignmentCounter++;
		}
	}
	else if (!NORMAL_trucks.isEmpty() && assignmentCounter < 3 && !assignedVip)
	{
		if (VIP_cargos.getCount() >= normalCapacity)
		{
			tmpt = NORMAL_trucks.peekFront();
			NORMAL_trucks.dequeue();
			for (int i = 0; i < normalCapacity; i++)
			{
				tmpc = VIP_cargos.peekFront(priority);
				VIP_cargos.dequeue();
				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
			}
			priority = getLoadingPriority(tmpt, hour + 24 * day);
			LOADINGNORMAL_trucks.enqueue(tmpt, priority);
			assignedVip = true;
			assignmentCounter++;
		}
	}
	else if (!SPECIAL_trucks.isEmpty() && assignmentCounter < 3 && !assignedVip)
	{
		if (VIP_cargos.getCount() >= specialCapacity)
		{
			tmpt = SPECIAL_trucks.peekFront();
			SPECIAL_trucks.dequeue();
			for (int i = 0; i < specialCapacity; i++)
			{
				tmpc = VIP_cargos.peekFront(priority);
				VIP_cargos.dequeue();
				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
			}
			priority = getLoadingPriority(tmpt, hour + 24 * day);
			LOADINGSPECIAL_trucks.enqueue(tmpt, priority);
			assignedVip = true;
			assignmentCounter++;
		}
	}
	if (!SPECIAL_trucks.isEmpty() && assignmentCounter < 3 && !assignedSpecial)
	{
		if (SPECIAL_cargos.getCount() >= specialCapacity)
		{
			tmpt = SPECIAL_trucks.peekFront();
			SPECIAL_trucks.dequeue();
			for (int i = 0; i < specialCapacity; i++)
			{
				tmpc = SPECIAL_cargos.peekFront();
				SPECIAL_cargos.dequeue();
				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
			}
			priority = getLoadingPriority(tmpt, hour + 24 * day);
			LOADINGSPECIAL_trucks.enqueue(tmpt, priority);
			assignedSpecial = true;
			assignmentCounter++;
		}
	}
	if (!NORMAL_trucks.isEmpty() && assignmentCounter < 3 && !assignedNormal)
	{
		if (NORMAL_cargos.getCount() >= normalCapacity)
		{
			tmpt = NORMAL_trucks.peekFront();
			NORMAL_trucks.dequeue();
			for (int i = 0; i < normalCapacity; i++)
			{
				tmpc = NORMAL_cargos.peekFront();
				NORMAL_cargos.dequeue();
				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
			}
			priority = getLoadingPriority(tmpt, hour + 24 * day);
			LOADINGNORMAL_trucks.enqueue(tmpt, priority);
			assignedNormal = true;
			assignmentCounter++;
		}
	}
	else if (!SPECIAL_trucks.isEmpty() && assignmentCounter < 3 && !assignedNormal)
	{
		if (NORMAL_cargos.getCount() >= specialCapacity)
		{
			tmpt = SPECIAL_trucks.peekFront();
			SPECIAL_trucks.dequeue();
			for (int i = 0; i < specialCapacity; i++)
			{
				tmpc = NORMAL_cargos.peekFront();
				NORMAL_cargos.dequeue();
				tmpt->addCargo(tmpc, -tmpc->getDeliveryDistance());
				tmpc->setCurrTruck(tmpt);
			}
			priority = getLoadingPriority(tmpt, hour + 24 * day);
			LOADINGSPECIAL_trucks.enqueue(tmpt, priority);
			assignedNormal = true;
			assignmentCounter++;
		}
	}






}
void Company::Moving() {
	//____________________________________MOVING____________________________________________
	int val;
	int prior;
	cargo* tmpc;
	trucks* tmpt;
	while (!LOADINGNORMAL_trucks.isEmpty())
	{

		tmpt = LOADINGNORMAL_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val) {
			if (tmpt->PeekCargo(prior)->getCargoType() == VIP)
			{
				assignedVip = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			else if (tmpt->PeekCargo(prior)->getCargoType() == SPECIAL)
			{
				assignedSpecial = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			else
			{
				assignedNormal = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			tmpt->Incrementjourneys();
			tmpt->incCheckj();
			LOADINGNORMAL_trucks.dequeue();
			int pri = getTruckMovingPriority(tmpt);
			MOVINGNORMAL_trucks.enqueue(tmpt, pri);
			PriorityQueue<cargo*> cpq = tmpt->getCarriedCargos();

			//ADDED
			int accumulateLoadTime = 0;
			while (!cpq.isEmpty())
			{
				tmpc = cpq.peekFront(pri);
				pri = getCargoMovingPriority(tmpt, tmpc, accumulateLoadTime);
				MOVINGNORMAL_cargos.enqueue(tmpc, pri);
				//ADDED
				accumulateLoadTime += tmpc->getLoadTime();
				cpq.dequeue();
			}
		}
		else break;
	}
	while (!LOADINGSPECIAL_trucks.isEmpty())
	{

		tmpt = LOADINGSPECIAL_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val) {
			if (tmpt->PeekCargo(prior)->getCargoType() == VIP)
			{
				assignedVip = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			else if (tmpt->PeekCargo(prior)->getCargoType() == SPECIAL)
			{
				assignedSpecial = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			else
			{
				assignedNormal = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			tmpt->Incrementjourneys();
			tmpt->incCheckj();
			LOADINGSPECIAL_trucks.dequeue();
			int pri = getTruckMovingPriority(tmpt);
			MOVINGSPECIAL_trucks.enqueue(tmpt, pri);
			PriorityQueue<cargo*> cpq = tmpt->getCarriedCargos();
			//ADDED
			int accumulateLoadTime = 0;
			while (!cpq.isEmpty())
			{
				tmpc = cpq.peekFront(pri);
				pri = getCargoMovingPriority(tmpt, tmpc, accumulateLoadTime);
				MOVINGSPECIAL_cargos.enqueue(tmpc, pri);
				//ADDED
				accumulateLoadTime += tmpc->getLoadTime();
				cpq.dequeue();
			}
		}
		else
			break;
	}
	while (!LOADINGVIP_trucks.isEmpty())
	{
		tmpt = LOADINGVIP_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val) {
			if (tmpt->PeekCargo(prior)->getCargoType() == VIP)
			{
				assignedVip = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			else if (tmpt->PeekCargo(prior)->getCargoType() == SPECIAL)
			{
				assignedSpecial = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			else
			{
				assignedNormal = false;
				assignmentCounter--;
				if (assignmentCounter < 0)
					assignmentCounter = 0;
			}
			tmpt->Incrementjourneys();
			tmpt->incCheckj();
			LOADINGVIP_trucks.dequeue();
			int pri = getTruckMovingPriority(tmpt);
			MOVINGVIP_trucks.enqueue(tmpt, pri);
			PriorityQueue<cargo*> cpq = tmpt->getCarriedCargos();
			//ADDED
			int accumulateLoadTime = 0;
			while (!cpq.isEmpty())
			{
				tmpc = cpq.peekFront(pri);
				pri = getCargoMovingPriority(tmpt, tmpc,accumulateLoadTime);
				MOVINGVIP_cargos.enqueue(tmpc, pri);
				//ADDED
				accumulateLoadTime += tmpc->getLoadTime();
				cpq.dequeue();
			}
		}
		else
			break;
	}
}
void Company::Deliver()
{
	cargo* tmpc;
	int val;
	trucks* tmpt;
	//_________________________DELIVERED TRUCKS__________________________
	while (!MOVINGVIP_cargos.isEmpty())
	{
		tmpc = MOVINGVIP_cargos.peekFront(val);
		tmpt = tmpc->getCurrTruck();
		val = -val;
		if (day * 24 + hour == val) {
			MOVINGVIP_cargos.dequeue();
			tmpc->setCurrTruck(NULL);
			DELIVERED_cargos.enqueue(tmpc);
			tmpt->removeLastCargo();
			//IF NoOfJourney == maxJourneys >> checkup; else  >> waitingtrucks
		}
		else break;
	}
	while (!MOVINGSPECIAL_cargos.isEmpty())
	{
		tmpc = MOVINGSPECIAL_cargos.peekFront(val);
		tmpt = tmpc->getCurrTruck();
		val = -val;
		if (day * 24 + hour == val) {
			MOVINGSPECIAL_cargos.dequeue();
			tmpc->setCurrTruck(NULL);
			DELIVERED_cargos.enqueue(tmpc);
			tmpt->removeLastCargo();
		}
		else break;

	}
	while (!MOVINGNORMAL_cargos.isEmpty())
	{
		tmpc = MOVINGNORMAL_cargos.peekFront(val);
		tmpt = tmpc->getCurrTruck();
		val = -val;
		if (day * 24 + hour == val) {
			MOVINGNORMAL_cargos.dequeue();
			tmpc->setCurrTruck(NULL);
			DELIVERED_cargos.enqueue(tmpc);
			tmpt->removeLastCargo();
		}
		else break;

	}
}
void Company::Returntrucks()
{
	trucks* tmpt;
	int val;
	int pri;
	//_________________________DELIVERED TRUCKS__________________________
	while (!MOVINGVIP_trucks.isEmpty())
	{
		tmpt = MOVINGVIP_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val) {
			MOVINGVIP_trucks.dequeue();
			if (tmpt->getcheckJ() == tmpt->getJ())
			{
				tmpt->resetcheckj();
				pri = getTruckCheckUpPriority(tmpt);
				CHECKUPVIP_trucks.enqueue(tmpt, pri);
			}
			else
				VIP_trucks.enqueue(tmpt);
		}
		else break;
	}
	while (!MOVINGSPECIAL_trucks.isEmpty())
	{
		tmpt = MOVINGSPECIAL_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val) {
			MOVINGSPECIAL_trucks.dequeue();
			if (tmpt->getcheckJ() == tmpt->getJ())
			{
				tmpt->resetcheckj();
				pri = getTruckCheckUpPriority(tmpt);
				CHECKUPSPECIAL_trucks.enqueue(tmpt, pri);
			}
			else
				SPECIAL_trucks.enqueue(tmpt);
		}
		else break;
	}
	while (!MOVINGNORMAL_trucks.isEmpty())
	{
		tmpt = MOVINGNORMAL_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val) {
			MOVINGNORMAL_trucks.dequeue();
			if (tmpt->getcheckJ() == tmpt->getJ())
			{
				tmpt->resetcheckj();
				pri = getTruckCheckUpPriority(tmpt);
				CHECKUPNORMAL_trucks.enqueue(tmpt, pri);
			}
			else
				NORMAL_trucks.enqueue(tmpt);
		}
		else break;
	}
}
void Company::backFromCheckup()
{
	int val;
	trucks* tmpt;
	while (!CHECKUPVIP_trucks.isEmpty())
	{
		tmpt = CHECKUPVIP_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val)
		{
			CHECKUPVIP_trucks.dequeue();
			VIP_trucks.enqueue(tmpt);
		}
		else
			break;
		//^^^ ADDED 5/25
	}
	while (!CHECKUPSPECIAL_trucks.isEmpty())
	{
		tmpt = CHECKUPSPECIAL_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val)
		{
			CHECKUPSPECIAL_trucks.dequeue();
			SPECIAL_trucks.enqueue(tmpt);
		}
		else
			break;
		//^^^ ADDED 5/25
	}
	while (!CHECKUPNORMAL_trucks.isEmpty())
	{
		tmpt = CHECKUPNORMAL_trucks.peekFront(val);
		val = -val;
		if (day * 24 + hour == val)
		{
			CHECKUPNORMAL_trucks.dequeue();
			NORMAL_trucks.enqueue(tmpt);
		}
		else
			break;
		//^^^ ADDED 5/25
	}
}
void Company::Update()
{
	int M = Interface.getMode();
	bool cond = !events.isEmpty() || !MOVINGVIP_trucks.isEmpty() || !MOVINGSPECIAL_trucks.isEmpty() || !MOVINGNORMAL_trucks.isEmpty() || !NORMAL_cargos.isEmpty() || !SPECIAL_cargos.isEmpty() || !VIP_cargos.isEmpty() || !LOADINGNORMAL_trucks.isEmpty() || !LOADINGSPECIAL_trucks.isEmpty() || !LOADINGVIP_trucks.isEmpty() || !CHECKUPNORMAL_trucks.isEmpty() || !CHECKUPSPECIAL_trucks.isEmpty() || !CHECKUPVIP_trucks.isEmpty();

	while (cond)
	{

		Deliver();
		Returntrucks();
		backFromCheckup();
		if (hour >= 5 && hour <= 23) {
			//PLACED EXECUTE IN + t<5(same)
			executeEvent();
			assign();
			Moving();
			if (M == 1)
			{
				Interface.printAll(day, hour, NORMAL_cargos, SPECIAL_cargos, VIP_cargos, LOADINGNORMAL_trucks, LOADINGSPECIAL_trucks, LOADINGVIP_trucks, NORMAL_trucks, SPECIAL_trucks,
					VIP_trucks, MOVINGNORMAL_trucks, MOVINGSPECIAL_trucks, MOVINGVIP_trucks, CHECKUPNORMAL_trucks, CHECKUPSPECIAL_trucks, CHECKUPVIP_trucks, DELIVERED_cargos);
				using namespace std::this_thread;
				using namespace std::chrono;
				sleep_until(system_clock::now() + milliseconds(10));
			}
			else if (M == 3)
			{
				Interface.printAll(day, hour, NORMAL_cargos, SPECIAL_cargos, VIP_cargos, LOADINGNORMAL_trucks, LOADINGSPECIAL_trucks, LOADINGVIP_trucks, NORMAL_trucks, SPECIAL_trucks,
					VIP_trucks, MOVINGNORMAL_trucks, MOVINGSPECIAL_trucks, MOVINGVIP_trucks, CHECKUPNORMAL_trucks, CHECKUPSPECIAL_trucks, CHECKUPVIP_trucks, DELIVERED_cargos);
				Interface.space();
			}

		}
		else if(M!=2)
		{
			Interface.Off();
			if (M == 3)
			{
				Interface.printAll(day, hour, NORMAL_cargos, SPECIAL_cargos, VIP_cargos, LOADINGNORMAL_trucks, LOADINGSPECIAL_trucks, LOADINGVIP_trucks, NORMAL_trucks, SPECIAL_trucks,
					VIP_trucks, MOVINGNORMAL_trucks, MOVINGSPECIAL_trucks, MOVINGVIP_trucks, CHECKUPNORMAL_trucks, CHECKUPSPECIAL_trucks, CHECKUPVIP_trucks, DELIVERED_cargos);
				Interface.space();
			}
			else
			{
				Interface.printAll(day, hour, NORMAL_cargos, SPECIAL_cargos, VIP_cargos, LOADINGNORMAL_trucks, LOADINGSPECIAL_trucks, LOADINGVIP_trucks, NORMAL_trucks, SPECIAL_trucks,
					VIP_trucks, MOVINGNORMAL_trucks, MOVINGSPECIAL_trucks, MOVINGVIP_trucks, CHECKUPNORMAL_trucks, CHECKUPSPECIAL_trucks, CHECKUPVIP_trucks, DELIVERED_cargos);
				using namespace std::this_thread;
				using namespace std::chrono;
				sleep_until(system_clock::now() + milliseconds(10));
			}
		}

		cond = !events.isEmpty() || !MOVINGVIP_trucks.isEmpty() || !MOVINGSPECIAL_trucks.isEmpty() || !MOVINGNORMAL_trucks.isEmpty() || !NORMAL_cargos.isEmpty() || !SPECIAL_cargos.isEmpty() || !VIP_cargos.isEmpty() || !LOADINGNORMAL_trucks.isEmpty() || !LOADINGSPECIAL_trucks.isEmpty() || !LOADINGVIP_trucks.isEmpty() || !CHECKUPNORMAL_trucks.isEmpty() || !CHECKUPSPECIAL_trucks.isEmpty() || !CHECKUPVIP_trucks.isEmpty();
		augmentHour();

	}

	Interface.output(NORMAL_cargos, SPECIAL_cargos, VIP_cargos, LOADINGNORMAL_trucks, LOADINGSPECIAL_trucks, LOADINGVIP_trucks, NORMAL_trucks, SPECIAL_trucks,
		VIP_trucks, MOVINGNORMAL_trucks, MOVINGSPECIAL_trucks, MOVINGVIP_trucks, CHECKUPNORMAL_trucks, CHECKUPSPECIAL_trucks, CHECKUPVIP_trucks, DELIVERED_cargos, day, hour);
}