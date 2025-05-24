#pragma once
#include "common.h"

template <class T>
class Queue {
    struct QueueNode
    {
        T data;
        QueueNode* next;
    };
    QueueNode* front;
    QueueNode* rear;
    int size;
    int count;
public:
    Queue(int size);
    ~Queue();
    bool isEmpty();
    void enqueue(T data);
    T dequeue();
    T peek();
    int getCount();
};