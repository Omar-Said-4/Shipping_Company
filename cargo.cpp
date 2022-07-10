#include "cargo.h"
#include "trucks.h"

cargo::cargo() {
	days = 0;
	hours = 1;
	loadTime = 1;
	deliveryDistance = 1;
	cost = 1000;
	currTruck = nullptr;
	promoted = false;
}

bool cargo::setCargoType(int type) {
	switch (type) {
	case 0:
		Type = VIP;
		return true;
	case 1:
		Type = SPECIAL;
		return true;
	case 2:
	default:
		Type = NORMAL;
		return true;
	}
	return false;
}
void cargo::getDeliverytime(int& pDay, int& pHour)
{
	pDay = deliverededDay;
	pHour = deliveredHour;
}
void cargo::setDeliverytime(int val)
{
	deliverededDay = val / 24;
	deliveredHour = val - deliverededDay * 24;
}
cargo::cargo(int ID)
{
	id = ID;
}
cargoType cargo::getCargoType() {
	return Type;
}
int cargo::getId()
{
	return id;
}

void cargo::getWaitingTime(int ch, int cd, int& h, int& d)
{
	int val = cd * 24 + ch - days * 24 - hours;
	d = val / 24;
	h = val % 24;
}
void cargo::setID(int a) { id = a; }
bool cargo::setTime(int Days, int Hours) {
	if (Days < 0 || Hours < 0) {
		days = 0;
		Hours = 1;
		return false;
	}
	else if (Hours >= 24) {
		days = Hours / 24 + Days;
		hours = Hours % 24;
		return true;
	}
	else {
		days = Days;
		hours = Hours;
	}
}

void cargo::setloadedtime(int val)
{
	loadedDay = val / 24;
	loadedHour = val - loadedDay * 24;
}

void cargo::getTime(int& Days, int& Hours) const {
	Days = days;
	Hours = hours;
}

bool cargo::setLoadTime(int LoadTime) {
	if (LoadTime <= 0) {
		LoadTime = 1;
		return false;
	}
	else loadTime = LoadTime;
	return true;
}

int cargo::getTruckId() const
{
	return truckId;
}

void cargo::setTruckId( int TID)
{
	truckId = TID;
}

 int cargo::getLoadTime() const {
	return loadTime;
}

 int cargo::getCost() const {
	return cost;
}


int cargo::getloadedDay()
{
	return loadedDay;
}
void cargo::setWaitedTime(int pWaitedTime)
{
	waitedTime = pWaitedTime;
}
int cargo::getWaitedTime()
{
	return waitedTime;
}
int cargo::getloadedHour()
{
	return loadedHour;
}

 int cargo::getDeliveryDistance() const {
	return deliveryDistance;
}

bool cargo::setDeliveryDistance(int DeliveryDistance) {
	if (DeliveryDistance <= 0) {
		deliveryDistance = 1;
		return false;
	}
	deliveryDistance = DeliveryDistance;
	return true;
}

bool cargo::setCost(int Cost) {
	if (Cost <= 0) {
		cost = 1000;
		return false;
	}
	cost = Cost;
	return true;
}

cargo::cargo( int days,  int hours, cargoType type,  int loadTime,
	 int deliveryDistance,  int cost, trucks* currTruck) : days(days), hours(hours),
	Type(type), loadTime(loadTime),
	deliveryDistance(deliveryDistance),
	cost(cost), currTruck(currTruck) {}

trucks* cargo::getCurrTruck() const {
	return currTruck;
}

bool cargo::isPromoted() const
{
	return promoted;
}

void cargo::promote()
{
	promoted = true;
}

void cargo::setCurrTruck(trucks* currTruck) {
	cargo::currTruck = currTruck;
	if(currTruck)
	truckId = currTruck->getId();
}

cargo::~cargo() {
	currTruck = nullptr;
}
