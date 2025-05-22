cmake_minimum_required(VERSION 3.14)
project(ParkingLotManagingSystem)

set(CMAKE_STRIP "")
set(CMAKE_GENERATOR "MinGW Makefiles" CACHE STRING "" FORCE)
set(CMAKE_C_COMPILER "D:/Code/MinGW/ucrt64/bin/gcc.exe" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "D:/Code/MinGW/ucrt64/bin/g++.exe" CACHE STRING "" FORCE)
set(CMAKE_MAKE_PROGRAM "D:/Code/MinGW/ucrt64/bin/mingw32-make.exe" CACHE STRING "" FORCE)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加pybind11路径
list(APPEND CMAKE_PREFIX_PATH "D:/python3.12.4/Lib/site-packages/pybind11/share/cmake/pybind11")

# 查找Python解释器和开发包
find_package(Python 3.12 EXACT REQUIRED COMPONENTS Interpreter Development)

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

# 设置目标包含目录
target_include_directories(parkingLotManagingSystem PUBLIC ${CMAKE_SOURCE_DIR}/inc)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 设置编译选项
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -O2)
endif()