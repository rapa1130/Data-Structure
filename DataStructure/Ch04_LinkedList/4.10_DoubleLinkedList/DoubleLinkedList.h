#pragma once
#include<iostream>
using namespace std;

template<typename T> class DoubleLinkedList;

template<typename T>
class DLNode{
    public:
        friend class DoubleLinkedList<T>;
        friend ostream& operator<<(ostream& os,const DoubleLinkedList<T>& DLlist);
        DLNode(const T& data ,DLNode<T>* left = nullptr ,DLNode<T>* right = nullptr)
            :left(left),right(right),data(data){}
        DLNode() : left(nullptr), right(nullptr) {}
    private:
        DLNode<T>* left;
        DLNode<T>* right;
        T data;
};


template<typename T>
class DoubleLinkedList{
    public:
        DoubleLinkedList(){
            first->right = first->left = first = new DLNode<T>();
        }
        void PushBack(const T& data){
            DLNode<T>* last = first->left;
            first->left = last->right = new DLNode<T>(data,last,right);
        }
        void PushFront(const T& data){
            DLNode<T>* second = first->right;
            first->right = second->left = new DLNode<T>(data,first,second);
        }
        void PopFront(){
            DLNode<T>* toDel = first->right;
            toDel->right->left = toDel->left;
            toDel->left->right = toDel->right;
            delete toDel;
        }
        void PopBack(){
            DLNode<T>* toDel= first->left;
            toDel->left->right = toDel->right;
            toDel->right->left = toDel->left;
            delete toDel;
        }
        bool IsEmpty() const{
            return first == first->right;
        }
        void Delete(DLNode<T>* toDel){
            DLNode<T>* prev= toDel->left;
            DLNode<T>* next= toDel->right;
            prev->right=next;
            next->left=prev;
            delete toDel;
        }
        friend ostream& operator<<(ostream& os,const DoubleLinkedList<T>& DLlist){
            for(DLNode<T>* now = DLlist.first->right; now!=DLlist.first ; now=now->right){
                os<<now->data<<" ";
            }
            os<<endl;
            return os;
        }
    private:
        DLNode<T>* first;
};

// template<typename T>
// ostream& operator<<(ostream& os,const DoubleLinkedList<T>& DLlist){
//     for(DLNode<T>* now = DLlist.first->right; now!=DLlist.first ; now=now->right){
//         os<<now->data<<" ";
//     }
//     os<<endl;
//     return os;
// }