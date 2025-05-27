#include "parkingLotManagingSystem.h"
#include <iostream>
using namespace std;

parkingLotManagingSystem::parkingLotManagingSystem(int capacity, int perHourCost)
{
    this->capacity = capacity;
    this->perHourCost = perHourCost;
    waitingQueue = new Queue<ParkingInfo>(capacity);
    parkingStack = new Stack<ParkingInfo>(capacity);
    exitStack = new Stack<int>(capacity);
}

parkingLotManagingSystem::~parkingLotManagingSystem()
{
    delete waitingQueue;
    delete parkingStack;
    delete exitStack;
}

Status parkingLotManagingSystem::setCost(int cost)
{
    if (cost < 0)
    {
        cout << "Cost cannot be negative." << endl;
        return ERROR;
    }
    perHourCost = cost;
    return OK;
}

Status parkingLotManagingSystem::setCapacity(int capacity)
{
    if (capacity < 0)
    {
        cout << "Capacity cannot be negative." << endl;
        return ERROR;
    }
    this->capacity = capacity;
    return OK; 
}

Status parkingLotManagingSystem::depart(int carNumber, int exitTime)
{
    if (parkingStack->isEmpty())
    {
        cout << "No cars in the parking lot." << endl;
        return ERROR;
    }

    ParkingInfo temp;
    Stack<ParkingInfo> tempStack(capacity);
    bool found = false;
    while (!parkingStack->isEmpty())
    {
        temp = parkingStack->pop();
        if (temp.carNumber == carNumber)
        {
            found = true;
        }
        else
        {
            tempStack.push(temp);
        }
    }

    while (!tempStack.isEmpty())
    {
        parkingStack->push(tempStack.pop());
    }

    if (!found)
    {
        cout << "Car not found in the parking lot." << endl;
        return ERROR;
    }

    temp.exitTime = exitTime;
    int cost = (temp.exitTime - temp.entryTime) * perHourCost;
    cout << "Car " << temp.carNumber << " stayed for " 
         << temp.exitTime - temp.entryTime << " hours, fee: " << cost << endl;

    while (parkingStack->getCount() < capacity && !waitingQueue->isEmpty())
    {
        parkingStack->push(waitingQueue->dequeue());
    }
    return OK;
}

Status parkingLotManagingSystem::arrive(int carNumber, int entryTime)
{
    ParkingInfo temp;
    temp.carNumber = carNumber;
    temp.entryTime = entryTime;
    if (parkingStack->getCount() < capacity)
    {
        parkingStack->push(temp);
        cout << "Car " << temp.carNumber << " parked at position " 
             << parkingStack->getCount() << endl;
    }
    else
    {
        waitingQueue->enqueue(temp);
        cout << "Car " << temp.carNumber << " waiting in queue at position " 
             << waitingQueue->getCount() << endl;
    }
    return OK;
}

Status parkingLotManagingSystem::test()
{
    cout << "The system is working normally." << endl;
    return OK;
}

Status parkingLotManagingSystem::display()
{
    cout << "Hourly parking fee: " << perHourCost << endl;
    cout << "Parking lot capacity: " << capacity << endl;
    cout << "Number of parked cars: " << parkingStack->getCount() << endl;
    cout << "Number of cars in waiting queue: " << waitingQueue->getCount() << endl;
    
    if(parkingStack->getCount() == 0){
        cout << "No cars in parking lot" << endl;
    }
    else {
        cout << "Parked cars:" << endl;
        for(int i = 0; i < parkingStack->getCount(); i++)
        {
            ParkingInfo temp = parkingStack->pop();
            cout << "Car " << temp.carNumber << " at position " << i << endl;
            parkingStack->push(temp);
        }
    }
    
    if(waitingQueue->getCount() == 0)
    {
        cout << "No cars in waiting queue" << endl;
    }
    else {
        cout << "Cars in waiting queue:" << endl;
        for(int i = 0; i < waitingQueue->getCount(); i++)
        {
            ParkingInfo temp = waitingQueue->dequeue();
            cout << "Car " << temp.carNumber << " at position " << i << endl;
            waitingQueue->enqueue(temp);
        } 
    }
    return OK;
}

int parkingLotManagingSystem::getCount()
{
    return parkingStack->getCount();
}

int parkingLotManagingSystem::getCapacity()
{
    return capacity;
}

int parkingLotManagingSystem::getPerHourCost()
{
    return perHourCost;
}

int parkingLotManagingSystem::getWaitingCount()
{
    return waitingQueue->getCount();
}