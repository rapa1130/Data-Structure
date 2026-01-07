#pragma once
#include"Queue.h"
#include<iostream>
using namespace std;

template<typename T>
class Deque : public Queue<T>{
public:
    Deque(int capacity=10):Queue<T>(capacity){
        this->rear=0;
        this->front=0;
    }
    void Push_Back(const T& item){
        this->Push();
    }
    void Push_Front(const T& item){
        if((this->rear + 1)%this->capacity == this->front){
            T* temp = new T[this->capacity*2];
            int start=(this->front + 1)%this->capacity;
            if(start<2){
                copy(this->arr + start,this->arr +this->rear + 1,temp);
            }
            else{
                copy(this->arr + start,this->arr+this->capacity,temp);
                copy(this->arr,this->arr+this->rear+1,temp+this->capacity -start);
            }
            delete[] this->arr;
            this->arr=temp;
            this->front = 2 * this->capacity - 1;
            this->rear = this->capacity - 2;
            this->capacity *= 2;
        }
        this->arr[this->front] = item;
        this->front = (this->front==0) ? this->capacity - 1 : this->front-1;

    }
    void Pop_Back(){
        if(this->IsEmpty()) throw "Deque is Empty!";
        //cout<<"rear:"<<this->rear<<endl;
        this->rear=this->rear==0? this->capacity-1 : this->rear - 1 ;
    }
    void Pop_Front(){
        this->Pop();
    }
};