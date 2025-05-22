import sys
import os

# 添加当前目录到模块搜索路径



sys.path.append(os.path.dirname(__file__))

os.add_dll_directory(r'D:\Code\MinGW\ucrt64\bin')

import parkingLotManagingSystem

plms = parkingLotManagingSystem.parkingLotManagingSystem(10,5)

plms.test()