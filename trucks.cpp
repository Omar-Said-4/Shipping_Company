
#include "trucks.h"

int trucks::getType() const {
	return Type;
}

int trucks::getCargoNumber() const
{
	return cargosNumbers;
}

unsigned int trucks::getTc() const {
	return TC;
}

unsigned int trucks::getMt() const {
	return MT;
}

unsigned int trucks::getSpeed() const {
	return Speed;
}

unsigned int trucks::getDi() const {
	return DI;
}
int trucks::getJourneyCount()
{
	return journeys_count;
}
unsigned int trucks::getJ() const {
	return J;
}
int trucks::getId()
{
	return myId;
}
void trucks::setId(int a)
{
	ID = a;
}
trucks::trucks() {
	TC = 1;
	MT = 1;
	resetcheckj();
	Speed = 20;
	DI = 1;
	J = 0;
	tDC = 0;
	ID++;
	cargosNumbers = 0;
	myId = ID;
	journeys_count = 0;
	activeTime = 0;
}
bool trucks::setTruckCapacity(int TruckCapacity) {
	if (TruckCapacity <= 0) {
		TC = 1;
		return false;
	}
	TC = TruckCapacity;
	return true;
}

int trucks::getcheckJ()
{
	return checkj;
}

bool trucks::setMaintainceTime(int maintainceTime) {
	if (maintainceTime <= 0) {
		MT = 1;
		return false;
	}
	MT = maintainceTime;
	return true;
}

bool trucks::setSpeed(int speed) {
	if (speed <= 10) {
		speed = 20;
		return false;
	}
	Speed = speed;
	return true;
}
PriorityQueue<cargo*> trucks::getCarriedCargos()
{
	return carriedCargos;
}
bool trucks::setTruckType(int type) {

	Type = truckType(type);
	return true;
}
trucks::trucks(int TruckCapacity, int speed, int noOfJournys, int maintainceTime)
{
	resetcheckj();
	TC = TruckCapacity;
	Speed = speed;
	J = noOfJournys;
	MT = maintainceTime;
	myId = ID;
	ID++;
	journeys_count = 0;
	activeTime = 0;
	cargosNumbers = 0;
}
void trucks::incCheckj()
{
	checkj++;
}
void trucks::resetcheckj()
{
	checkj = 0;
}
bool trucks::setDeliveryInterval(int DeliveryInterval) {
	if (DeliveryInterval <= 0) {
		DI = 1;
		return false;
	}
	DI = DeliveryInterval;
	return true;
}
void trucks::Incrementjourneys()
{
	journeys_count++;
}
void trucks::reset()
{
	journeys_count = 0;
}
bool trucks::setNoOFJournys(int Journys) {
	if (Journys < 0) {
		J = 0;
		return false;
	}
	J = Journys;
	return true;
}

bool trucks::noCargos()
{
	return carriedCargos.isEmpty();
}

void trucks::setId(unsigned int id) {
	ID = id;
}

unsigned int trucks::getTDC() const
{
	return tDC;
}

void trucks::incrementTDC(unsigned int x)
{
	tDC += x;
}

void trucks::setActiveTime(int AT)
{
	activeTime += AT;
}

int trucks::getActiveTime()
{
	return activeTime;
}




bool trucks::clearCargos() {
	if (carriedCargos.isEmpty())
		return false;
	carriedCargos.destroy();
	return true;
}

void trucks::addcargosNumber() {
	cargosNumbers++ ;
}


trucks::~trucks()
{
	ID--;
	carriedCargos.destroy();
}
int trucks::ID = 0;
unsigned int trucks::getActiveTime() const
{
	return AT;
}
void trucks::setActiveTime(unsigned int aT)
{
	AT = aT;
}
void  trucks::setLoadedtime(int val)
{
	loadedDay = val / 24;
	loadedHour = val - loadedDay * 24;
}

void  trucks::getLoadedTime(int& pDay, int& pHour)
{
	pDay = loadedDay;
	pHour = loadedHour;
	return;
}

void  trucks::setDeliveredTime(int val)
{
	deliveredTime = val;
}
int trucks::getDeliveredTime()
{
	return deliveredTime;
}

bool trucks::addCargo(cargo* C, int pri)
{
	carriedCargos.enqueue(C, pri);
	return true;
}

bool trucks::removeLastCargo() {

	carriedCargos.dequeue();
	return 1;
}

cargo* trucks::PeekCargo(int& val) {
	return carriedCargos.peekFront(val);
}
