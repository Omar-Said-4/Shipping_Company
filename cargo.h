#ifndef PROJECT_CARGO_H
#define PROJECT_CARGO_H

class trucks;
enum cargoType {
    VIP=0,
    SPECIAL=1,
    NORMAL=2
};

class cargo {
     int days,hours;
    cargoType Type;
     int loadTime;
     int deliveryDistance;
     int cost;
    int id;
    int deliveryTime;
    int loadedDay;
    int loadedHour;
    int deliverededDay;
    int deliveredHour;
     int truckId;
    bool promoted;
    trucks *currTruck;
    int waitedTime;
public:
    cargo();

    cargo( int days,  int hours, cargoType type,  int loadTime,
           int deliveryDistance,  int cost, trucks *currTruck);
    cargo(int ID);
    bool setCargoType(int type);
    void getDeliverytime(int& pDay,int&pHour);
    void setDeliverytime(int val);
    cargoType getCargoType();
    void getWaitingTime(int ch, int cd, int& h, int& d);
    trucks *getCurrTruck() const;
    bool isPromoted()const;
    void promote();
    void setCurrTruck(trucks *currTruck);

    bool setTime(int Days, int Hours);
    void setloadedtime(int val);
    void setdeliveredTime(int a, int b);
    int getloadedDay();
    void setWaitedTime(int pWaitedTime);
    int getWaitedTime();
    int getloadedHour();
    bool setLoadTime(int LoadTime);
    int getTruckId()const;
    void setTruckId( int TID);
    bool setDeliveryDistance(int DeliveryDistance);

    bool setCost(int Cost);

    void getTime(int &Days, int &Hours) const;

     int getLoadTime() const;

     int getDeliveryDistance() const;

     int getCost() const;
    int getId();
    void setID(int a);
    ~cargo();
};


#endif //PROJECT_CARGO_H
