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
    waitingQueue = new Queue<ParkingInfo>(capacity);
    parkingStack = new Stack<ParkingInfo>(capacity);
    exitStack = new Stack<int>(capacity);
}

parkingLotManagingSystem::~parkingLotManagingSystem()
// 释放内存
{
    delete waitingQueue;
    delete parkingStack;
    delete exitStack;
}

int parkingLotManagingSystem::getCount()
// 返回停车场中的车辆数量
{
    return parkingStack->getCount();
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

int parkingLotManagingSystem::getWaitingCount()
// 返回等待队列中的车辆数量
{
    return waitingQueue->getCount();
}

vector<ParkingInfo> parkingLotManagingSystem::getWaitingCar()
// 返回等待队列中的车辆信息
{
    vector<ParkingInfo> temp;
    while (!waitingQueue->isEmpty())
    {
        ParkingInfo car = waitingQueue->dequeue();
        temp.push_back(car);
    }
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        waitingQueue->enqueue(temp[i]); 
    }
    return temp;
}

vector<ParkingInfo> parkingLotManagingSystem::getParkingCar()
// 返回停车场中的车辆信息
{
    vector<ParkingInfo> temp;
    while (!parkingStack->isEmpty())
    {
        ParkingInfo car = parkingStack->pop();
        temp.push_back(car);
    }
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        parkingStack->push(temp[i]);
    }
    return temp;
}

bool parkingLotManagingSystem::isExist(int carNumber)
// carNumber: 车辆编号
// 判断车辆是否存在
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

Status parkingLotManagingSystem::depart(int carNumber, int exitTime)
// carNumber: 车辆编号
// exitTime: 车辆离开停车场的时间
// 车辆离开停车场, 计算停车费用, 并将车辆从停车场中移除
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
    return OK;
}

Status parkingLotManagingSystem::arrive(int carNumber, int entryTime)
// carNumber: 车辆编号
// entryTime: 车辆进入停车场的时间
// 车辆进入停车场, 如果停车场已满, 则将车辆加入等待队列
// 如果停车场未满, 则将车辆加入停车场
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

