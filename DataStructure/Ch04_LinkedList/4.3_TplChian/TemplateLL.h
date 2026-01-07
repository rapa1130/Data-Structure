#pragma once
#include<iostream>
#include<algorithm>
using namespace std;

template<typename T>
class LinkedList;

template<typename T>
class ChainIterator;

template<typename T>
class LinkedStack;

template<typename T>
class LinkedQueue;

template<typename D>
class Node{
    public:
    friend LinkedList<D>;
    friend ChainIterator<D>;
    friend LinkedStack<D>;
    friend LinkedQueue<D>;
    
        Node(const D& data,Node* link) :data(data),link(link){}
    
    private:
        D data;
        Node* link;
};




template<typename T>
class LinkedList{
    public:
        class ChainIterator{
            public:
            // 구현한 반복자 STL Copy 에 사용해보기
        // 구현한 반복자 STL Accumulate 에 사용해보기
                ChainIterator(Node<T>* start=nullptr) : iterator(start){}
                ChainIterator& operator++() {
                    iterator=iterator->link;
                    return *this;
                }
                ChainIterator operator++(int){
                    ChainIterator old(iterator);
                    iterator=iterator->link;
                    return old;
                }
                //비교 연산자
                bool operator==(const ChainIterator& right) const{
                    return right.iterator == iterator;
                }
                bool operator!=(const ChainIterator& right) const{
                    return right.iterator != iterator;
                }
                T& operator*()const{
                    return iterator->data;
                }
                T* operator->()const{
                    return &iterator->data;
                }

            private:
                Node<T>* iterator;
        };
        LinkedList() :first(nullptr),last(nullptr){}
        void PushFront(const T& data){
            if(first)first = new Node<T>(data,first);
            else{
                first = last = new Node<T>(data,nullptr);

            } 
        }
        void PushBack(const T& data){
            if(last){
                last = last->link = new Node<T>(data,nullptr);
            }else{
                first = last=new Node<T>(data,nullptr);
            }
        }
        void PopFront(){
            Node<T>* toDel=first;
            first=first->link;
            delete toDel;
            
            if(first == nullptr){ last=nullptr; }
        }
        void Insert(Node<T>* prev,const T& data){
            if(first){
                prev->link = new Node<T>(data,prev->link);
            }else{
                first = new Node<T>(data,nullptr);
            }
        }
        void Delete(Node<T>* prev , Node<T>* toDelete){
            if(first){
                prev->link=toDelete->link;
                delete toDelete;
            }else{
                first = toDelete->link;
                delete toDelete;
            }
        }
        void DeleteAll(){
            Node<T>* next;
            for(Node<T>* now=first;now!=nullptr;now=next){
                next=now->link;
                delete now;
            }
            first=nullptr;            
        }
        void Print()const{
            for(Node<T>* now=first;now!=nullptr;now=now->link){
                cout<<now->data<<" ";
            }
            cout<<endl;
        }
        ChainIterator Begin() const{
            return ChainIterator(first);
        }
        ChainIterator End() const{
            return ChainIterator(last->link);
        }
        void Concatenate(LinkedList<T>& right){
            if(first) last->link = right.first;
            else first=right.first;
            last=right.last;
            right.first=right.last=nullptr;
        }
        void Reverse(){
            Node<T>* prev=nullptr;
            Node<T>* next;
            for(Node<T>* now=first;now!=nullptr;now=next){
                next=now->link;
                now->link=prev;
                prev=now;
            }
            swap(first,last);
        }
    protected:
        Node<T>* first;
        Node<T>* last;
};
