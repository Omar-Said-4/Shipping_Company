#ifndef PROJECT_TRUCKS_H
#define PROJECT_TRUCKS_H

#include "cargo.h"
#include "LinkedList.h"
#include "PriorityQueue.h"

enum truckType {
    normal,
    special,
    vip
};

class trucks {


    truckType Type;
    unsigned int TC; //truck capacity
    unsigned int MT; //maintainance time
    unsigned int Speed;
    unsigned int DI;// delivery interval
    unsigned int J;//number of journeys
    unsigned int AT;
    unsigned int tDC;
    static int ID;
    int myId;
    PriorityQueue<cargo*> carriedCargos;
    int journeys_count;
    int loadedDay;
    int loadedHour;
	int deliveredTime;
    unsigned int cargosNumbers;
    int activeTime;
public:
    unsigned int getActiveTime()const;
    void setActiveTime(unsigned int aT);
    void setLoadedtime(int val);
    void setDeliveredTime(int val);
    int getDeliveredTime();
    int checkj;
    void setId(unsigned int id);
    unsigned int getTDC()const;
    void incrementTDC(unsigned int x);
    void setActiveTime(int AT);
    int getActiveTime();
    trucks();
    PriorityQueue<cargo*>getCarriedCargos();
    //trucks(int TruckCapacity, int speed, int DI, int noOfJournys, int maintainceTime);
    trucks(int TruckCapacity, int speed,int noOfJournys, int maintainceTime);
    void incCheckj();
    void resetcheckj();
    bool setTruckCapacity(int TruckCapacity);
    int getcheckJ();
    bool setMaintainceTime(int maintainceTime);

    bool setSpeed(int speed);

    bool setTruckType(int type);

    bool setDeliveryInterval(int DeliveryInterval);

    bool setNoOFJournys(int Journys);

    int getType() const;
    int getCargoNumber()const;
    unsigned int getTc() const;

    unsigned int getMt() const;

    unsigned int getSpeed() const;

    unsigned int getDi() const;

    unsigned int getJ() const;

    bool addCargo(cargo* C,int pri);

    bool removeLastCargo();
    cargo* PeekCargo(int& pri);

    bool clearCargos();
    int getId();
    void setId(int a);
    void addcargosNumber();
    void Incrementjourneys();
    void reset();
    bool noCargos();
    int getJourneyCount();
    
    void getLoadedTime(int& pDay,int& pHour);
    void getDeliveredTime(int& pDay,int& pHour);

    ~trucks();
};

#endif