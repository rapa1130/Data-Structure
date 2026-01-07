#pragma once
#include<iostream>
using namespace std;

enum NodeType {ref,ptr, no};

template<typename T>
class GeneralList;

template<typename T>
class GeneralListTree;

//GenListNode
template<typename T>
class GeneralListNode{
    public:
    friend class GeneralList<T>;
    friend class GeneralListTree<T>;
        GeneralListNode(NodeType tag,GeneralListNode* next) : next(next), tag(tag){}
    private:
        GeneralListNode* next;
        NodeType tag;
        union{
            GeneralListNode* down;
            T data;
            int ref;
        };
};

template<typename T>
class GeneralList{
    public:
        GeneralList()
        {
            // first = new GeneralListNode<T>(NodeType::ref, nullptr);
            first = GetNode(NodeType::ref,nullptr);
            first->ref = 1;
        }
        int GetDepth() const{
            return _getDepth(first);
        }
        GeneralList<T>& operator=(const GeneralList<T>& right) {
            first = Copy(right.first);
            return *this;
        }
        friend ostream& operator<<(ostream& os,const GeneralList<T>& GList){
            GList.PrintList(os,GList.first);
            return os;
        }
        friend istream& operator>>(istream& is,GeneralList<T>& GList){
            string expression;
            cin >> expression;
            int nowPos=0;
            GList.StringToGL(expression, nowPos, GList.first);
            return is;
        }
        bool operator==(const GeneralList<T>& right) const{
            return Equal(first,right.first);
        }
        GeneralListNode<T>* GetNode(NodeType tag = NodeType::ref,GeneralListNode<T>* next = nullptr){
            if(av){
                GeneralListNode<T>* ret = av;
                // cout<<"av->next:"<<av->next<<endl;
                av = av->next;
                ret->tag = tag;
                ret->next = next;
                return ret;
            }else{
                // cout<<"new!!"<<endl;
                return new GeneralListNode<T>(tag,next);
            }
        }
        ~GeneralList(){
            cout<<"Desutructor is Called!"<<endl;
            FreeList(first);
            PrintAV();
        }
        void PrintAV() const{
            cout<<"av:";
            for(GeneralListNode<T>* now=av;now!=nullptr;now=now->next){
                cout<<"(";
                if(now->tag ==NodeType::ref) cout<<"ref|";
                else if(now->tag == NodeType::ptr) cout<<"ptr|";
                else cout<<"no|"<<now->data;
                cout<<") ";
            }
            cout<<endl;
        }
    protected
    :
        GeneralListNode<T>* Copy(GeneralListNode<T>* cp){
            GeneralListNode<T>* ret = nullptr;
            if(cp){
                ret = GetNode(cp->tag, nullptr);
                if(cp->tag == NodeType::ptr){
                    ret->down = Copy(cp->down);
                }else if(cp->tag == NodeType::no){
                    ret->data = cp->data;
                }else{
                    ret->ref = 1;
                }
                ret->next = Copy(cp->next);
            }
            return ret;
        }
        bool Equal(GeneralListNode<T>* a,GeneralListNode<T>* b) const{
            if(a==nullptr && b ==nullptr){
                return true;
            }
            if(a->tag != b->tag) return false;

            if(a->tag == NodeType::ptr) return Equal(a->next,b->next) && Equal(a->down,b->down);
            else if(a->tag == NodeType::no) return Equal(a->next,b->next) && a->data == b->data;
            else return Equal(a->next,b->next);
        }
        int _getDepth(GeneralListNode<T>* ptr)const{
            if(ptr->next == nullptr){
                return 0;
            }
            int depth = 0;
            for(;ptr!=nullptr;ptr=ptr->next){
                if(ptr->tag == NodeType::ptr){
                    depth = max(_getDepth(ptr->down),depth);
                }
            }
            return depth + 1;
        }
        void StringToGL(const string& str, int& nowPos,GeneralListNode<T>* current){
            nowPos++;
            //first 연결 필요
            
            for(;nowPos<str.size();nowPos++){
                char ch = str[nowPos];
                if(ch == ')'){
                    return;
                }
                else if(ch == ','){
                    continue;
                }else if(ch=='('){
                    // current = current->next = new GeneralListNode<T>(NodeType::ptr,nullptr); 
                    current = current->next = GetNode(NodeType::ptr,nullptr); 
                    // current->down= new GeneralListNode<T>(NodeType::ref,nullptr);
                    current->down= GetNode(NodeType::ref,nullptr);
                    current->down->ref = 1;
                    StringToGL(str,nowPos,current->down);
                }else{
                    // current = current->next = new GeneralListNode<T>(NodeType::no,nullptr);
                    current = current->next = GetNode(NodeType::no,nullptr);
                    current->data = ch;
                }
            }
        }
        void PrintList(ostream& os, GeneralListNode<T>* toPrint) const{
            os<<"(";
            for(;toPrint!=nullptr; toPrint = toPrint->next){
                if(toPrint->tag == NodeType::ref){
                    continue;
                }else if(toPrint->tag == NodeType::ptr){
                    PrintList(os,toPrint->down);
                }else{
                    os<<toPrint->data;
                    
                }
                if(toPrint->next != nullptr){   
                    os<<",";
                }
            }
            os<<")";
        }
        void FreeList(GeneralListNode<T>* toFree){
            toFree->ref--;
            if(toFree->ref ==0){
                GeneralListNode<T>* deleteStart = toFree;
                while(toFree->next !=nullptr){
                    toFree = toFree->next;
                    if(toFree->tag == NodeType::ptr){
                        FreeList(toFree->down);
                    }
                }   
                toFree->next = av;
                av = deleteStart;
            }
        }
        GeneralListNode<T>* first;
        static GeneralListNode<T>* av;
};

template<typename T>
GeneralListNode<T>* GeneralList<T>::av = nullptr;

