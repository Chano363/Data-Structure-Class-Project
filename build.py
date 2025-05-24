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
    subprocess.run(["cmake", "-G", "MinGW Makefiles", ".."], check=True)
except subprocess.CalledProcessError as e:
    print(f"CMake 配置失败: {e}")
    print("请检查 CMakeLists.txt 文件或环境变量配置。")
    exit(1)

time.sleep(1)

# 编译项目
try:
    subprocess.run(["cmake", "--build", ".", "--config", "Release"], check=True)
except subprocess.CalledProcessError as e:
    print(f"编译失败: {e}")
    exit(1)

print("构建成功！")