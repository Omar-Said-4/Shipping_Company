#include "UI.h"
#include<iomanip>

UI::UI()
{

}
void UI::printTime(int day, int hour)
{
	cout << "Current Time (Day:Hour):" << day << ':' << hour << endl;
}
void UI::printWaitingCargos(QueueLinkedList<cargo*>& normal, QueueLinkedList<cargo*>& special, PriorityQueue<cargo*>& vip)
{
	QueueLinkedList<cargo*>temp;
	cargo* tmp;
	bool flag = false;
	int totalCount = normal.getCount() + special.getCount() + vip.getCount();
	cout << totalCount << " Waiting Cargos: [";
	while (!normal.isEmpty())
	{
		tmp = normal.peekFront();
		normal.dequeue();
		temp.enqueue(tmp);
		cout << tmp->getId() << ',';
		flag = true;
	}
	if (flag)
	{
		flag = false;
		cout << "\b";
	}
	cout << ']' << " (";
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront();
		temp.dequeue();
		normal.enqueue(tmp);
	}
	while (!special.isEmpty())
	{
		flag = true;
		tmp = special.peekFront();
		special.dequeue();
		temp.enqueue(tmp);
		cout << tmp->getId() << ',';
	}
	if (flag)
	{
		flag = false;
		cout << "\b";
	}
	cout << ')' << " {";
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront();
		temp.dequeue();
		special.enqueue(tmp);
	}
	int pri;
	PriorityQueue<cargo*>tempo;
	while (!vip.isEmpty())
	{
		flag = true;
		tmp = vip.peekFront(pri);
		vip.dequeue();
		tempo.enqueue(tmp, pri);
		cout << tmp->getId() << ',';
	}
	if (flag)
	{
		flag = false;
		cout << "\b";
	}
	cout << '}' << endl;
	while (!tempo.isEmpty())
	{
		tmp = tempo.peekFront(pri);
		tempo.dequeue();
		vip.enqueue(tmp, pri);
	}
}
void UI::printLoadingTrucks(PriorityQueue<trucks*>& normal, PriorityQueue<trucks*>& special, PriorityQueue<trucks*>& vip)
{
	int totalCount = normal.getCount() + special.getCount() + vip.getCount();
	PriorityQueue<trucks*>temp1 = normal;
	PriorityQueue<trucks*>temp2 = special;
	PriorityQueue<trucks*>temp3 = vip;
	trucks* tmp;
	int pri;
	cout << totalCount << " Loading Trucks : ";
	PriorityQueue<cargo*>carriedCargos;
	while (!temp1.isEmpty() || !temp2.isEmpty() || !temp3.isEmpty())
	{
		if (!temp1.isEmpty()) {
			tmp = temp1.peekFront(pri);
			cout << tmp->getId() << "[";
			temp1.dequeue();
			carriedCargos = tmp->getCarriedCargos();
			while (!carriedCargos.isEmpty())
			{
				cout << carriedCargos.peekFront(pri)->getId() << ',';
				carriedCargos.dequeue();
			}
			cout << "\b]" << " ";
		}
		if (!temp2.isEmpty()) {
			tmp = temp2.peekFront(pri);
			cout << tmp->getId() << "(";
			temp2.dequeue();
			carriedCargos = tmp->getCarriedCargos();
			while (!carriedCargos.isEmpty())
			{
				cout << carriedCargos.peekFront(pri)->getId() << ',';
				carriedCargos.dequeue();
			}
			cout << "\b)" << " ";
		}
		if (!temp3.isEmpty()) {
			tmp = temp3.peekFront(pri);
			cout << tmp->getId() << "{";
			temp3.dequeue();
			carriedCargos = tmp->getCarriedCargos();
			while (!carriedCargos.isEmpty())
			{
				cout << carriedCargos.peekFront(pri)->getId() << ',';
				carriedCargos.dequeue();
			}
			cout << "\b}" << " ";
		}
	}

	cout << endl;
}
void UI::printEmptyTrucks(QueueLinkedList<trucks*>& normal, QueueLinkedList<trucks*>& special, QueueLinkedList<trucks*>& vip)
{
	trucks* tmp;
	QueueLinkedList<trucks*>temp;
	int totalCount = normal.getCount() + special.getCount() + vip.getCount();
	cout << totalCount << " Empty Trucks: [";
	while (!normal.isEmpty())
	{
		tmp = normal.peekFront();
		normal.dequeue();
		temp.enqueue(tmp);
		cout << tmp->getId();
		if (!normal.isEmpty())
			cout << ",";
	}
	cout << "]" << " (";
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront();
		temp.dequeue();
		normal.enqueue(tmp);
	}
	while (!special.isEmpty())
	{
		tmp = special.peekFront();
		special.dequeue();
		temp.enqueue(tmp);
		cout << tmp->getId();
		if (!special.isEmpty())
			cout << ",";

	}
	cout << ")" << " {";
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront();
		temp.dequeue();
		special.enqueue(tmp);
	}
	while (!vip.isEmpty())
	{
		tmp = vip.peekFront();
		vip.dequeue();
		temp.enqueue(tmp);
		cout << tmp->getId();
		if (!vip.isEmpty())
			cout << ",";

	}
	cout << "}" << endl;
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront();
		temp.dequeue();
		vip.enqueue(tmp);
	}
}
void UI::printMovingCargos(PriorityQueue<trucks*>& normal, PriorityQueue<trucks*>& special, PriorityQueue<trucks*>& vip)
{
	int totalCount = 0;
	int pri;

	PriorityQueue<trucks*>temp1;
	PriorityQueue<trucks*>temp2;
	PriorityQueue<trucks*>temp3;
	temp1 = normal;
	while (!temp1.isEmpty())
	{

		totalCount += temp1.peekFront(pri)->getCarriedCargos().getCount();
		temp1.dequeue();
	}
	temp1 = special;
	while (!temp1.isEmpty())
	{

		totalCount += temp1.peekFront(pri)->getCarriedCargos().getCount();
		temp1.dequeue();
	}
	temp1 = vip;
	while (!temp1.isEmpty())
	{

		totalCount += temp1.peekFront(pri)->getCarriedCargos().getCount();
		temp1.dequeue();
	}
	trucks* tmp;
	cout << totalCount << " Moving Cargos : ";
	PriorityQueue<cargo*>carriedCargos;
	while (!normal.isEmpty() || !special.isEmpty() || !vip.isEmpty())
	{
		if (!normal.isEmpty()) {
			tmp = normal.peekFront(pri);
			normal.dequeue();
			temp1.enqueue(tmp, pri);
			if (!tmp->noCargos()) {
				cout << tmp->getId() << "[";
				carriedCargos = tmp->getCarriedCargos();
				while (!carriedCargos.isEmpty())
				{
					cout << carriedCargos.peekFront(pri)->getId() << ',';
					carriedCargos.dequeue();
				}
				cout << "\b]" << " ";
			}
		}
		if (!special.isEmpty()) {
			tmp = special.peekFront(pri);
			special.dequeue();
			temp2.enqueue(tmp, pri);
			if (!tmp->noCargos()) {
				cout << tmp->getId() << "(";
				carriedCargos = tmp->getCarriedCargos();
				while (!carriedCargos.isEmpty())
				{
					cout << carriedCargos.peekFront(pri)->getId() << ',';
					carriedCargos.dequeue();
				}
				cout << "\b)" << " ";
			}
		}
		if (!vip.isEmpty()) {
			tmp = vip.peekFront(pri);
			vip.dequeue();
			temp3.enqueue(tmp, pri);
			if (!tmp->noCargos()) {
				cout << tmp->getId() << "{";
				carriedCargos = tmp->getCarriedCargos();
				while (!carriedCargos.isEmpty())
				{
					cout << carriedCargos.peekFront(pri)->getId() << ',';
					carriedCargos.dequeue();
				}
				cout << "\b}" << " ";
			}
		}
	}
	while (!temp1.isEmpty())
	{
		tmp = temp1.peekFront(pri);
		temp1.dequeue();
		normal.enqueue(tmp, pri);
	}
	while (!temp2.isEmpty())
	{
		tmp = temp2.peekFront(pri);
		temp2.dequeue();
		special.enqueue(tmp, pri);
	}
	while (!temp3.isEmpty())
	{
		tmp = temp3.peekFront(pri);
		temp3.dequeue();
		vip.enqueue(tmp, pri);
	}
	cout << endl;
}

