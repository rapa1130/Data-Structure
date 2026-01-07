#pragma once
#include<iostream>
using namespace std;

template<typename T>
void Change1DSize(T*& arr,int size, int newCapacity){
    T* temp = new T[newCapacity + 1];
    copy(arr,arr+size,temp);
    delete[] arr;
    arr=temp;
}

template<typename T>
class MaxPQ{
    public:
        MaxPQ(int capacity=10)
            :capacity(capacity),size(0)
        {
            heap= new T[capacity+1];
        }
        void Push(const T& data){
            if(capacity <= size){
                capacity *= 2;
                Change1DSize(heap,size,capacity);
            }
            int current = ++size;
            while(current>1 && data > heap[current/2]){
                heap[current] = heap[current/2];
                current/=2;
            }
            heap[current] = data;
        }
        void Pop(){
            const T& e = heap[size--];
            int child = 2;
            int parent = 1;
            while(child < size){
                if(heap[child] < heap[child + 1]) child++;
                if(heap[child] < e) break;
                heap[parent] = heap[child];
                parent = child;
                child *= 2;
            }
            heap[parent] = e;
            
        }
        bool IsEmpty() const{
            return size==0;
        }
        T Top() const{
            return heap[1];
        }
        void PrintQueue() const{
            for(int i=1;i<=size;i++){
                cout<<heap[i]<<" ";
            }
            cout<<endl;
        }
    private:
        int capacity;
        T* heap;
        int size;
};