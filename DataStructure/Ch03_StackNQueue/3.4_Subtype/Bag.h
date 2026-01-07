//#pragma once
#include<iostream>
using namespace std;


template<typename T>
class Bag{
public:
    Bag(int capacity=10);
    virtual void Push(const T& item);
    virtual void Pop();
    virtual T& Element() const;
    virtual int Size()const;
    virtual bool IsEmpty() const;
    virtual ~Bag();
protected:
    T* arr;
    int top;
    int capacity;
};

template<typename T>
Bag<T>::Bag(int capacity)
    :capacity(capacity),top(-1)
{
    arr=new T[capacity];
}

template<typename T>
void Bag<T>::Push(const T& item){
    if(top==capacity){
        T* temp=new T[capacity*2];
        copy(arr,arr+capacity,temp);
        delete[] arr;
        capacity*=2;
        arr=temp;
    }
    arr[++top]=item;
}

template<typename T>
void Bag<T>::Pop(){
    if(IsEmpty()) throw "This is Empty";
    int half=top/2;
    copy(arr+half+1,arr+top+1,arr+half);
    top--;
}
template<typename T>
T& Bag<T>::Element() const{
    if(IsEmpty()) throw "This is Empty";
    return arr[top];
}
template<typename T>
int Bag<T>::Size()const{
    return top+1;
}
//Size
template<typename T>
bool Bag<T>::IsEmpty() const{
    return Size()==0;
}
template<typename T>
Bag<T>::~Bag(){
    delete[] arr;
}

/*
template<typename T>
class Stack:public Bag<T>{
public:
    Stack(int capacity=10);
    T& Top() const;
    void Pop() const;
};
template<typename T>
Stack<T>::Stack(int capacity)
    :Bag<T>(capacity)
{
}
template<typename T>
T& Stack<T>::Top() const{
}

template<typename T>
void Stack<T>::Pop() const{
    if(this->IsEmpty()) throw "Stack is Empty!";
}*/