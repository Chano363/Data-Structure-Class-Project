#include<iostream>
#include"../inc/stack.h"

using namespace std;
template<class T>
Stack<T>::Stack(int size){
    this->size = size;
    top = -1;
    count = 0;
    data = new int[size];
    if (data == NULL){
        cout << "Memory allocation failed" << endl;
        return; 
    }
    count = 0;
}

template<class T>
Stack<T>::~Stack(){
    delete[] data; 
}

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
        this->data[top] = data;
    }
    return OK; 
}

template<class T>
T Stack<T>::pop(){
    if (isEmpty()){
        cout << "Stack is empty" << endl;
        return ERROR; 
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
        cout << "Stack is empty" << endl;
        return ERROR; 
    } 
    else {
        return data[top]; 
    }
}

template<class T>
int Stack<T>::getCount(){
    return count;
}