#pragma once
#include"../../Ch04_LinkedList/4.11_GeneralList/GenList.h"
#include<iostream>

using namespace std;

template<typename T>
class GeneralListTree : public GeneralList<T>{
    public:
        friend istream& operator>>(istream& is,GeneralListTree<T>& right){
            string treeStr;
            cin>>treeStr;
            int index=0;
            right.stringToNode(treeStr,index,right.first);
            return is;
        }
        friend ostream& operator<<(ostream& os, GeneralListTree<T>& right){
            cout<<"(";
            right.printTree(os,right.first);
            cout<<")";
            return os;
        }
    private:
        void printTree(ostream& os, GeneralListNode<T>* now) const{
            if(now== nullptr) return;
            if(now->tag == NodeType::ptr){
                cout<<"(";
                printTree(os,now->down);
                cout<<")";
            }
            else if(now->tag == NodeType::no) {
                os<<now->data;
                if(now->next != nullptr && now->next->tag == NodeType::no){
                    os<<",";
                }
            }
            printTree(os,now->next);
        }
        void stringToNode(const string& str, int& index, GeneralListNode<T>* nodePtr){
            ++index;
            char ch = str[index];
            if(ch == ')'){
                return;
            }
            else if(ch =='('){
                nodePtr = nodePtr->next = this->GetNode(NodeType::ptr,nullptr);
                nodePtr->down = this->GetNode(NodeType::ref,nullptr);
                nodePtr->down->ref = 1;
                stringToNode(str,index,nodePtr->down);
                stringToNode(str,index,nodePtr);
            }
            else if( ch == ','){
                stringToNode(str,index,nodePtr);
            }else{
                nodePtr->next = this->GetNode(NodeType::no,nullptr);
                nodePtr = nodePtr->next;
                nodePtr->data = ch;
                stringToNode(str,index,nodePtr);
            }
        }
};