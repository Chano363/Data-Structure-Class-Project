#pragma once
#define OK 1
#define ERROR 0
const int maxSize = 100;
using Status = int;

struct ParkingInfo
{
<<<<<<< HEAD
    int carNumber; // 车辆编号
    int entryTime; // 进入停车场的时间
    int exitTime;  // 离开停车场的时间
=======
    int carNumber;
    int entryTime;
    int exitTime;

    ParkingInfo() : carNumber(0), entryTime(0), exitTime(0) {}
    
    ParkingInfo(int num, int entry) : carNumber(num), entryTime(entry), exitTime(0) {}
    
    ParkingInfo(const ParkingInfo& other) {
        carNumber = other.carNumber;
        entryTime = other.entryTime;
        exitTime = other.exitTime;
    }
>>>>>>> origin/xjs-dev
};