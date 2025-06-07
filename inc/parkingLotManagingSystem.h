#pragma once
#include "common.h"
#include "queue.h"
#include "stack.h"
#include <vector>

class parkingLotManagingSystem
{
public:
    parkingLotManagingSystem(int capacity = 2, int perHourCost = 10);
    ~parkingLotManagingSystem();
    Status setCost(int cost);
    Status setCapacity(int capacity);
    Status arrive(int carNumber, int entryTime);
    int depart(int carNumber, int exitTime);
    Status test();
    Status display();
    bool isExist(int carNumber);
    int getCount();
    int getCapacity();
    int getPerHourCost();
    int getWaitingCount();
    std::vector<ParkingInfo> getWaitingCar();
    std::vector<ParkingInfo> getParkingCar();
private:
    int capacity;
    Queue<ParkingInfo> *waitingQueue;
    Stack<ParkingInfo> *parkingStack;
    std::vector<int> costs;
    int perHourCost;
};