void UI::printIncheckupTrucks(PriorityQueue<trucks*>& normal, PriorityQueue<trucks*>& special, PriorityQueue<trucks*>& vip)
{
	trucks* tmp;
	int pri;
	PriorityQueue<trucks*>temp;
	int totalCount = normal.getCount() + special.getCount() + vip.getCount();
	cout << totalCount << " In-Checkup Trucks: [";
	while (!normal.isEmpty())
	{
		tmp = normal.peekFront(pri);
		normal.dequeue();
		temp.enqueue(tmp, pri);
		cout << tmp->getId();
		//Added 5/26
		if (!normal.isEmpty())
			cout << ',';
	}
	cout << ']' << " (";
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront(pri);
		temp.dequeue();
		normal.enqueue(tmp, pri);
	}
	while (!special.isEmpty())
	{
		tmp = special.peekFront(pri);
		special.dequeue();
		temp.enqueue(tmp, pri);
		cout << tmp->getId();
		if (!special.isEmpty())
			cout << ',';
	}
	cout << ')' << " {";
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront(pri);
		temp.dequeue();
		special.enqueue(tmp, pri);
	}
	while (!vip.isEmpty())
	{
		tmp = vip.peekFront(pri);
		vip.dequeue();
		temp.enqueue(tmp, pri);
		cout << tmp->getId();
		if (!vip.isEmpty())
			cout << ',';
	}
	cout << '}' << endl;
	while (!temp.isEmpty())
	{
		tmp = temp.peekFront(pri);
		temp.dequeue();
		vip.enqueue(tmp, pri);
	}
}
void UI::printDeliveredCargos(QueueLinkedList<cargo*>& cargos)
{
	QueueLinkedList<cargo*>temp = cargos;
	cargo* tmp;
	bool flag = false;
	int totalCount = temp.getCount();
	cout << totalCount << " Delivered Cargos: ";
	while (!temp.isEmpty())
	{
		flag = true;
		tmp = temp.peekFront();
		temp.dequeue();
		if (tmp->getCargoType() == VIP)
		{
			cout << "{" << tmp->getId() << "} ";
		}
		else if (tmp->getCargoType() == SPECIAL)
		{
			cout << "(" << tmp->getId() << ") ";

		}
		else
		{
			cout << "[" << tmp->getId() << "] ";

		}
	}
}
void UI::printAll(int day, int hour,
	QueueLinkedList<cargo*>& wcnormal, QueueLinkedList<cargo*>& wcspecial, PriorityQueue<cargo*>& wcvip,
	PriorityQueue<trucks*>& ltnormal, PriorityQueue<trucks*>& ltspecial, PriorityQueue<trucks*>& ltvip,
	QueueLinkedList<trucks*>& etnormal, QueueLinkedList<trucks*>& etspecial, QueueLinkedList<trucks*>& etvip,
	PriorityQueue<trucks*>& mcnormal, PriorityQueue<trucks*>& mcspecial, PriorityQueue<trucks*>& mcvip,
	PriorityQueue<trucks*>& incnormal, PriorityQueue<trucks*>& incspecial, PriorityQueue<trucks*>& incvip,
	QueueLinkedList<cargo*>& dc
)
{
	printTime(day, hour);
	printWaitingCargos(wcnormal, wcspecial, wcvip);
	cout << "------------------------------------------------------------------------------------------------" << endl;
	printLoadingTrucks(ltnormal, ltspecial, ltvip);
	cout << "------------------------------------------------------------------------------------------------"  << endl;
	printEmptyTrucks(etnormal, etspecial, etvip);
	cout << "------------------------------------------------------------------------------------------------"  << endl;
	printMovingCargos(mcnormal, mcspecial, mcvip);
	cout << "------------------------------------------------------------------------------------------------"  << endl;
	printIncheckupTrucks(incnormal, incspecial, incvip);
	cout << "------------------------------------------------------------------------------------------------"  << endl;
	printDeliveredCargos(dc);
	cout << endl << "------------------------------------------------------------------------------------------------"  << endl;
}
void UI::output(QueueLinkedList<cargo*>& wcnormal, QueueLinkedList<cargo*>& wcspecial, PriorityQueue<cargo*>& wcvip,
	PriorityQueue<trucks*>& ltnormal, PriorityQueue<trucks*>& ltspecial, PriorityQueue<trucks*>& ltvip,
	QueueLinkedList<trucks*>& etnormal, QueueLinkedList<trucks*>& etspecial, QueueLinkedList<trucks*>& etvip,
	PriorityQueue<trucks*>& mcnormal, PriorityQueue<trucks*>& mcspecial, PriorityQueue<trucks*>& mcvip,
	PriorityQueue<trucks*>& incnormal, PriorityQueue<trucks*>& incspecial, PriorityQueue<trucks*>& incvip,
	QueueLinkedList<cargo*>& dc, unsigned int cDay, unsigned int cHour)
{
	ofstream out("out.txt");
	out << fixed << showpoint;
	out << setw(6) << "CDT" << setw(7) << "ID" << setw(7) << "PT" << setw(7) << "WT" << setw(7) << "TID" << endl;
	unsigned int normalCount = 0, vipCount = 0, specialCount = 0, normalT = 0, specialT = 0, vipT = 0;
	unsigned int  totalWaitingHours = 0, noOfPromotedCargos = 0, tst;
	double totalUtilization = 0, totalActiveTime = 0;
	int day, hour;
	int wDay, wHour;
	tst = cDay * 24 + cHour;
	while (!dc.isEmpty())
	{
		if (dc.peekFront()->getCargoType() == VIP)
		{
			vipCount++;
		}
		else if (dc.peekFront()->getCargoType() == SPECIAL)
		{
			specialCount++;
		}
		else normalCount++;
		dc.peekFront()->getTime(day, hour);
		if (dc.peekFront()->isPromoted())
			noOfPromotedCargos++;
		int cDdays, cDhours;
		dc.peekFront()->getDeliverytime(cDdays, cDhours);
		out << setw(5);
		if(cDhours>=0&&cDhours<=9)
			out << cDdays << ":0" << cDhours << setw(5);
		else
		out << cDdays << ':' << cDhours << setw(5);
		if(hour>=0&&hour<=9)
		out << dc.peekFront()->getId() << setw(5) << day << ":0" << hour;
		else
		out << dc.peekFront()->getId() << setw(5) << day << ':' << hour;
		int time;
		time = dc.peekFront()->getWaitedTime();
		wDay = time / 24;
		wHour = time % 24;
		totalWaitingHours += wHour + wDay * 24;
		out << setw(5);
		if(wHour>=0&&wHour<=9)
		out << wDay << ":0" << wHour;
		else
		out << wDay << ':' << wHour;
		out << setw(5);
		out << dc.peekFront()->getTruckId();
		out << endl;
		dc.dequeue();
	}
	cDay--;
	normalT = mcnormal.getCount() + incnormal.getCount() + ltnormal.getCount() + etnormal.getCount();
	specialT = mcspecial.getCount() + incspecial.getCount() + ltspecial.getCount() + etnormal.getCount();
	vipT = mcvip.getCount() + incvip.getCount() + ltvip.getCount() + etvip.getCount();
	unsigned int tc, n, tdc, tsim, tat;
	tsim = cDay * 24 + cHour;
	while (!etnormal.isEmpty())
	{
		tdc = etnormal.peekFront()->getCargoNumber();
		tc = etnormal.peekFront()->getTc();
		n = etnormal.peekFront()->getJourneyCount();
		tat = etnormal.peekFront()->getActiveTime();
		totalActiveTime += tat;
		if (n == 0)
		{
			etnormal.dequeue();
			continue;
		}
		totalUtilization += double(tdc) / (tc * n) * (double(tat) / tsim);
		etnormal.dequeue();
	}
	while (!etspecial.isEmpty())
	{
		tdc = etspecial.peekFront()->getCargoNumber();
		tc = etspecial.peekFront()->getTc();
		n = etspecial.peekFront()->getJourneyCount();
		tat = etspecial.peekFront()->getActiveTime();
		totalActiveTime += tat;
		if (n == 0)
		{
			etspecial.dequeue();
			continue;
		}
		totalUtilization += double(tdc) / (tc * n) * (double(tat) / tsim);
		etspecial.dequeue();
	}
	while (!etvip.isEmpty())
	{
		tdc = etvip.peekFront()->getCargoNumber();
		tc = etvip.peekFront()->getTc();
		n = etvip.peekFront()->getJourneyCount();
		tat = etvip.peekFront()->getActiveTime();
		totalActiveTime += tat;
		if (n == 0)
		{
			etvip.dequeue();
			continue;
		}
		totalUtilization += double(tdc) / (tc * n) * (double(tat) / tsim);
		etvip.dequeue();
	}
	/*PriorityQueue<trucks*>tempN;
	PriorityQueue<trucks*>tempS;
	PriorityQueue<trucks*>tempV;
	while (!mcnormal.isEmpty())
	{
		int pri;
		totalActiveTime += mcnormal.peekFront(pri)->getActiveTime();
		PriorityQueue<cargo*>tempC = mcnormal.peekFront(pri)->getCarriedCargos();
		while (!tempC.isEmpty())
		{
			if (tempC.peekFront(pri)->isPromoted())
				noOfPromotedCargos++;
			tempC.peekFront(pri)->getWaitingTime(cHour, cDay, wDay, wHour);
			totalWaitingHours += wHour + wDay * 24;
			if (tempC.peekFront(pri)->getCargoType() == VIP)
			{
				vipCount++;
			}
			else if (tempC.peekFront(pri)->getCargoType() == SPECIAL)
			{
				specialCount++;
			}
			else normalCount++;
		}
		unsigned int tc, n, tdc, tat;
		tc = mcnormal.peekFront(pri)->getTc();
		tdc = mcnormal.peekFront(pri)->getTDC();
		n = mcnormal.peekFront(pri)->getJourneyCount();
		if (tc * n == 0)
			continue;
		tat = mcnormal.peekFront(pri)->getActiveTime();
		totalUtilization += tdc / (tc * n) * (tat / tst);
		tempN.enqueue(mcnormal.peekFront(pri), pri);
		mcnormal.dequeue();
	}
	while (!mcspecial.isEmpty())
	{
		int pri;
		totalActiveTime += mcspecial.peekFront(pri)->getActiveTime();
		PriorityQueue<cargo*>tempC = mcspecial.peekFront(pri)->getCarriedCargos();
		while (!tempC.isEmpty())
		{
			if (tempC.peekFront(pri)->isPromoted())
				noOfPromotedCargos++;
			tempC.peekFront(pri)->getWaitingTime(cHour, cDay, wDay, wHour);
			totalWaitingHours += wHour + wDay * 24;
			if (tempC.peekFront(pri)->getCargoType() == VIP)
			{
				vipCount++;
			}
			else if (tempC.peekFront(pri)->getCargoType() == SPECIAL)
			{
				specialCount++;
			}
			else normalCount++;
		}
		unsigned int tc, n, tdc, tat;
		tc = mcspecial.peekFront(pri)->getTc();
		tdc = mcspecial.peekFront(pri)->getTDC();
		n = mcspecial.peekFront(pri)->getJourneyCount();
		if (tc * n == 0)
			continue;
		tat = mcspecial.peekFront(pri)->getActiveTime();
		totalUtilization += tdc / (tc * n) * (tat / tst);
		tempS.enqueue(mcspecial.peekFront(pri), pri);
		mcspecial.dequeue();
	}
	while (!mcvip.isEmpty())
	{
		int pri;
		totalActiveTime += mcvip.peekFront(pri)->getActiveTime();
		PriorityQueue<cargo*>tempC = mcvip.peekFront(pri)->getCarriedCargos();
		while (!tempC.isEmpty())
		{
			if (tempC.peekFront(pri)->isPromoted())
				noOfPromotedCargos++;
			tempC.peekFront(pri)->getWaitingTime(cHour, cDay, wDay, wHour);
			totalWaitingHours += wHour + wDay * 24;
			if (tempC.peekFront(pri)->getCargoType() == VIP)
			{
				vipCount++;
			}
			else if (tempC.peekFront(pri)->getCargoType() == SPECIAL)
			{
				specialCount++;
			}
			else normalCount++;
		}
		unsigned int tc, n, tdc, tat;
		tc = mcvip.peekFront(pri)->getTc();
		tdc = mcvip.peekFront(pri)->getTDC();
		n = mcvip.peekFront(pri)->getJourneyCount();
		if (tc * n == 0)
			continue;
		tat = mcvip.peekFront(pri)->getActiveTime();
		totalUtilization += tdc / (tc * n) * (tat / tst);
		tempV.enqueue(mcvip.peekFront(pri), pri);
		mcvip.dequeue();
	}*/
	unsigned long totalCargos = specialCount + normalCount + vipCount;
	unsigned long totalTrucks = normalT + specialT + vipT;
	totalActiveTime = totalActiveTime / (double(tsim)*totalTrucks);
	totalWaitingHours = totalWaitingHours / totalCargos;
	out << "Cargos: " << totalCargos << " [N: " << normalCount << ", S: " << specialCount << ", V: " << vipCount << ']' << endl;
	out << "Cargo Average Wait = " << totalWaitingHours / 24 << ':' << totalWaitingHours << endl;
	out << "Auto-Promoted Cargos: " << double(noOfPromotedCargos) / totalCargos * 100 << '%' << endl;
	out << "Trucks: " << totalTrucks << " [N: " << normalT << ", S: " << specialT << ", V: " << vipT << ']' << endl;
	out << "Average Active Time = " << totalActiveTime * 100 << '%' << endl;
	out << "Avergae Utilization = " << double(totalUtilization) / totalTrucks * 100 << '%' << endl;
}
int UI::getMode()
{
	int entry;
	cout << "Press 1 for Step-By-Step Mode" << endl;
	cout << "Press 2 for Silent Mode" << endl;
	cout << "Press 3 for Interactive Mode" << endl;
	cin >> entry;
	switch (entry)
	{
	case 1:
		cout << "Step-By-Step Mode" << endl;
		break;
	case 2:
		cout << "Silent Mode" << endl;
		break;
	default:
		cout << "Interactive Mode" << endl;
	}
	return entry;
}
void UI::Off()
{
	cout << "Company is Not Active" << endl;
}
void UI::space()
{
	system("pause");
}