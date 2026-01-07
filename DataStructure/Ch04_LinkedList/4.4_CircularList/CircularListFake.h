#pragma once

#include<iostream>
using namespace std;

template<typename T>
class CircularLinkedList;

template<typename T>
class Node{
    public:
        Node(const T& data,Node<T>* link = nullptr) :data(data),link(link) {}
        Node(Node<T>* link) :link(link) {
        }
        friend CircularLinkedList<T>;
        
    private:
        T data;
        Node<T>* link;
};


template<typename T>
class CircularLinkedList{
    public:
        class Iterator{
            public:
                Iterator(Node<T>* start) : current(start) {}
                bool operator==(const Iterator& right) const{
                    return current == right.current;
                }
                bool operator!=(const Iterator& right) const{
                    return current != right.current;
                }
                T& operator*() const{
                    return current->data;
                }
                T* operator->() const{
                    return &current->data;
                }
                Iterator operator++(){
                    current=current->link;
                    return *this;
                }
                Iterator operator++(int){
                    Iterator ret = *this;
                    current=current->link;
                    return ret;
                }
            private:
                Node<T>* current;
        };
        //Constructor
        CircularLinkedList(const T& fake)
        {
            // last->link = last = new Node<T>(fake,nullptr);
            last=new Node<T>(fake,nullptr);
            last->link=last;
        }
        CircularLinkedList()
        {
            last=new Node<T>(nullptr);
            last->link=last;
        }
        CircularLinkedList operator=(const CircularLinkedList& right){
            if(last!=last->link){
                while(last!=last->link){
                    PopFront();
                }
                last->link=last;
            }
            cout<<"Pop finish"<<endl;
            for(auto iter=right.Begin();iter!=right.End();iter++){
                PushBack(*iter);
            }
            return *this;
        }
        Iterator Begin() const{
            Node<T>* head=last->link;
            return Iterator(head->link);
        }
        //end
        Iterator End() const{
            return Iterator(last->link);
        }
        //PushBack
        void PushBack(const T& data){
            last = last->link = new Node<T>(data,last->link);
        }
        //PushFront
        void PushFront(const T& data){
            Node<T>* head = last->link;
            if(head==last){
                last = head->link = new Node<T>(data,head);
            }else{
                head->link = new Node<T>(data,head->link);
            }
            
        }
        //PopFront
        void PopFront(){
            Node<T>* head=last->link;
            Node<T>* toDel=head->link;
            head->link=toDel->link;
            delete toDel;
            if(head== head->link){
                last=head;
            }
            
        }
        //Print
        void Print() const{
            for(CircularLinkedList<T>::Iterator iter=Begin();iter!=End();iter++){
                cout<<*iter<<endl;
            }
            cout<<endl;
        }
        void DeleteAll(){
            while(!IsEmpty()){
                PopFront();
            }
        }
        CircularLinkedList Reverse(){
            CircularLinkedList<T> reversed;
            for(Iterator iter=Begin();iter!=End();++iter){
                reversed.PushFront(*iter);
            }
            return reversed;
        }
        bool IsEmpty() const{
            return last == last->link;
        }
    private:
        Node<T>* last;
};