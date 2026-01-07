#pragma once

template<typename T>
class LinkedQueue;

template<typename T>
class QueueNode{
    public:
        QueueNode(const T& data = 0 ,QueueNode* link=nullptr) : data(data), link(link) {}
        friend LinkedQueue<T>;
    private:
        T data;
        QueueNode* link;
};

template<typename T>
class LinkedQueue{
    public:
        //Constructor
        LinkedQueue() : rear(nullptr), front(nullptr) {}
        //isEmpty
        bool IsEmpty(){
            return front == nullptr;
        }
        //Rear
        T Rear() const{
            return rear->data;
        }
        //Front
        T Front() const{
            return front->data;
        }
        //Pop
        void Pop(){
            QueueNode<T>* temp=front;
            front=front->link;
            delete temp;
        }
        //Push
        void Push(const T& data){
            if(rear) rear = rear->link = new QueueNode<T>(data,nullptr);
            else{
                front = rear = new QueueNode<T>(data,nullptr);
            }
        }
        //length
    private:
        QueueNode<T>* rear;
        QueueNode<T>* front;
};