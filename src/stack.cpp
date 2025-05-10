#include<iostream>
#include"../inc/stack.h"

using namespace std;
template<class T>
Stack<T>::Stack(int size){
    this->size = size;
    top = -1;
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
Status Stack<T>::push(int data){
    if (top == size - 1){
        cout << "Stack is full" << endl;
        return ERROR;
    } else {
        top++;
        this->data[top] = data;
    }
    return OK; 
}

template<class T>
int Stack<T>::pop(){
    if (isEmpty()){
        cout << "Stack is empty" << endl;
        return ERROR; 
    } 
    else {
        int temp = data[top];
        top--;
        return temp; 
    }
}

template<class T>
int Stack<T>::peek(){
    if (isEmpty()){
        cout << "Stack is empty" << endl;
        return ERROR; 
    } 
    else {
        return data[top]; 
    }
}

