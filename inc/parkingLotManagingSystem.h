#pragma once
#include "common.h"
#include "queue.h"
#include "stack.h"
#include <vector>

class parkingLotManagingSystem {
    struct ParkingInfo {
        int carNumber;
        int entryTime;
        int exitTime;
    };
int capacity;
Queue<ParkingInfo> *waitingQueue;
Stack<ParkingInfo> *parkingStack;
Stack<int> *exitStack;
std::vector<int> costs;
int perHourCost;
public:
    parkingLotManagingSystem(int capacity = 2, int perHourCost = 10);
    ~parkingLotManagingSystem();
    Status setCost(int cost);
    Status setCapacity(int capacity);
    Status arrive(int carNumber);
};