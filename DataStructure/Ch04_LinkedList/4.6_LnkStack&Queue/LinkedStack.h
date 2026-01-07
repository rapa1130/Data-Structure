#pragma once

template<typename T>
class LinkedStack;

template<typename T>
class Node{
    public:
        Node(const T& data = 0 ,Node* link=nullptr) : data(data), link(link) {}
        friend LinkedStack<T>;
    private:
        T data;
        Node* link;
};

template<typename T>
class LinkedStack{
    public:
        LinkedStack():top(nullptr){}
        bool IsEmpty() const{
            return top==nullptr;
        }
        T Top() const{
            return top->data;
        }
        void Push(const T& data){
            top=new Node<T>(data,top);
        }
        void Pop(){
            if(IsEmpty()) throw "Stack is Empty to Pop.";
            Node<T>* toDel=top;
            top=top->link;
            delete toDel;
        }
    private:
        Node<T>* top;
};