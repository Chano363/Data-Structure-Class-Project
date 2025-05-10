#include <iostream>
#include "../inc/queue.h"

using namespace std;

Queue::Queue(int size){
    this->size = size;
    front = rear = new QueueNode;
    front->next = nullptr;
    count = 0;
}

Queue::~Queue(){
    while (!isEmpty()){
        dequeue(); 
    }
    delete front;
    delete rear;
    count = 0;
}

bool Queue::isEmpty(){
    return count == 0; 
}

void Queue::enqueue(int data){
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

int Queue::dequeue(){
    if (isEmpty()){
        cout << "Queue is empty" << endl;
        return ERROR;
    }
    else {
        QueueNode* temp = front;
        int tempData = temp->data;
        front = front->next;
        delete temp;
        count--;
        return tempData;
    } 
}

int Queue::peek(){
    if (isEmpty()){
        cout << "Queue is empty" << endl;
        return ERROR;
    }
    else {
        return front->data;
    } 
}