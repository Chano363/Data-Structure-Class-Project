#include "parkingLotManagingSystem.h"
#include <iostream>
using namespace std;

parkingLotManagingSystem::parkingLotManagingSystem(int capacity, int perHourCost)
{
    this->capacity = capacity;
    this->perHourCost = perHourCost;
    waitingQueue = new Queue<ParkingInfo>(capacity);
    parkingStack = new Stack<ParkingInfo>(capacity);
}

parkingLotManagingSystem::~parkingLotManagingSystem()
{
    delete waitingQueue;
    delete parkingStack;
}

vector<ParkingInfo> parkingLotManagingSystem::getWaitingCar()
{
    vector<ParkingInfo> temp;
    Queue<ParkingInfo> tempQueue(capacity);  
    while (!waitingQueue->isEmpty()) {
        ParkingInfo car = waitingQueue->dequeue();
        temp.push_back(car);
        tempQueue.enqueue(car); 
    }
    while (!tempQueue.isEmpty()) {
        waitingQueue->enqueue(tempQueue.dequeue());
    }
    return temp;
}

vector<ParkingInfo> parkingLotManagingSystem::getParkingCar()
{
    vector<ParkingInfo> temp;
    Stack<ParkingInfo> tempStack(capacity);

    while (!parkingStack->isEmpty()) {
        tempStack.push(parkingStack->pop());
    }
    
    while (!tempStack.isEmpty()) {
        ParkingInfo car = tempStack.pop();
        temp.push_back(car); 
        cout << "CarNum:" << car.carNumber << " Entry:" << car.entryTime << endl;
        parkingStack->push(car);  
    }
    
    return temp;
}

bool parkingLotManagingSystem::isExist(int carNumber)
{
    Stack<ParkingInfo> tempStack(capacity);
    bool found = false;
    while (!parkingStack->isEmpty())
    {
        ParkingInfo temp = parkingStack->pop();
        if (temp.carNumber == carNumber)
        {
            found = true;
        }
        tempStack.push(temp);
    }
    while (!tempStack.isEmpty())
    {
        parkingStack->push(tempStack.pop());
    }
    Queue <ParkingInfo> tempQueue(capacity);
    while (!waitingQueue->isEmpty())
    {
        ParkingInfo temp = waitingQueue->dequeue();
        if (temp.carNumber == carNumber)
        {
            found = true;
        }
        tempQueue.enqueue(temp);
    }
    while (!tempQueue.isEmpty())
    {
        waitingQueue->enqueue(tempQueue.dequeue()); 
    }
    return found;
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

int parkingLotManagingSystem::depart(int carNumber, int exitTime)
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
            break;
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
    if (exitTime < temp.entryTime)
    {
        cout << "Exit time cannot be earlier than entry time." << endl;
        return ERROR;
    }
    int cost = (temp.exitTime - temp.entryTime) * perHourCost;
    cout << "Car " << temp.carNumber << " stayed for " 
         << temp.exitTime - temp.entryTime << " hours, fee: " << cost << endl;

    while (parkingStack->getCount() < capacity && !waitingQueue->isEmpty())
    {
        parkingStack->push(waitingQueue->dequeue());
    }
    return cost;
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
    vector<ParkingInfo> tempParking = getParkingCar();
    vector<ParkingInfo> tempWaiting = getWaitingCar();
    if(parkingStack->getCount() == 0){
        cout << "No cars in parking lot" << endl;
    }
    else {
        cout << "Parked cars:" << endl;
        for(int i = 0; i < tempParking.size(); i++){
            ParkingInfo car = tempParking[i];
            cout << "Car " << car.carNumber << " parked at position " << i << endl;
        }
    }
    if(waitingQueue->getCount() == 0)
    {
        cout << "No cars in waiting queue" << endl;
    }
    else {
        cout << "Cars in waiting queue:" << endl;
        for(auto car : tempWaiting){
            cout << "Car " << car.carNumber << " waiting in queue at position " << waitingQueue->getCount() << endl; 
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