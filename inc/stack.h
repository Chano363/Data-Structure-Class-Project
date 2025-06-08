#pragma once
#include "common.h"
#include <vector>

template <class T>
class Stack
{
    int size;
    int count;
    int top;
    std::vector<T> data;

public:
    Stack(int size);
    ~Stack();
    bool isEmpty() const;
    Status push(const T& data);
    T pop();
    T peek() const;
    int getCount() const;
};
