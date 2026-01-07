//#pragma once
#pragma once
#include"Bag.h"
using namespace std;

template<typename T>
class Stack:public Bag<T>{
public:
    Stack(int capacity=10)
        :Bag<T>(capacity)
    {
    }
    T& Top() const{
        return this->arr[this->top];
    }
    void Pop() {
        if(this->IsEmpty()) throw "Stack is Empty!";
        (this->top)--;
    }
};

/*template<typename T>
Stack<T>::Stack(int capacity) :Bag<T>(capacity){

}
template<typename T>
T& Stack<T>::Top() const{
    T ret;
    return ret;
}

template<typename T>
void Stack<T>::Pop() const{
    if(IsEmpty()) throw "Stack is Empty!";
}*/