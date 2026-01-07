#pragma once
#include"../4.3_TplChian/TemplateLL.h"

template <typename T>
class LinkedQueue : public LinkedList<T>{
    public:
        void Push(const T& data){
            this->PushBack(data);
        }
        void Pop(){
            this->PopFront();
        }
        T Front() const{
            return this->first->data;
        }
        T Rear() const{
            return this->last->data;
        }
        bool IsEmpty() const{
            return this->first == nullptr;
        }

    private:
        //Node<T>* front;
        //Node<T>* rear;
};