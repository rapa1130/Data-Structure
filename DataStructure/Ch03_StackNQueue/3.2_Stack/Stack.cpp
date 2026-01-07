//#include"Stack.h"


/*

#include<iostream>
#include"Stack.h"
using namespace std;


template <typename T>
inline Stack<T>::Stack(int capacity)
    : capacity(capacity), size(0)
{
    if(capacity<1) throw "capacity is more than 1";
    arr=new T[capacity];
}

template <typename T>
bool Stack<T>::isEmpty() const
{
    return size==0;
}

template <typename T>
T &Stack<T>::Top() const
{
    if(isEmpty()){
        throw "Stack is Empty";
    }
    return arr[size-1];
}

template <typename T>
void Stack<T>::Push(const T &item)
{
    if(capacity==size){
        capacity*=2;
        T* temp=new T[capacity];
        copy(arr,arr+size,temp);
        delete[] arr;
        arr=temp;
    }
    arr[size]=item;
    size++;
}

template <typename T>
void Stack<T>::Pop()
{
    if(isEmpty()){
        throw "Stack is Empty";
    }
    size--;
}

template <typename T>
Stack<T> &Stack<T>::SplitHalf()
{
    // TODO: 여기에 return 문을 삽입합니다.
}

template <typename T>
Stack<T> &Stack<T>::MergeStack(const Stack &stack) const
{
    // TODO: 여기에 return 문을 삽입합니다.
}

template<typename T>
ostream& operator<<(ostream& os,const Stack<T>& stack){
    for(int i=0;i<stack.size;i++){
        os<<stack.arr[i]<<" ";
    }
    os<<endl;
}

//#ifndef STACK_H
//#define STACK_H

*/
#include"Stack.h"