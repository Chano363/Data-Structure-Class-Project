#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "parkingLotManagingSystem.h"

namespace py = pybind11;

PYBIND11_MODULE(parkingLotManagingSystem, m) {
    // 绑定ParkingInfo结构体
    py::class_<ParkingInfo>(m, "ParkingInfo")
        .def(py::init<>())
        .def(py::init<int, int>())
        .def_readwrite("carNumber", &ParkingInfo::carNumber)
        .def_readwrite("entryTime", &ParkingInfo::entryTime)
        .def_readwrite("exitTime", &ParkingInfo::exitTime)
        .def("__repr__", [](const ParkingInfo &p) {
            return "(" + std::to_string(p.carNumber) + ", " + std::to_string(p.entryTime) + ")";
        });
    
    m.attr("OK") = OK;
    m.attr("ERROR") = ERROR;
    
    // 绑定parkingLotManagingSystem类
    py::class_<parkingLotManagingSystem>(m, "parkingLotManagingSystem")
        .def(py::init<int, int>(), py::arg("capacity") = 2, py::arg("perHourCost") = 10)
        .def("setCost", &parkingLotManagingSystem::setCost)
        .def("setCapacity", &parkingLotManagingSystem::setCapacity)
        .def("arrive", &parkingLotManagingSystem::arrive)
        .def("depart", &parkingLotManagingSystem::depart)
        .def("test", &parkingLotManagingSystem::test)
        .def("getParkingCount", &parkingLotManagingSystem::getParkingCount)
        .def("getCapacity", &parkingLotManagingSystem::getCapacity)
        .def("getPerHourCost", &parkingLotManagingSystem::getPerHourCost)
        .def("getWaitingCount", &parkingLotManagingSystem::getWaitingCount)
        .def("isExist", &parkingLotManagingSystem::isExist)
        
        // 修改等待车辆获取方法
        .def("getWaitingCar", [](parkingLotManagingSystem& self) {
            auto cars = self.getWaitingCar();
            std::vector<ParkingInfo> result;
            result.reserve(cars.size());
            for (const auto& car : cars) {
                result.push_back(car);
            }
            return result;
        }, py::return_value_policy::move)
        
        // 修改停车车辆获取方法
        .def("getParkingCar", [](parkingLotManagingSystem& self) {
            auto cars = self.getParkingCar();
            std::vector<ParkingInfo> result;
            result.reserve(cars.size());
            for (const auto& car : cars) {
                result.push_back(car);
            }
            return result;
        }, py::return_value_policy::move);
}