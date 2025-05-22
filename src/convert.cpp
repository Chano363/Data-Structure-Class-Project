#include <pybind11/pybind11.h>
#include "../inc/parkingLotManagingSystem.h"

namespace py = pybind11;

PYBIND11_MODULE(parkingLotManagingSystem, m) {
    // 绑定ParkingInfo结构体
    py::class_<ParkingInfo>(m, "ParkingInfo")
        .def_readwrite("carNumber", &ParkingInfo::carNumber)
        .def_readwrite("entryTime", &ParkingInfo::entryTime)
        .def_readwrite("exitTime", &ParkingInfo::exitTime);

    // 绑定parkingLotManagingSystem类
    py::class_<parkingLotManagingSystem>(m, "parkingLotManagingSystem")
        .def(py::init<int, int>(), py::arg("capacity") = 2, py::arg("perHourCost") = 10)
        .def("setCost", &parkingLotManagingSystem::setCost)
        .def("setCapacity", &parkingLotManagingSystem::setCapacity)
        .def("arrive", &parkingLotManagingSystem::arrive)
        .def("depart", &parkingLotManagingSystem::depart)
        .def("test", &parkingLotManagingSystem::test);
}