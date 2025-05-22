#include <iostream>
#include "queue.h"
#include <stdexcept>


using namespace std;
template<class T>
Queue<T>::Queue(int size){
    this->size = size;
    front = rear = new QueueNode;
    front->next = nullptr;
    count = 0;
}

template<class T>
Queue<T>::~Queue(){
    while (!isEmpty()){
        dequeue(); 
    }
    delete front;
    delete rear;
    count = 0;
}

template<class T>
bool Queue<T>::isEmpty(){
    return count == 0; 
}

template<class T>
void Queue<T>::enqueue(T data){
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
T Queue<T>::dequeue(){
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
T Queue<T>::peek(){
    if (isEmpty()){
        throw runtime_error("Queue is empty");
    }
    else {
        return front->data;
    } 
}

template<class T>
int Queue<T>::getCount(){
    return count;
}

template class Queue<ParkingInfo>;
template class Queue<int>;
