#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Queue{
public:
    Queue(int capacity=10)
        :capacity(capacity),front(0),rear(0)
    {
        arr=new T[capacity];
    }  

    void Push(const T& item){
        if(front == (rear+1) % capacity){
            int newCapacity = capacity * 2;
            T* temp=new T[newCapacity];

            int start = (front+1) % capacity;
            if(start<2){
                copy(arr+start,arr+rear + 1,temp);
            }
            else{
                copy(arr+start,arr + capacity,temp);
                copy(arr,arr+rear + 1,temp+(capacity-start));
            }
            front = newCapacity-1;
            rear = capacity-2;
            capacity=newCapacity;
            delete[] arr;
            arr=temp;
        }
        rear = (rear+1) % capacity;
        arr[rear] = item;
    } 

    void Pop(){
        if(IsEmpty()){
            throw "queue is empty";
        }
        front=(front+1)%capacity;
        //arr[front].T();
    }

    T& Front() const{
        if(IsEmpty()){
            throw "queue is empty";
        }
        return arr[(front+1) % capacity];
    }

    T& Rear() const{
        if(IsEmpty()){
            throw "queue is empty";
        }
        return arr[rear];
    }

    bool IsEmpty() const{
        return front==rear;
    }
    void Print()const{
        int index=(front+1)%capacity;
        while(index!=rear+1){
            cout<<arr[index]<<" ";
            index=(index+1)%capacity;
        }
        cout<<endl;
    }
private:
    T* arr;
    int capacity;
    int front;
    int rear;
};