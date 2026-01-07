#pragma once
#include"Bag.h"
#include<iostream>
using namespace std;

template<typename T>
class Queue : public Bag<T>{
public:
    Queue(int capacity=10) :Bag<T>(capacity),front(0),rear(0){
    }
    void Pop() override{
        if(this->IsEmpty()) throw "Queue is Empty!";
        front=(front+1)%this->capacity;
    }
    void Push(const T& item) override{
        if(((rear+1)%this->capacity)==front){
            T* temp=new T[this->capacity*2];
            int start=(front+1)%this->capacity;
            if(start<2){
                copy(this->arr+start,this->arr+rear+1,temp);
            }
            else{
                copy(this->arr+start,this->arr+this->capacity,temp);
                copy(this->arr,this->arr + rear + 1,temp+(this->capacity-start));
            }
            delete[] this->arr;
            this->arr=temp;
            front=this->capacity*2 - 1;
            rear=this->capacity - 2;
            this->capacity *= 2;
        }
        rear=(rear+1)%this->capacity;
        this->arr[rear]=item;
    }
    bool IsEmpty() const override{
        return front==rear;
    }
    int Size() const override {
        int start=(front+1)%this->capacity;
        if(start<2) return rear-start+1;
        else{
            int size=0;
            size+=this->capacity-start;
            size+=rear + 1;
            return size;
        }
    }
    virtual T& Front() const{
        if(this->IsEmpty()) throw "Queue is Empty!";
        return this->arr[((front+1)%this->capacity)];
    }
    virtual T& Rear() const{
        if(this->IsEmpty()) throw "Queue is Empty!";
        return this->arr[rear];
    }
protected:
    int front;
    int rear;
};