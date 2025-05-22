#include "../inc/parkingLotManagingSystem.h"
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
    // 车辆离开
    // 如果停车场中没有车辆，返回错误
    if (parkingStack->isEmpty())
    {
        cout << "No cars in the parking lot." << endl;
        return ERROR;
    }
    // 如果停车场中有车辆，找到车辆，将其他车辆放入临时栈中，将车辆从停车场中移除，将临时栈中的车辆放入停车场中
    // 将车辆的离开时间记录到车辆的结构体中并计算费用
    // 将临时栈中的车辆放入停车场中
    ParkingInfo temp;
    Stack<ParkingInfo> tempStack(capacity);
    bool found = false;
    while (!parkingStack->isEmpty())
    {
        temp = parkingStack->pop();
        if (temp.carNumber == carNumber)
        {
            exitStack->push(temp.carNumber);
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

    // 如果没有找到车辆，返回错误
    if (!found)
    {
        cout << "Car not found in the parking lot." << endl;
        return ERROR;
    }

    temp.exitTime = exitTime;
    int cost = (temp.exitTime - temp.entryTime) * perHourCost;
    cout << "车辆" << temp.carNumber << "停留时间" << temp.exitTime - temp.entryTime << "小时，费用" << cost << endl;
    // 如果停车场中还有空位，将等待队列中的车辆放入停车场中
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
        cout << "车辆" << temp.carNumber << "停在停车场 " << parkingStack->getCount() << " 号位" << endl;
    }
    else
    {
        waitingQueue->enqueue(temp);
        cout << "车辆" << temp.carNumber << "停在等待队列 " << waitingQueue->getCount() << " 号位" << endl;
    }
    return OK;
}

Status parkingLotManagingSystem::test()
{
    cout << 500 / 100 << endl;
    return OK;
}