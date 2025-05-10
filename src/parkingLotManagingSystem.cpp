#include "../inc/parkingLotManagingSystem.h"
#include<iostream>
using namespace std;

parkingLotManagingSystem::parkingLotManagingSystem(int capacity, int perHourCost) {
    this->capacity = capacity;
    this->perHourCost = perHourCost;
    waitingQueue = new Queue(capacity);
    parkingStack = new Stack(capacity);
    exitStack = new Stack(capacity);
}

parkingLotManagingSystem::~parkingLotManagingSystem() {
    delete waitingQueue;
    delete parkingStack;
    delete exitStack;  
}

Status parkingLotManagingSystem::setCost(int cost) {
    if (cost < 0) {
        cout << "Cost cannot be negative." << endl;
        return ERROR;
    }
    perHourCost = cost;
    return OK; 
}

Status parkingLotManagingSystem::arrive(int carNumber) {
    if (waitingQueue->isEmpty()) {
        cout << "No cars in the waiting queue." << endl;
        return ERROR;
    } 
}