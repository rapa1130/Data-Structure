#pragma once
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
template<typename T>
class LinkedList;
template<typename T>
class WinnerTree;

template<typename T>
class Node{
    public:
        friend class LinkedList<T>;
        friend class WinnerTree<T>;
        // friend ostream& operator<<(ostream& os, const LinkedList<T> list);
        Node():next(nullptr){}
        Node(const T& data) :data(data),next(nullptr){}
        Node(const T& data,Node<T>* next) :data(data),next(next){}
        Node(Node<T>* next):next(next) {}
    private:
        T data;
        Node<T>* next;
};

template<typename T>
class LinkedList{
    public:
        friend class WinnerTree<T>;
        LinkedList(){
            last->next = last = new Node<T>();
        }
        void PushBack(const T& data){
            last = last->next = new Node<T>(data,last->next);
        }
        void PushFront(const T& data){
            Node<T>* first = last->next;
            first->next = new Node<T>(data,first->next);
            if(last == first){
                last = first->next;
            }
        }
        //front
        T& Front() const{
            return (last->next->next)->data;
        }
        //popfront
        void PopFront(){
            Node<T>* first = last->next;
            Node<T>* toDel = first->next;
            first->next = toDel->next;
            if(toDel == last) last = first;
            delete toDel;
        }
        //isEmpty
        bool IsEmpty() const{
            return last == last->next;
        }
        friend ostream& operator<<(ostream& os, const LinkedList<T> list){
            Node<T>* first = list.last->next;
            for(Node<T>* now = first->next ; now != first ; now = now->next){
                os<<now->data<<" ";
            }
            return os;
        }
    private:
        Node<T>* last;
};


//TestCode
/*
#include<iostream>
#include"Ch05_Tree/5.8_SelectionTree/WinnerTree.h"
using namespace std;

vector<LinkedList<int>> GetLLVec(){
    LinkedList<int> a;
    a.PushBack(3);
    a.PushBack(5);
    a.PushBack(10);
    LinkedList<int> b;
    b.PushBack(1);
    b.PushBack(18);
    b.PushBack(30);
    LinkedList<int> c;
    c.PushBack(15);
    c.PushBack(16);
    c.PushBack(44);
    LinkedList<int> d;
    d.PushBack(2);
    d.PushBack(8);
    d.PushBack(99);


    vector<LinkedList<int>> vec;
    vec.push_back(a);
    vec.push_back(b);
    vec.push_back(c);
    vec.push_back(d);
    return vec;
}


int main(){
    vector<LinkedList<int>> vec = GetLLVec();
    WinnerTree<int> tree(&vec);

    do{
        cout<<tree.Top()<<endl;
        tree.Next();
    }while(!tree.IsEnd());

    
}

*/

template<typename T>
class WinnerTree{
    public:
        //생성자
        WinnerTree(vector<LinkedList<T>>* sequences)
        :treeSize(GetTreeSize(sequences))
        {
            this->nowRun.resize(sequences->size());
            this->firsts.resize(sequences->size());
            for(int i=0;i<sequences->size();i++){
                this->nowRun[i] = (*sequences)[i].last->next->next;
                firsts[i] = (*sequences)[i].last->next;
            }
            tree = MakeTree(sequences, treeSize);
            runIndexTree = new int[treeSize];
            InitializeTree();
        }
        
        
        
        void PrintTree() const{
            for(int i=1;i<treeSize;i++){
                if(tree[i] != nullptr){
                    cout<<"("<<runIndexTree[i] <<")"<<tree[i]->data<<" ";
                }else{
                    cout<<"(_)"<<"_"<<" ";
                }
            }

        }
        
        void ExtractNode(int runIndex){
            int treeIndex = (treeSize/2) + runIndex;
            if(nowRun[runIndex] == firsts[runIndex]){
                delete tree[treeIndex];
                tree[treeIndex] = nullptr;
            }else{
                tree[treeIndex] =nowRun[runIndex];
                nowRun[runIndex] = nowRun[runIndex]->next;
            }
            
            runIndexTree[treeIndex] = runIndex;

            while(treeIndex>1){
                int sibling = treeIndex + (treeIndex % 2 == 0 ? 1: -1);
                int parent = treeIndex / 2;
                if(tree[treeIndex] != nullptr && (tree[sibling] == nullptr ||  tree[treeIndex]->data < tree[sibling]->data)){
                    tree[parent] = tree[treeIndex];
                    runIndexTree[parent] = runIndexTree[treeIndex];
                }else{
                    tree[parent] = tree[sibling];
                    runIndexTree[parent] = runIndexTree[sibling];
                }
                treeIndex = parent;
            }

        }
        
        T Top() const{
            return tree[1]->data;
        }

        void Next() {
            int topRunIndex = runIndexTree[1];
            ExtractNode(topRunIndex);
        }
        bool IsEnd() const{
            return tree[1] == nullptr;
        }



    private:
        Node<T>** tree; 
        int* runIndexTree;
        int treeSize;
        vector<Node<T>*> nowRun;
        vector<Node<T>*> firsts;

        void InitializeTree(){
            for(int i=0;i<nowRun.size();i++){
                ExtractNode(i);
            }
        }
        Node<T>** MakeTree(vector<LinkedList<T>>* sequences, int treeSize){
            Node<T>** ret;

            ret = new Node<T>*[treeSize];
            fill_n(ret,treeSize,new Node<T>(INT32_MAX));
            return ret;
        }
        int GetTreeSize(vector<LinkedList<T>>* sequences) const{
            int n = sequences->size();
            int s;
            for(s = 1; s < n; s*=2);
            return s*2 ;
        }
};
