#include<iostream>
#include"stack.h"
#include"common.h"
#include <stdexcept>

using namespace std;
template<class T>
Stack<T>::Stack(int size)
// size: 栈的大小
// 初始化栈
{
    this->size = size;
    top = -1;
    count = 0;
}

template<class T>
Stack<T>::~Stack(){}

template<class T>
bool Stack<T>::isEmpty()
// 判断栈是否为空
{
    return top == -1; 
}

template<class T>
Status Stack<T>::push(T data)
// data: 要入栈的数据
// 入栈
{
    if (top == size - 1){
        cout << "Stack is full" << endl;
        return ERROR;
    } else {
        top++;
        count++;
        this->data.push_back(data);
    }
    return OK; 
}

template<class T>
T Stack<T>::pop()
// 出栈
{
    if (isEmpty()){
        throw runtime_error("Stack is empty");
    } 
    else {
        T temp = data[top];
        top--;
        count--;
        return temp; 
    }
}

template<class T>
T Stack<T>::peek()
// 查看栈顶元素
{
    if (isEmpty()){
        throw runtime_error("Stack is empty");
    } 
    else {
        return data[top]; 
    }
}

template<class T>
int Stack<T>::getCount()
// 返回栈中的元素个数
{
    return count;
}

template class Stack<int>;
template class Stack<ParkingInfo>;