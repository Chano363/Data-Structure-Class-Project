#pragma once
#include"common.h"

template<class T>
class Stack{
int size;
int count;
int top;
std::vector<T>data;
public:
    Stack(int size);
    ~Stack();
    bool isEmpty();
    Status push(int data);
    int pop();
    int peek();
};
