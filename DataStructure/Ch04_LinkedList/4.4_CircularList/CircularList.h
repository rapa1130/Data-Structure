#pragma once
#include<iostream>
using namespace std;
template<typename T>
class CircularList;

template<typename T>
class LinkListIterator;

template<typename T>
class Node{
    public:
        Node(const T& data = 0 ,Node* link=nullptr) : data(data), link(link) {}
        friend CircularList<T>;
        friend LinkListIterator<T>;
    private:
        T data;
        Node* link;
};


template<typename T>
class CircularList{
    public:
        class LinkListIterator{
            public:
                //constructor
                LinkListIterator(Node<T>* start = nullptr):now(start){}
                //operator ++
                LinkListIterator operator++(){ //pre
                    now=now->link;
                    return *this;                        
                }
                LinkListIterator operator++(int){ //pre
                    LinkListIterator ret(now);
                    now=now->link;
                    return now;                        
                }
                //opertor==
                bool operator==(const LinkListIterator& right) const{
                    return now==right.now;
                }
                //opertor!=
                bool operator!=(const LinkListIterator& right) const{
                    return now!=right.now;
                }
                //opertor&
                T* operator->(){
                    return &now->data;
                }
                //opertor*
                T& operator*(){
                    return now->data;
                }
                friend CircularList<T>;
            private:
                Node<T>* now;
        };
        CircularList() : last(nullptr) {}
        void PushFront(const T& data){
            // if(last) last->link = new Node<T>(data , last->link);
            // else{
            //     last = new Node<T>(data ,nullptr);
            //     last->link=last;
            // } 
            if(last){
                Node<T>* newNode= GetNode();
                newNode->data=data;
                newNode->link = last->link;
                last->link =newNode;
            }else{
                Node<T>* newNode=GetNode();
                newNode->data=data;
                newNode->link=nullptr;
                last=newNode;
                last->link=last;
            }
        }
        void PushBack(const T& data){
            if(last) {
                // last->link = new Node<T>(data , last->link);
                Node<T>* newNode = GetNode();
                newNode->data=data;
                newNode->link=last->link;
                last->link=newNode;
                last = last->link;
            }
            else{
                Node<T>* newNode = GetNode();
                newNode->data=data;
                newNode->link=nullptr;
                last=newNode;
            }
        }
        void Print()const{
            cout<<"[";
            if(last){
                Node<T>* now = last->link;
                do{
                    cout<<now->data<<" ";
                    now=now->link;
                }while(now != last->link);
            }
            cout<<"]"<<endl;
        }
        //length
        int length()const{
            if(last){
                int len=1;
                for(Node<T>* now=last->link;now!=last;now=now->link,len++);
                return len;
            }else{
                return 0;
            }
        }
        LinkListIterator Begin() const{
            return LinkListIterator(last->link);
        }
        LinkListIterator End() const{
            return LinkListIterator(last->link);
        }
        //delete
        void Delete(const LinkListIterator& prev,const LinkListIterator& toDelete){
            //1개만 남은 경우에 대한 처리(prev 사용이 무의미한 시점)
            if(toDelete.now->link == toDelete.now){
                delete toDelete.now;
                last=nullptr;
                return;
            }

            //last에 대한 처리
            if(toDelete==last){
                last=prev.now;
            }
            prev.now->link=toDelete.now->link;
            delete toDelete.now;
        }
        //delete All
        void DeleteAll(){
            if(last){
                Node<T>* now = last->link;
                do{
                    Node<T>* next=now->link;
                    delete now;
                    now=next;
                }while(now!=last);
                last=nullptr;
            }
        }
        //Merge
        void Merge(CircularList<T>& right){
            Node<T>* first=last->link;
            last->link = right.last->link;                        
            right.last->link = first;
            last=right.last;
            right.last=nullptr;
        }
        //min
        int Min()const{
            if(last){
                Node<T>* now=last->link;
                int min=INT32_MAX;
                do{
                    if(min > now->data) min = now->data;
                    now=now->link;
                }while(now!=last);
                return min;
            }else{
                return INT32_MAX;
            }
        }
        Node<T>* GetNode(){
            if(av){
                Node<T>* x = av;
                av = av->link;
                return x;
            }else{
                return new Node<T>();
            }
        }
        void RetNode(Node<T>*& ret){
            ret->link=av;
            av=ret;
            ret=nullptr;
        }
        ~CircularList(){
            if(last){
                Node<T>* first = last->link;
                last->link = av;
                av = first;
                last = nullptr;
            }
            cout<<"Av:";
            for(Node<T>* now=av;now!=nullptr;now=now->link){
                cout<<now->data<<" ";
            }
            cout<<endl;
        }
    private:
        Node<T>* last;
        static Node<T>* av;
};

template<typename T>
Node<T>* CircularList<T>::av = nullptr;