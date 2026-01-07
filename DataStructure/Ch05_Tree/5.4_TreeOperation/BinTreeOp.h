#pragma once
#include<iostream>
#include<string>
#include<set>
#include<map>   
#include"../../Ch03_StackNQueue/3.2_Stack/Stack.h"
#include"../../Ch03_StackNQueue/3.3_Queue/Queue.h"
using namespace std;

enum Operator{AND,OR,NOT,T,F};

class OpTree;

template<typename T>
class BinaryTree;

template<typename T>
class TreeNode{
    public:
        friend class BinaryTree<T>;
        friend class OpTree;
        friend ostream& operator<<(ostream& is, BinaryTree<T>& right);
        friend istream& operator>>(istream& is, BinaryTree<T>& right);
        TreeNode(TreeNode<T>* leftLink,TreeNode<T>* rightLink)
            :leftLink(leftLink),rightLink(rightLink){}
        TreeNode()
            :leftLink(nullptr),rightLink(nullptr){}
        TreeNode(const T& data, TreeNode<T>* leftLink,TreeNode<T>* rightLink)
            :data(data),leftLink(leftLink),rightLink(rightLink){}
    private:
        T data;
        TreeNode<T>* leftLink;
        TreeNode<T>* rightLink;
};

template<typename T>
class BinaryTree{
    public:
        friend class OpTree;
        BinaryTree():first(nullptr) {}
        friend istream& operator>>(istream& is, BinaryTree<T>& right){
            string expression;
            is >> expression;
            int index=0;
            right.stringToTree(expression,index,right.first);
            return is;
        }
        friend ostream& operator<<(ostream& os, BinaryTree<T>& right){
            os<<"(";
            right.printTree(os,right.first);
            os<<")";
            return os;

        }
        void InOrder() const{
            inOrder(first);
        }
        void PreOrder() const{
            preOrder(first);
        }
        void PostOrder() const{
            postOrder(first);
        }
        void InOrder_iter() const{
            Stack<TreeNode<T>*> s;
            TreeNode<T>* node = first;
            while(true){
                for(;node != nullptr;node = node->leftLink) s.Push(node);
                if(s.isEmpty()) break;
                node = s.Top();
                s.Pop();
                cout<<node->data<<" ";
                node = node->rightLink;
            }
        }
        class Iterator{
            public:
                Iterator(const BinaryTree<T>& tree)
                    :iter(tree.first){}
                T* Next(){
                    for(;iter != nullptr;iter = iter->leftLink) s.Push(iter);
                    if(s.isEmpty()) return nullptr;
                    iter = s.Top();
                    s.Pop();
                    T* ret = &iter->data;
                    iter = iter->rightLink;
                    return ret;
                }
            private:
                TreeNode<T>* iter;
                Stack<TreeNode<T>*> s;
        };
        void LevelOrder() const{
            Queue<TreeNode<T>*> q;
            if(first ==nullptr) return;
            q.Push(first);
            while(!q.IsEmpty()){
                TreeNode<T>* now = q.Front();
                cout<<now->data<<" ";
                q.Pop();
                if(now->leftLink) q.Push(now->leftLink);
                if(now->rightLink) q.Push(now->rightLink);
            }
        }
        void InOrder_iter_noStack() const{
            if(first == nullptr) return;
            TreeNode<T>* lastRight, *p, *q, *r, *r1;
            TreeNode<T>* top;
            p = q = first;

            while(true){
                while(true){
                    //순회 종료 시점 호출은 언제해야할까?
                    if(!p->leftLink && !p->rightLink){
                        cout<<p->data<<" "<<endl;
                        break;
                    }else if(!p->leftLink){
                        r = p->rightLink;
                        p->rightLink = q;
                        q = p;
                        p =p->rightLink;
                    }else{
                        r = p->leftLink;
                        p->leftLink = q;
                        q = p;
                        p = r;
                        
                    }
                }
                
                TreeNode<T>* av = p;

                while(true){
                    if(p == first) return;
                    if(!q->leftLink){
                        r = q->rightLink;
                        q->rightLink = p;
                        p = q;
                        q =r;
                    }
                    else if(!q->rightLink){
                        cout<<q->data<<" "<<endl;
                        r = q->leftLink;
                        q->leftLink = p;
                        p=q;
                        q=r;
                    }
                    else if(q == lastRight){ // -> 오른쪽에서 돌아오는데 2가지 노드일 경우
                        lastRight = top->leftLink;
                        r = top->rightLink;
                        top->leftLink = top->rightLink = nullptr;
                        top = r;
                        r = q->rightLink;
                        q->rightLink = p;
                        p = q;
                        q = r;
                    }
                    else{ // -> 왼쪽에서 돌아오는데 2가지 노드일 경우
                        cout<<q->data<<" "<<endl;
                        av->rightLink = top;
                        av->leftLink = lastRight;
                        top = av;
                        lastRight = q;
                        r = q->leftLink;
                        q->leftLink = p;
                        p = q->rightLink;
                        q->rightLink = r;
                        break;
                    }
                }
            }
            

            
            
        }
        BinaryTree(const BinaryTree& right){
            first = copy(right.first);
        }
        BinaryTree& operator=(const BinaryTree& right){
            if(this == &right){
                return *this;
            }
            deleteAll(first);
            first = copy(right.first);
            return *this;
        }
        bool operator==(const BinaryTree& right) const{
            return equal(first,right.first);
        }
        ~BinaryTree(){
            deleteAll(first);
        }
        int LeafNum() const{
            return getLeafs(first);
        }
        //swapTree
    private:
        int getLeafs(TreeNode<T>* now) const{
            if(now == nullptr) return 0;
            if(now->leftLink == nullptr && now->rightLink == nullptr) return 1;
            int left= getLeafs(now->leftLink);
            int right = getLeafs(now->rightLink);
            cout<<"now:"<<now->data<<"| left : "<<left<<"  right : "<<right<<endl;
            return left+ right;
            // return getLeafs(now->leftLink) + getLeafs(now->rightLink);

        }
        void deleteAll(TreeNode<T>* toDel){
            if(toDel ==nullptr) return;
            deleteAll(toDel->leftLink);
            deleteAll(toDel->rightLink);
            delete toDel;
        }
        bool equal(TreeNode<T>* l, TreeNode<T>* r) const{
            if(l==nullptr && r==nullptr) return true;
            if(l==nullptr && r !=nullptr || l != nullptr && r == nullptr) return false;

            return l->data == r->data && equal(l->leftLink,r->leftLink) && equal(l->rightLink,r->rightLink);
        }
        TreeNode<T>* copy(TreeNode<T>* from){
            if(!from) return nullptr;
            return new TreeNode<T>(from->data,copy(from->leftLink),copy(from->rightLink));
        }
        void inOrder(TreeNode<T>* node) const{
            if(!node) return;
            inOrder(node->leftLink);
            cout<<node->data<<" ";
            inOrder(node->rightLink);
        }
        void preOrder(TreeNode<T>* node) const{
            if(!node) return;
            cout<<node->data<<" ";
            preOrder(node->leftLink);
            preOrder(node->rightLink);
        }
        void postOrder(TreeNode<T>* node) const{
            if(!node) return;
            postOrder(node->leftLink);
            postOrder(node->rightLink);
            cout<<node->data<<" ";
        }
        void printTree(ostream& os, TreeNode<T>* now) const{
            if(now == nullptr) return;
            os<<now->data;
            if(now->leftLink){
                os<<"(";
                printTree(os,now->leftLink);
                if(now->rightLink != nullptr) cout<<",";
                
                printTree(os,now->rightLink);
                os<<")";
            }

        }
        void stringToTree(const string& expression,int& index,TreeNode<T>*& parent){
            index++;
            parent = new TreeNode<T>(expression[index],nullptr,nullptr);
            index++;
            if(expression[index] == ')'){
                index++;
                return;
            }else if(expression[index] == '('){
                stringToTree(expression,index,parent->leftLink);
                if(expression[index] == ','){
                    stringToTree(expression,index,parent->rightLink);
                }
            }
            else if(expression[index] == ','){
                return;
            }else{
                cout<<"%%%%%ERROR%%%%%%"<<endl;
            }
        }
        
