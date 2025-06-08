#pragma once
#define OK 1
#define ERROR 0
#include <iostream>
const int maxSize = 100;
using Status = int;



struct ParkingInfo
{
    int carNumber;
    int entryTime;
    int exitTime;

    ParkingInfo() = default;   

    ParkingInfo(int num, int entry) : carNumber(num), entryTime(entry), exitTime(0) {}
    
    ParkingInfo(const ParkingInfo& other) {
        carNumber = other.carNumber;
        entryTime = other.entryTime;
        exitTime = other.exitTime;
        std::cout << "深拷贝车辆: " << carNumber << " 时间: " << entryTime << std::endl;
    }

    ParkingInfo& operator=(const ParkingInfo& other) {
        if (this != &other) {
            carNumber = other.carNumber;
            entryTime = other.entryTime;
            exitTime = other.exitTime;
            // std::cout << "深拷贝赋值: " << carNumber << " 时间: " << entryTime << std::endl;
        }
        return *this;
    }
};