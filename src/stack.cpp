#include<iostream>
#include"stack.h"
#include"common.h"
#include <stdexcept>

using namespace std;
template<class T>
Stack<T>::Stack(int size){
    this->size = size;
    top = -1;
    count = 0;
}

template<class T>
Stack<T>::~Stack(){}

template<class T>
bool Stack<T>::isEmpty(){
    return top == -1; 
}

template<class T>
Status Stack<T>::push(T data){
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
T Stack<T>::pop(){
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
T Stack<T>::peek(){
    if (isEmpty()){
        throw runtime_error("Stack is empty");
    } 
    else {
        return data[top]; 
    }
}

template<class T>
int Stack<T>::getCount(){
    return count;
}

template class Stack<int>;
template class Stack<ParkingInfo>;