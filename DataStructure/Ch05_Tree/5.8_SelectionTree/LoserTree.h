#pragma once
#include<iostream>


using namespace std;
template<typename T>
class LinkedList;
template<typename T>
class LoserTree;

template<typename T>
class Node{
    public:
        friend class LinkedList<T>;
        friend class LoserTree<T>;
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
        friend class LoserTree<T>;
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

//Exmaple
/*
#include"Ch05_Tree/5.8_SelectionTree/LoserTree.h"
#include<iostream>
#include<vector>

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
    LoserTree<int> t(vec);
    while(!t.IsEnd()){
        cout<<"["<<t.Top()<<"] : ";
        // t.PrintTree();
        cout<<endl;
        t.Next();
    }
}
*/

template<typename T>
class LoserTree{
    public:
        LoserTree(vector<LinkedList<T>>& vec)
            :treeSize(GetTreeSize(vec))
        {
            tree = new LinkedList<T>*[treeSize];
            runs.resize(vec.size());
            fill_n(tree,treeSize,nullptr);
            runIndexTree = new int[treeSize];
            for(int i=0;i<vec.size();i++){
                runs[i] = &vec[i];
                ExtractNode(i,true);
            } 
        }

        //Top
        T Top() const{
            T ret = tree[0]->Front(); 
            tree[0]->PopFront();
            return ret;
        }

        //ExtractNode
        void ExtractNode(int runIndex,bool isInitial){
            LinkedList<T>* nowWin;
            int nowRunIndex = runIndex;

            if(runs[runIndex]->IsEmpty()) nowWin = nullptr;
            else nowWin = runs[runIndex]; 
            
            int treeIndex = runToTree(runIndex);
            int parent;
            tree[treeIndex] = nowWin;
            runIndexTree[treeIndex] = runIndex;
            treeIndex /= 2;

            while(treeIndex>0){
                if(nowWin == nullptr || (tree[treeIndex] != nullptr && nowWin->Front() < tree[treeIndex]->Front())){
                    if(nowWin == nullptr && tree[treeIndex]!=nullptr && !isInitial){ //말단 노드인 경우만으로 제한을 하면 해결되려니?
                        swap(nowWin,tree[treeIndex]);
                        swap(nowRunIndex, runIndexTree[treeIndex]);
                    }
                }else{
                    // if(isInitial || nowWin == nullptr || tree[treeIndex] != nullptr){
                    //     swap(nowWin,tree[treeIndex]);
                    //     swap(nowRunIndex, runIndexTree[treeIndex]);
                    // }
                    if(isInitial){
                        swap(nowWin,tree[treeIndex]);
                        swap(nowRunIndex, runIndexTree[treeIndex]);
                    }
                }
                treeIndex /= 2;             
            }
            tree[0] = nowWin;
            runIndexTree[0] = nowRunIndex;
        }
        void PrintTree() const{
            for(int i=0;i<treeSize;i++){
                if(tree[i] == nullptr){
                    cout<<"("<<runIndexTree[i]<<")_"<<" ";
                }else{
                    cout<<"("<<runIndexTree[i] <<")"<<tree[i]->Front()<<" ";

                }
            }
            cout<<endl;
        }
        //Next
        void Next(){
            int nowRun = runIndexTree[0];
            ExtractNode(nowRun,false);
            
        }

        //IsEnd
        bool IsEnd() const{
            return tree[0] == nullptr;
        }

    private:
        // pair<Node<T>*,int>* tree;
        LinkedList<T>** tree;
        vector<LinkedList<T>*> runs;
        int treeSize;
        int* runIndexTree;


        int GetTreeSize(const vector<LinkedList<T>>& vec) const{
            int s = 1;
            for(s=1; s<=vec.size(); s*=2);
            return s;
        }
        int treeToRun(int treeIndex) const{
            return treeIndex - treeSize/2;
        }
        int runToTree(int runIndex) const{
            return treeSize/2 + runIndex;
        }
};