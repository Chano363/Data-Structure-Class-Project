#include <iostream>
#include "queue.h"
#include <stdexcept>


using namespace std;
template<class T>
Queue<T>::Queue(int size)
// size: 队列的大小
// 初始化队列
{
    this->size = size;
    front = rear = new QueueNode;
    front->next = nullptr;
    count = 0;
}

template<class T>
Queue<T>::~Queue()
// 释放内存
{
    while (!isEmpty()){
        dequeue(); 
    }
    delete front;
    count = 0;
}

template<class T>
bool Queue<T>::isEmpty()
// 判断队列是否为空
{
    return count == 0; 
}

template<class T>
void Queue<T>::enqueue(T data)
// data: 要入队的数据
// 入队
{
    if (count == size){
        cout << "Queue is full" << endl;
        return; 
    }
    QueueNode* newNode = new QueueNode;
    newNode->data = data;
    newNode->next = nullptr; 
    if (isEmpty()){
        front = newNode;
        rear = newNode; 
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
    return;
}

template<class T>
T Queue<T>::dequeue()
// 出队
{
    if (isEmpty()){
        throw runtime_error("Queue is empty");
    }
    else {
        QueueNode* temp = front;
        T tempData = temp->data;
        front = front->next;
        delete temp;
        count--;
        return tempData;
    } 
}

template<class T>
T Queue<T>::peek()
// 返回队首元素
{
    if (isEmpty()){
        throw runtime_error("Queue is empty");
    }
    else {
        return front->data;
    } 
}

template<class T>
int Queue<T>::getCount()
// 返回队列中的元素个数
{
    return count;
}

template class Queue<ParkingInfo>;
template class Queue<int>;
