import sys
import os
import time
import configparser
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel, QLineEdit, QMessageBox, QHBoxLayout, QTextEdit, QDialog

config = configparser.ConfigParser()
config.read('config.ini')

# 设置模块搜索路径
build_path = config.get('Paths', 'build_path', fallback='build')
sys.path.append(os.path.abspath(build_path))

# 设置DLL搜索路径
mingw_bin = config.get('Paths', 'mingw_bin', fallback=r'D:\MinGW\mingw64\bin')
if os.path.isdir(mingw_bin):
    os.add_dll_directory(mingw_bin)

import parkingLotManagingSystem

class ParkingLotApp(QWidget):
    def __init__(self):
        super().__init__()
        self.plms = None  # 停车场管理系统实例
        self.last_time = 0  # 记录上一次输入的时间
        self.initUI()

    def initUI(self):
        # 设置窗口标题和大小
        self.setWindowTitle('停车场管理系统')
        self.setGeometry(100, 100, 400, 400)

        # 创建主布局
        layout = QVBoxLayout()

        # 添加状态显示区域
        self.status_display = QTextEdit(self)
        self.status_display.setReadOnly(True)
        self.status_display.setPlaceholderText('停车场状态')
        layout.addWidget(self.status_display)

        # 添加初始化部分
        init_layout = QHBoxLayout()
        self.capacity_input = QLineEdit(self)
        self.capacity_input.setPlaceholderText('停车场容量')
        init_layout.addWidget(self.capacity_input)

        self.per_hour_cost_input = QLineEdit(self)
        self.per_hour_cost_input.setPlaceholderText('每小时费用')
        init_layout.addWidget(self.per_hour_cost_input)

        self.init_button = QPushButton('初始化停车场', self)
        self.init_button.clicked.connect(self.init_parking_lot)
        init_layout.addWidget(self.init_button)

        layout.addLayout(init_layout)

        # 添加车辆到达部分
        arrive_layout = QHBoxLayout()
        self.car_number_input = QLineEdit(self)
        self.car_number_input.setPlaceholderText('车牌号')
        arrive_layout.addWidget(self.car_number_input)

        self.entry_time_input = QLineEdit(self)
        self.entry_time_input.setPlaceholderText('进入时间')
        arrive_layout.addWidget(self.entry_time_input)

        self.arrive_button = QPushButton('车辆到达', self)
        self.arrive_button.clicked.connect(self.arrive_car)
        arrive_layout.addWidget(self.arrive_button)

        layout.addLayout(arrive_layout)

        # 添加车辆离开部分
        depart_layout = QHBoxLayout()
        self.depart_car_number_input = QLineEdit(self)
        self.depart_car_number_input.setPlaceholderText('车牌号')
        depart_layout.addWidget(self.depart_car_number_input)

        self.exit_time_input = QLineEdit(self)
        self.exit_time_input.setPlaceholderText('离开时间')
        depart_layout.addWidget(self.exit_time_input)

        self.depart_button = QPushButton('车辆离开', self)
        self.depart_button.clicked.connect(self.depart_car)
        depart_layout.addWidget(self.depart_button)

        layout.addLayout(depart_layout)

        # 添加控制台输入部分
        self.console_input = QLineEdit(self)
        self.console_input.setPlaceholderText('输入格式：(A/D/E, 车牌号, 时间)')
        layout.addWidget(self.console_input)

        self.process_button = QPushButton('处理输入', self)
        self.process_button.clicked.connect(self.process_console_input)
        layout.addWidget(self.process_button)

        # 添加显示说明
        self.instructions_btn = QPushButton('输入说明',self)
        self.instructions_btn.setStyleSheet("color: blue;")
        self.instructions_btn.clicked.connect(self.show_instructions)
        layout.addWidget(self.instructions_btn)
        # 设置布局
        self.setLayout(layout)
    def show_instructions(self):
        dialog = QDialog(self)
        dialog.setWindowTitle("输入说明")
        dialog.resize(600, 400)

        text_edit = QTextEdit(dialog)
        text_edit.setReadOnly(True)

        try:
            # 处理打包后的资源路径
            if getattr(sys, 'frozen', False):
                # 打包后运行时
                base_path = sys._MEIPASS
                file_path = os.path.join(base_path, "instructions.txt")
            else:
                # 开发时运行时
                base_path = os.path.dirname(os.path.abspath(__file__))
                file_path = os.path.join(base_path, "docs", "instructions.txt")

            with open(file_path, "r", encoding="utf-8") as file:
                text = file.read()
                text_edit.setPlainText(text)
        except FileNotFoundError:
            text_edit.setPlainText(f"未找到说明文件: {file_path}")
        except Exception as e:
            text_edit.setPlainText(f"读取说明文件出错: {str(e)}")

        layout = QVBoxLayout()
        layout.addWidget(text_edit)
        dialog.setLayout(layout)
        dialog.exec_()
    def update_status(self):
        """更新停车场状态显示"""
        try:
            print(f"\n{'='*20} 开始更新状态 {'='*20}")
            print(f"更新时间: {time.strftime('%H:%M:%S')}")

            if not self.plms:
                display_text = '停车场未初始化'
                self.status_display.setPlainText(display_text)
                print("更新状态: 停车场未初始化")
                return

            # 获取基本状态信息
            capacity = self.plms.getCapacity()
            parked_count = self.plms.getParkingCount()
            waiting_count = self.plms.getWaitingCount()

            # 获取车辆列表
            parked_cars = self.plms.getParkingCar()
            waiting_cars = self.plms.getWaitingCar()

            # 调试输出
            print(f"PLMS对象地址: {hex(id(self.plms))}")
            print(f"停车场容量: {capacity}")
            print(f"已停车辆数: {parked_count}")
            print(f"等待车辆数: {waiting_count}")
            print(f"获取停车车辆类型: {type(parked_cars)}")
            print(f"获取停车车辆数量: {len(parked_cars)}")

            # 构建状态文本
            status_text = f"停车场容量: {capacity}\n"
            status_text += f"已停车辆数: {parked_count}\n"
            status_text += f"等待车辆数: {waiting_count}\n\n"

            # 添加停车场车辆信息
            status_text += "=== 停车场中的车辆 ===\n"
            if parked_count > 0:
                for i, car in enumerate(parked_cars):
                    status_text += f"{i+1}. 车牌号: {car.carNumber}, 进入时间: {car.entryTime}\n"
                    print(f"车辆{i+1}: 车牌={car.carNumber}, 进入时间={car.entryTime}, 对象ID={id(car)}")
            else:
                status_text += "停车场为空\n"

            # 添加等待队列车辆信息
            status_text += "\n=== 等待队列中的车辆 ===\n"
            if waiting_count > 0:
                for i, car in enumerate(waiting_cars):
                    status_text += f"{i+1}. 车牌号: {car.carNumber}, 进入时间: {car.entryTime}\n"
            else:
                status_text += "等待队列为空\n"

            # 更新显示
            self.status_display.setPlainText(status_text)
            print("状态文本已更新")

            self.status_display.update()
            self.status_display.repaint()
            QApplication.processEvents()

        except Exception as e:
            error_msg = f'更新状态时出错: {str(e)}'
            print(error_msg)
            import traceback
            traceback.print_exc()
            QMessageBox.warning(self, '错误', error_msg)
        finally:
            print(f"{'='*20} 结束更新状态 {'='*20}\n")
    def init_parking_lot(self):
        # 获取输入值
        capacity = self.capacity_input.text()
        per_hour_cost = self.per_hour_cost_input.text()
        self.last_time = 0
        # 验证输入
        if not capacity or not per_hour_cost:
            QMessageBox.warning(self, '错误', '请输入有效的容量和每小时费用！')
            return

        try:
            capacity = int(capacity)
            per_hour_cost = int(per_hour_cost)
            if(capacity <= 0 or per_hour_cost <= 0):
                QMessageBox.warning(self, '错误', '请输入有效的容量和每小时费用！')
                return
        except ValueError:
            QMessageBox.warning(self, '错误', '请输入有效的数字！')
            return

        # 初始化停车场管理系统
        self.plms = parkingLotManagingSystem.parkingLotManagingSystem(capacity, per_hour_cost)
        QMessageBox.information(self, '成功', '停车场已初始化！')
        # 更新状态显示
        self.capacity_input.clear()
        self.per_hour_cost_input.clear()

        self.update_status()

    def arrive_car(self):
        if not self.plms:
            QMessageBox.warning(self, '错误', '请先初始化停车场！')
            return
        # 获取输入值
        car_number = self.car_number_input.text()
        entry_time = self.entry_time_input.text()
        # 验证输入
        if not car_number or not entry_time:
            QMessageBox.warning(self, '错误', '请输入有效的车牌号和进入时间！')
            return

        try:
            car_number = int(car_number)
            entry_time = int(entry_time)
        except ValueError:
            QMessageBox.warning(self, '错误', '请输入有效的数字！')
            return
        if car_number <= 0 or entry_time <= 0:
            QMessageBox.warning(self, '错误', '请输入有效的车牌号和进入时间！')
            return
        if self.plms.isExist(car_number):
            QMessageBox.warning(self, '错误', '车牌号已存在！')
            return
        if self.last_time >= entry_time:
            QMessageBox.warning(self, '错误', '输入时间必须大于上一次输入的时间！')
            return
        self.last_time = entry_time  # 更新上一次输入的时间
        
        # 车辆到达
        self.plms.arrive(car_number, entry_time)
        if self.plms.getParkingCount() >= self.plms.getCapacity():
            QMessageBox.information(self, '成功', f'车辆 {car_number} 停在便道 {self.plms.getWaitingCount()} 号车位！')
        else :
            QMessageBox.information(self, '成功', f'车辆 {car_number} 停在停车场 {self.plms.getParkingCount()} 号车位！')
        
        self.car_number_input.clear() 
        self.entry_time_input.clear() 

        QApplication.processEvents() 
        
        # 更新状态显示
        self.update_status()

    def depart_car(self):
        if not self.plms:
            QMessageBox.warning(self, '错误', '请先初始化停车场！')
            return
        # 获取输入值
        car_number = self.depart_car_number_input.text()
        exit_time = self.exit_time_input.text()
        # 验证输入
        if not car_number or not exit_time:
            QMessageBox.warning(self, '错误', '请输入有效的车牌号和离开时间！')
            return
        try:
            car_number = int(car_number)
            exit_time = int(exit_time)
        except ValueError:
            QMessageBox.warning(self, '错误', '请输入有效的数字！')
            return
        if car_number <= 0 or exit_time <= 0:
            QMessageBox.warning(self, '错误', '请输入有效的车牌号和离开时间！')
            return
        if exit_time <= self.last_time:
            QMessageBox.warning(self, '错误', '输入时间必须大于上一次输入的时间！')
            return
        self.last_time = exit_time  # 更新上一次输入的时间
        # 检查车辆是否在停车场
        parked_cars = self.plms.getParkingCount()
        if parked_cars == 0:
            QMessageBox.warning(self, '错误', '停车场中没有车辆！')
            return
        # 车辆离开
        result = self.plms.depart(car_number, exit_time)
        if result == parkingLotManagingSystem.ERROR:
            QMessageBox.warning(self, '错误', f'车牌号 {car_number} 不在停车场中！')
        else:
            QMessageBox.information(self, '成功', f'车辆 {car_number} 已离开，停车费用为 {result}')
        
        # 清空输入框
        self.depart_car_number_input.clear() 
        self.exit_time_input.clear() 
        QApplication.processEvents() 
        # 更新状态显示
        self.update_status()

    def process_console_input(self):
        """处理控制台输入"""
        if not self.plms:
            QMessageBox.warning(self, '错误', '请先初始化停车场！')
            return

        # 获取输入值
        input_text = self.console_input.text().strip()
        if not input_text:
            QMessageBox.warning(self, '错误', '请输入有效的数据！')
            return

        # 解析输入
        try:
            operation, car_number, time = input_text.strip('()').split(',')
            operation = operation.strip().upper()
            if operation == 'E':
                # 处理结束操作
                QMessageBox.information(self, '结束', '输入结束！')
                self.close()
                return
            car_number = int(car_number.strip())
            time = int(time.strip())
            if car_number <= 0 or time <= 0:
                QMessageBox.warning(self, '错误', '输入的车牌号或时间无效！')
                return
            # 检查时间是否升序
            if time <= self.last_time:
                QMessageBox.warning(self, '错误', '输入时间必须大于上一次输入的时间！')
                return
            self.last_time = time  # 更新上一次输入的时间

        except ValueError:
            QMessageBox.warning(self, '错误', '输入格式无效！')
            return

        # 处理操作
        if operation == 'A':
            if self.plms.isExist(car_number):
                QMessageBox.warning(self, '错误', '车牌号已存在！')
                return
            self.plms.arrive(car_number, time)
            if self.plms.getParkingCount() >= self.plms.getCapacity():
                QMessageBox.information(self, '成功', f'车辆 {car_number} 停在便道 {self.plms.getWaitingCount()} 号车位！')
            else :
                QMessageBox.information(self, '成功', f'车辆 {car_number} 停在停车场 {self.plms.getParkingCount()} 号车位！')
        elif operation == 'D':
            if self.plms.getParkingCount() == 0:
                QMessageBox.warning(self, '错误', '停车场中没有车辆！')
                return
            if not self.plms.isExist(car_number):
                QMessageBox.warning(self, '错误', f'车牌号 {car_number} 不在停车场中！')
                return
            cost = self.plms.depart(car_number, time)
            QMessageBox.information(self, '成功', f'车辆 {car_number} 已离开，停车费用为 {cost}')
        else:
            QMessageBox.warning(self, '错误', '无效的操作类型！')
        # 清空输入框
        self.console_input.clear()  
        # 更新状态显示
        self.update_status()

if __name__ == '__main__':
    NoDebug = 1
    if NoDebug:
        app = QApplication(sys.argv)
        ex = ParkingLotApp()
        ex.show()
        sys.exit(app.exec_())
    
    plms = parkingLotManagingSystem.parkingLotManagingSystem(10, 10)
    for i in range(3):
        carnumber = int(input("请输入车牌号："))
        time = int(input("请输入时间："))
        plms.arrive(carnumber, time)
    parked = plms.getParkingCar()
    print(type(parked))  # 应该显示 <class 'list'>
    print(type(parked[0]))  # 应该显示 <class 'parkingLotManagingSystem.ParkingInfo'>
    print(parked[0].carNumber)  # 检查第一个车辆的车牌号
    print(f"停车场中有 {len(parked)} 辆车辆")
    for car in parked:
        print(f"车牌号: {car.carNumber}, 进入时间: {car.entryTime}")
    