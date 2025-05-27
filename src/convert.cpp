#include <pybind11/pybind11.h>
#include <pybind11/stl_bind.h>
#include "parkingLotManagingSystem.h"

namespace py = pybind11;

PYBIND11_MODULE(parkingLotManagingSystem, m) {
    // 绑定ParkingInfo结构体
    py::class_<ParkingInfo>(m, "ParkingInfo")
        .def_readwrite("carNumber", &ParkingInfo::carNumber)
        .def_readwrite("entryTime", &ParkingInfo::entryTime)
        .def_readwrite("exitTime", &ParkingInfo::exitTime);
    m.attr("OK") = OK;
    m.attr("ERROR") = ERROR;
    py::bind_vector<std::vector<ParkingInfo> >(m, "Vector");
    // 绑定parkingLotManagingSystem类
    py::class_<parkingLotManagingSystem>(m, "parkingLotManagingSystem")
        .def(py::init<int, int>(), py::arg("capacity") = 2, py::arg("perHourCost") = 10)
        .def("setCost", &parkingLotManagingSystem::setCost)
        .def("setCapacity", &parkingLotManagingSystem::setCapacity)
        .def("arrive", &parkingLotManagingSystem::arrive)
        .def("depart", &parkingLotManagingSystem::depart)
        .def("test", &parkingLotManagingSystem::test)
        .def("getCount", &parkingLotManagingSystem::getCount)
        .def("getCapacity", &parkingLotManagingSystem::getCapacity)
        .def("getPerHourCost", &parkingLotManagingSystem::getPerHourCost)
        .def("getWaitingCount", &parkingLotManagingSystem::getWaitingCount)
        .def("isExist", &parkingLotManagingSystem::isExist)
        .def("getWaitingCar", &parkingLotManagingSystem::getWaitingCar)
        .def("getParkingCar", &parkingLotManagingSystem::getParkingCar);
}