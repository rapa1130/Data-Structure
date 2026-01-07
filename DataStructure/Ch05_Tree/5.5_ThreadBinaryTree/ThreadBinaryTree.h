#pragma once
#include<iostream>
using namespace std;

template<typename T>
class ThreadBinaryTree;

template<typename T>
class ThreadNode{
    public:
        ThreadNode()
            :leftLink(nullptr),rightLink(nullptr),threadLeft(false),threadRight(false){}
        ThreadNode(const T& data,ThreadNode<T>* leftLink,ThreadNode<T>* rightLink,bool threadLeft,bool threadRight)
            :data(data),leftLink(leftLink),rightLink(rightLink),threadLeft(threadLeft),threadRight(threadRight){}
        ThreadNode(const T& data,ThreadNode<T>* leftLink,ThreadNode<T>* rightLink)
            :data(data),leftLink(leftLink),rightLink(rightLink),threadLeft(false),threadRight(false){}
        ThreadNode(ThreadNode<T>* leftLink,ThreadNode<T>* rightLink)
            :leftLink(leftLink),rightLink(rightLink),threadLeft(false),threadRight(false){}
        ThreadNode(ThreadNode<T>* leftLink,ThreadNode<T>* rightLink,bool threadLeft,bool threadRight)
            :leftLink(leftLink),rightLink(rightLink),threadLeft(threadLeft),threadRight(threadRight){}
        friend class ThreadBinaryTree<T>;
    private:
        T data;
        ThreadNode<T>* leftLink;
        ThreadNode<T>* rightLink;
        bool threadLeft;
        bool threadRight;
        
};

template<typename T>
class ThreadBinaryTree{
    public:
        ThreadBinaryTree(){
            first = new ThreadNode<T>(nullptr,nullptr,true,false);
            first->rightLink = first->leftLink = first;
        }
        class Iterator{
            public:
                Iterator(ThreadNode<T>* first)
                    :current(first){}
                Iterator operator++(int){
                    ThreadNode<T>* temp = current->rightLink;
                    if(!current->threadRight)
                        while(!temp->threadLeft) temp=temp->leftLink;
                    current = temp;

                    return *this;
                }
                Iterator operator++(){
                    ThreadNode<T>* temp = current->rightLink;
                    if(!current->threadRight)
                        while(!temp->threadLeft) temp=temp->leftLink;
                    current = temp;

                    return temp;
                }
                T& operator*() const{
                    return current->data;
                }
                T* operator->() const{
                    return &current->data;
                }
                bool operator==(const Iterator& right) const{
                    return current->data == right.current->data;
                }
                bool operator!=(const Iterator& right) const{
                    return current->data != right.current->data;
                }
            private:
                ThreadNode<T>* current;
        };
        Iterator Begin() const{
            return Iterator(first->leftLink);
        }
        Iterator End() const{
            return Iterator(first);
        }
        //입력
        friend istream& operator>>(istream& is,ThreadBinaryTree<T>& right){
            string expression;
            cin>>expression;
            int index=0;
            right.treeFromString(expression,index,right.first,right.first->leftLink,true);
            return is;
        }
        friend ostream& operator<<(ostream& os,const ThreadBinaryTree<T>& right){
            ThreadNode<T>* now = right.InOrderSuccessor(right.first);
            for( ; now != right.first ;){
                os<< now->data<<" ";
                if(!now->threadRight){
                    for(now = now->rightLink;!now->threadLeft;now=now->leftLink);
                }else{
                    now=now->rightLink;
                }
            }
            os<<endl;
            return os;
        }
        void InsertLeft(ThreadNode<T>* parent,ThreadNode<T>* child){
            
            child->threadLeft = parent->threadLeft;
            child->leftLink = parent->leftLink;
            child->threadRight = true;
            child->rightLink = parent;
            parent->leftLink = child;
            parent->threadLeft = false;
            if(!child->threadLeft){
                ThreadNode<T>* temp = InOrderPredesessor(child);
                temp->rightLink = child;
            }
            cout<<"[L] parent: "<<parent->data<<"  "<<parent<<" l:"<<parent->leftLink<<" r:"<<parent->rightLink<<endl;
            cout<<"[L] child:  "<<child->data<<"  " <<child<<" l:"<<child->leftLink<<" r:"<<child->rightLink<<endl;
        }
        void InsertRight(ThreadNode<T>* parent, ThreadNode<T>* child){
            child->threadRight = parent->threadRight;
            child->rightLink = parent->rightLink;
            parent->threadRight= false;
            parent->rightLink = child;
            child->threadLeft = true;
            child->leftLink = parent;
            if(!child->threadRight){
                ThreadNode<T>* temp = InOrderSuccessor(child);
                temp->leftLink = child;
            }
            cout<<"[R] parent: "<<parent->data<<"  "<<parent<<" l:"<<parent->leftLink<<" r:"<<parent->rightLink<<endl;
            cout<<"[R] child:   "<<child->data<<"  " <<child<<" l:"<<child->leftLink<<" r:"<<child->rightLink<<endl;
        }
        ThreadNode<T>* InOrderPredesessor(ThreadNode<T>* now) const{
            if(now->threadLeft){
                return now->leftLink;
            }else{
                ThreadNode<T>* temp = now->leftLink;
                while(!temp->threadRight) temp = temp->rightLink;
                return temp;
            }
        }
        ThreadNode<T>* InOrderSuccessor(ThreadNode<T>* now) const{
            if(now->threadRight){
                return now->rightLink;
            }else{
                ThreadNode<T>* x = now->rightLink;
                while(!x->threadLeft){
                    x = x->leftLink;
                }
                return x;
            }
        }

        //중위 순회
    private:
        void treeFromString(const string& str, int& index,ThreadNode<T>* parent,ThreadNode<T>* now,bool isLeft){
            char ch = str[index++];
            if(ch == '('){
                now = new ThreadNode<T>(nullptr,nullptr,true,true);
                if(isLeft) { InsertLeft(parent,now);}
                else { InsertRight(parent,now);}
                treeFromString(str,index,now,now->leftLink,true);
                while(str[index] ==')') index++; 
                now->data = str[index++];
                treeFromString(str,index,now,now->rightLink,false);
            }else if(ch == ')'){
                index++;
                return;
            }else{
                now = new ThreadNode<T>(ch,nullptr,nullptr,true,true);
                now->data = ch;
                if(isLeft) InsertLeft(parent,now);
                else InsertRight(parent,now);
            }
        }
      
        ThreadNode<T>* first;
};


//전위 스레드 이진트리.
