cmake_minimum_required(VERSION 3.14)
project(ParkingLotManagingSystem)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_STRIP "")

# 添加配置选项
option(USE_CONFIG_FILE "使用配置文件" ON)
if(USE_CONFIG_FILE)
    # 查找配置文件
    find_file(CONFIG_FILE config.cmake PATHS ${CMAKE_SOURCE_DIR})
    if(CONFIG_FILE)
        include(${CONFIG_FILE})
    else()
        message(STATUS "未找到配置文件，使用默认设置")
    endif()
endif()

# 修改MinGW路径查找方式
if(DEFINED MINGW_PATH)
    set(MINGW_MAKE_PROGRAM "${MINGW_PATH}/mingw32-make.exe")
else()
    find_program(MINGW_MAKE_PROGRAM mingw32-make.exe)
endif()

if (NOT MINGW_MAKE_PROGRAM)
    message(FATAL_ERROR "未找到 mingw32-make.exe，请确保 MinGW 已正确安装并添加到 PATH 环境变量中。")
endif()

# 设置 CMake 生成器和编译器路径
set(CMAKE_GENERATOR "MinGW Makefiles" CACHE STRING "" FORCE)
set(CMAKE_C_COMPILER "gcc.exe" CACHE STRING "" FORCE)
set(CMAKE_CXX_COMPILER "g++.exe" CACHE STRING "" FORCE)
set(CMAKE_MAKE_PROGRAM "${MINGW_MAKE_PROGRAM}" CACHE STRING "" FORCE)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 查找Python解释器和开发包
find_package(Python 3.12 EXACT REQUIRED COMPONENTS Interpreter Development)

# 修改pybind11路径配置
execute_process(
    COMMAND python -c "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# 设置pybind11路径
set(pybind11_DIR "${pybind11_DIR}")
message(STATUS "pybind11_DIR: ${pybind11_DIR}")

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

# 添加链接库
target_link_libraries(parkingLotManagingSystem PRIVATE
    -static-libgcc
    -static-libstdc++
)

# 创建静态库
add_library(parkingLotManagingSystem_static STATIC
    src/queue.cpp
    src/stack.cpp
    src/parkingLotManagingSystem.cpp
)

# 添加独立可执行文件
add_executable(test_exe src/test.cpp)
target_link_libraries(test_exe PRIVATE parkingLotManagingSystem_static)

# 设置输出文件后缀为.pyd
set_target_properties(parkingLotManagingSystem PROPERTIES
    SUFFIX ".pyd"
)

# 设置输出目录
find_program(PYINSTALLER pyinstaller)
if(PYINSTALLER)    
    add_custom_target(package_python
        COMMAND ${PYINSTALLER} 
                --onefile 
                --windowed
                --name=ParkingLotSystem
                --add-data="${CMAKE_BINARY_DIR}/bin/parkingLotManagingSystem.pyd;."
                --paths="${CMAKE_SOURCE_DIR}"
                --distpath=${CMAKE_SOURCE_DIR}/output
                ${CMAKE_SOURCE_DIR}/main.py
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "打包Python程序为exe"
        DEPENDS parkingLotManagingSystem
    )
else()
    message(WARNING "未找到pyinstaller，无法创建打包任务")
endif()

# 设置目标包含目录
target_include_directories(parkingLotManagingSystem PUBLIC ${CMAKE_SOURCE_DIR}/inc)


# 设置编译选项
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -O2)
endif()