        TreeNode<T>* first;
};

class OpTree{
    public:
        OpTree()
        {
            opTree = BinaryTree<pair<Operator,bool>>();
            bintree =BinaryTree<char>();
        }
        friend istream& operator>>(istream& is, OpTree& tree){
            string expression;
            is >> expression;
            int index=0;
            tree.stringToTree(expression,index,tree.bintree.first);
            return is;
        }
        friend ostream& operator<<(ostream& os,const OpTree& tree){
            tree.printOpTree(os,tree.opTree.first);
            return os;
        }
        vector<map<char,bool>> MappingVarTruthCase(){
                set<char> vars = FindVariables();
                vector<vector<int>> tfs = GetTF(vars);

                vector<map<char,bool>> ret;
                for(auto iter_out=tfs.begin();iter_out!=tfs.end();++iter_out){
                    const vector<int>& nowTfs = *iter_out;
                    map<char,bool> nowMap;
                    int index=0;
                    for(auto iter_inner=vars.begin();iter_inner!=vars.end();++iter_inner,++index){
                        nowMap.insert(pair(*iter_inner,nowTfs[index]));
                    }
                    ret.push_back(nowMap);
                }
                return ret;
        }
        vector<vector<int>> GetTF(const set<char>& vars) const{
            vector<int> tfs(vars.size());
            vector<vector<int>> ret;
            fill(tfs.begin(),tfs.end(),false);
            int index=0;
            getTF(ret,tfs,index);
            return ret;
        }
        BinaryTree<char> GetTruthTree(map<char,bool>& nowTF) {
            BinaryTree<char> ret = bintree;
            setTreeTF(ret.first,nowTF);
            return ret;
        }
        OpTree ConvertToOpTree(const BinaryTree<char>& toConvert){
            OpTree ret;
            convertToOptree(ret.opTree.first,toConvert.first);
            return ret;
        }
        bool CaculateOpTree(){
            caculateOpTree(opTree.first);
            return opTree.first->data.second;
        }
        bool IsSatisfying() {
            vector<map<char,bool>> vec= MappingVarTruthCase();
            for(int i=0;i<vec.size();i++){
                BinaryTree<char> binTree= GetTruthTree(vec[i]);
                OpTree nowOptree = ConvertToOpTree(binTree);
                if(nowOptree.CaculateOpTree()) return true;
            }
            return false;
        }
        void PrintTruthTable() {
            vector<map<char,bool>> vec= MappingVarTruthCase();
	
            for(int i=0;i<vec.size();i++){
                BinaryTree<char> binTree= GetTruthTree(vec[i]);
                OpTree nowOptree = ConvertToOpTree(binTree);
                cout<<":"<<nowOptree;
                cout<<nowOptree.CaculateOpTree()<<endl;
            }
        }
    private:
        void caculateOpTree(TreeNode<pair<Operator,bool>>* now) const{
            if(now == nullptr) return;
            caculateOpTree(now->leftLink);
            caculateOpTree(now->rightLink);
            switch (now->data.first)
            {
            case Operator::AND:
                now->data.second=
                now->leftLink->data.second && now->rightLink->data.second;
                break;
            case Operator::OR:
                now->data.second=
                now->leftLink->data.second || now->rightLink->data.second;
                break;
            case Operator::NOT:
                now->data.second = !now->rightLink->data.second;
                break;
            case Operator::T:
                now->data.second =true;
                break;
            case Operator::F:
                now->data.second=false;
                break;
            default:
                cout<<"%%%%%%%ERROR%%%%%% (caculateOpTree)"<<endl;
                break;
            }
        }
        set<char> FindVariables() const{
            set<char> vars;
            findVariables(bintree.first,vars);
            return vars;
        }
        void setTreeTF(TreeNode<char>* now, map<char,bool>& nowTF){
            if(now == nullptr) return;
            switch (now->data)
            {
            case '&':
            case '|':
            case '~':
                break;
            default:
                if(nowTF[now->data]){
                    now->data='T';
                }else{
                    now->data='F';
                }
                break;
            }
            setTreeTF(now->leftLink,nowTF);
            setTreeTF(now->rightLink,nowTF);
        }
        void getTF(vector<vector<int>>& ret, vector<int>& tfs,int nowIndex)const{
            if(nowIndex >= tfs.size()){
                ret.push_back(tfs);
                return;
            }
            tfs[nowIndex]=false;
            getTF(ret,tfs,nowIndex + 1);
            tfs[nowIndex] = true;
            getTF(ret,tfs,nowIndex + 1);
        }
        void findVariables(TreeNode<char>* node,set<char>& vars) const{
            if(node ==nullptr) return;
            switch (node->data){
                case '~':
                case '|':
                case '&':
                    break;
                default:
                    vars.insert(node->data);
                    break;
            }
            findVariables(node->leftLink,vars);

            findVariables(node->rightLink,vars);
        }
        void printOpTree(ostream& os ,TreeNode<pair<Operator,bool>>* now)const{
            if(now == nullptr) return;
            printOpTree(os,now->leftLink);
            os<<OperatorToChar(now->data.first)<<" ";
            printOpTree(os, now->rightLink);
        }
        char OperatorToChar(Operator oper) const{
            switch (oper)
            {
            case Operator::AND:
                return '&';
                break;
            case Operator::OR:
                return '|';
                break;
            case Operator::NOT:
                return '~';
                break;
            case Operator::T:
                return 'T';
                break;
            case Operator::F:
                return 'F';
                break;
            default:
                cout<<"ERROR!!!!!!!!!!"<<endl;
                break;
            }
        }
        Operator charToOperator(char ch)const{
            switch (ch)
            {
            case '&':
                return Operator::AND;
                break;
            case '|':
                return Operator::OR;
                break;
            case '~':
                return Operator::NOT;
                break;
            case 'T':
                return Operator::T;
                break;
            case 'F':
                return Operator::F;
                break;
            default:
                return Operator::F;
                break;
            }
        }
        void stringToTree(const string& expression,int& index, TreeNode<char>*& node){
            char ch = expression[index];
            index++;
            if(ch == '('){
                node = new TreeNode<char>();
                stringToTree(expression,index,node->leftLink);
                node->data = expression[index++];
                stringToTree(expression,index,node->rightLink);
                index++;
            }
            else if(ch == '~'){
                index--;
                return;
            }else{
                node = new TreeNode<char>();
                node->data = ch;
            }
            
        }
        void convertToOptree(TreeNode<pair<Operator,bool>>*& to,TreeNode<char>* from){
            if(!from){
                return;
            }
            Operator oper = charToOperator(from->data);
            to = new TreeNode<pair<Operator,bool>>(pair<Operator,bool>(oper,false),nullptr,nullptr);
            convertToOptree(to->leftLink,from->leftLink);
            convertToOptree(to->rightLink,from->rightLink);
        }
        BinaryTree<pair<Operator,bool>> opTree;
        BinaryTree<char> bintree;
};