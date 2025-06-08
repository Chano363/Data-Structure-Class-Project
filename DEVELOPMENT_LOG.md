# 开发日志

## 技术决策记录
记录重要的架构设计和算法选择

### 2025-06-08 - 重复输出问题分析

#### 问题描述
- 测试代码工作正常但GUI出现重复输出
- 主要发生在`getParkingCar()`方法调用时

#### 测试代码工作正常的原因
 **顺序执行特性**  
测试代码是顺序执行的，没有其他操作干扰  
 **即时处理结果**  
调用`getParkingCar()`后立即处理结果  
 **对象生命周期**  
临时对象在函数调用之间没有被覆盖  

#### GUI不能工作的原因
**事件循环影响**  
GUI有事件循环，可能导致内存重用  
**语言边界问题**  
PyQt的Python/C++边界可能导致对象生命周期问题  
**方法调用问题**  
多次调用`getParkingCar()`可能暴露了对象重用问题  

#### 对象生命周期分析
**问题根源：对象生命周期管理**

在C++中，对象生命周期管理是核心问题。让我们分析原始代码中的对象流程：

​​arrive函数中的临时对象​​：
```
Status arrive(int carNumber, int entryTime) {
    ParkingInfo temp; // 在栈上创建临时对象
    temp.carNumber = carNumber;
    temp.entryTime = entryTime;
    parkingStack->push(temp); // 将临时对象的副本压入栈
} // 函数结束时，temp对象被销毁
​​栈的实现问题​​：
template<class T>
Status Stack<T>::push(T data) {
    this->data.push_back(data); // 存储的是data的副本
}
```
**为什么会显示第一个车辆信息？**

问题在于​​对象复制语义​​和​​内存重用​​：(事实上并不是这里的问题)

​​第一次调用arrive​​：创建临时对象temp1(carNumber=1)<br>
将temp1的副本压入栈<br>
temp1在函数结束时被销毁<br>
但副本存储在栈的vector中<br>
​​第二次调用arrive​​：<br>
创建临时对象temp2 (carNumber=2)<br>
但temp2可能使用与temp1相同的内存位置<br>
将temp2的副本压入栈<br>
由于栈的vector存储的是副本，而不是引用<br>

**如何解决？**
1. 避免对象复制：使用引用或指针
2. 自定义深拷贝函数
3. 对象池管理：对象放到对象池里，栈和队列对对象池里的元素进行操作，对象池里的对象不会（因函数结束）被销毁，而是被重复利用

#### 问题真正的解决
stack中的data容器，pop操作没有进行pop_back()操作，而之后getParking操作仍然遍历整个data容器，而不是截取下标从0到top的部分，导致了重复输出。