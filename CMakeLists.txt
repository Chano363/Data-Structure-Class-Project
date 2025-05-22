cmake_minimum_required(VERSION 3.14)
project(ParkingLotManagingSystem)

# 设置生成器为MinGW Makefiles
set(CMAKE_GENERATOR "MinGW Makefiles" CACHE INTERNAL "")

set(CMAKE_CXX_COMPILER "D:/Code/MinGW/ucrt64/bin/g++.exe")


# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_PREFIX_PATH "D:/python3.12.4/Lib/site-packages/pybind11/share/cmake/pybind11")

# 查找Python解释器和开发包
find_package(Python REQUIRED COMPONENTS Interpreter Development)

# 查找系统安装的pybind11
find_package(pybind11 REQUIRED)

# 包含目录
include_directories(inc)

# 创建Python模块
pybind11_add_module(parkingLotManagingSystem
    src/queue.cpp
    src/stack.cpp
    src/parkingLotManagingSystem.cpp
    src/convert.cpp
)

# 设置源文件编码
set_source_files_properties(
    src/parkingLotManagingSystem.cpp
    PROPERTIES
    ENCODING "UTF-8"
)