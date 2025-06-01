import os
import subprocess
import shutil
import time

# 删除 build 目录
if os.path.exists("build"):
    shutil.rmtree("build")

# 创建 build 目录
os.makedirs("build")

# 进入 build 目录
os.chdir("build")

# 运行 CMake
try:
    # 定义 CMake 配置命令
    cmake_command = [
        "cmake",
        "-G", "MinGW Makefiles",
        ".."  
    ]
    # 运行 CMake 配置命令
    subprocess.run(cmake_command, check=True)
except subprocess.CalledProcessError as e:
    print(f"CMake 配置失败: {e}")
    print("请检查 CMakeLists.txt 文件或环境变量配置。")
    exit(1)

time.sleep(1)

# 编译项目
try:
    subprocess.run(["cmake", "--build", ".", "--config", "Release", "--target", "package_python"], check=True)
except subprocess.CalledProcessError as e:
    print(f"编译失败: {e}")
    exit(1)

print("构建成功！")

# 删除 output/temp 文件夹里的文件
temp_dir = os.path.join("..", "output", "temp")
if os.path.exists(temp_dir):
    for root, dirs, files in os.walk(temp_dir, topdown=False):
        for file in files:
            file_path = os.path.join(root, file)
            os.remove(file_path)
        for dir in dirs:
            dir_path = os.path.join(root, dir)
            shutil.rmtree(dir_path)
    print(f"{temp_dir} 里的文件已删除。")
else:
    print(f"{temp_dir} 目录不存在。")