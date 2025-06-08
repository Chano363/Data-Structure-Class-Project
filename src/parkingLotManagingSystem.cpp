#include "parkingLotManagingSystem.h"
#include <iostream>
using namespace std;

parkingLotManagingSystem::parkingLotManagingSystem(int capacity, int perHourCost)
// capacity: 停车场的容量
// perHourCost: 每小时的停车费
// 初始化停车场
{
    this->capacity = capacity;
    this->perHourCost = perHourCost;
    waitingQueue = new Queue<ParkingInfo>(capacity*100);
    parkingStack = new Stack<ParkingInfo>(capacity);
}

parkingLotManagingSystem::~parkingLotManagingSystem()
// 释放内存
{
    delete waitingQueue;
    delete parkingStack;
}

int parkingLotManagingSystem::getParkingCount()
// 返回停车场中的车辆数量
{
    return parkingStack->getCount();
}

int parkingLotManagingSystem::getWaitingCount()
// 返回等待队列中的车辆数量
{
    return waitingQueue->getCount();
}

int parkingLotManagingSystem::getCapacity()
// 返回停车场的容量
{
    return capacity;
}

int parkingLotManagingSystem::getPerHourCost()
// 返回每小时的停车费
{
    return perHourCost;
}

vector<ParkingInfo> parkingLotManagingSystem::getWaitingCar()
// 返回等待队列中的车辆信息
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
// 返回停车场中的车辆信息
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
// carNumber: 车辆编号
// 判断车辆是否存在
{
    for(int i = 0; i < objectPool.size(); i++) {
        if(objectPool[i].carNumber == carNumber) {
            return true; 
        }
    }
    return false;
}

Status parkingLotManagingSystem::setCost(int cost)
// cost: 每小时的停车费
// 设置每小时的停车费
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
// capacity: 停车场的容量
// 设置停车场的容量
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
        ParkingInfo car = waitingQueue->dequeue();
        car.entryTime = exitTime; // 更新车辆的进入时间为当前时间
        parkingStack->push(car);
    }
    for(auto it = objectPool.begin(); it != objectPool.end(); it++){
        if(it->carNumber == carNumber){
            objectPool.erase(it);
            break;
        } 
    }
    return cost;
}

Status parkingLotManagingSystem::arrive(int carNumber, int entryTime)
// carNumber: 车辆编号
// entryTime: 车辆进入停车场的时间
// 车辆进入停车场, 如果停车场已满, 则将车辆加入等待队列
// 如果停车场未满, 则将车辆加入停车场
{
    if (isExist(carNumber))
    {
        cout << "Car " << carNumber << " already exists." << endl;
        return ERROR;
    }
    
    ParkingInfo temp;
    temp.carNumber = carNumber;
    temp.entryTime = entryTime;
    objectPool.push_back(temp);
    if (parkingStack->getCount() < capacity)
    {
        parkingStack->push(objectPool.back());
        cout << "Car " << temp.carNumber << " parked at position " 
             << parkingStack->getCount() << endl;
    }
    else
    {
        waitingQueue->enqueue(objectPool.back());
        cout << "Car " << temp.carNumber << " waiting in queue at position " 
             << waitingQueue->getCount() << endl;
    }
    return OK;
}

Status parkingLotManagingSystem::test()
// 测试系统是否正常(调试用)
{
    cout << "The system is working normally." << endl;
    return OK;
}

Status parkingLotManagingSystem::display()
// 显示停车场和等待队列中的车辆信息(调试用)
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

