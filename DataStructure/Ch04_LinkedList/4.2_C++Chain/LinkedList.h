#pragma once
#include <iostream>
using namespace std;
class LinkedList{
    public:
        class Node{
            public:
                Node(int data=0,Node* link = nullptr) : data(data),link(link) {}
                friend LinkedList;
            private:
                int data;
                Node* link;
        };

        LinkedList():first(nullptr){}
        void PushFront(int data){
            if(first){
                first = new Node(data,first);
            }else{
                first = new Node(data,nullptr);
            }
        }        
        void Insert(Node* prev,int data){
            if(first){
                prev->link=new Node(data,prev->link);
            }else{
                first=new Node(data);
            }
        }
        LinkedList merge(LinkedList& r){
            LinkedList ret;
            ret.first=first;
            Node* last=ret.first;
            if(ret.first){
                for(;last->link!=nullptr;last=last->link);
                last->link=r.first;
            }else{
                ret.first=r.first;
            }
            first=nullptr;
            r.first=nullptr;
            return ret;
        }
        void DeleteAll(){
            Node* now=first;
            while(now!=nullptr){
                Node* next=now->link;
                delete now;
                now=next;
            }
            first=nullptr;
        }
        //delete(Node* prev,Node* toDelete)
        void Delete(Node* prev, Node* toDelete){
            if(first==toDelete) first=first->link;
            else prev->link = toDelete->link;
            delete toDelete;

        }
        void Print()const{
            Node* now=first;
            while(now!=nullptr){
                cout<<now->data<<" ";
                now=now->link;
            }cout<<endl;
        }
        int length(){
            int len=0;
            for(Node* now=first;now!=nullptr;now=now->link) len++;
            return len;
        }
        Node* test(){
            return first->link;
        }
        Node* test2(){
            return first->link->link;
        }
    private:
        Node* first;
};