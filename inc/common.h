#pragma once
#define OK 1
#define ERROR 0
const int maxSize = 100;
using Status = int;

struct ParkingInfo
{
    int carNumber; // 车辆编号
    int entryTime; // 进入停车场的时间
    int exitTime;  // 离开停车场的时间
};