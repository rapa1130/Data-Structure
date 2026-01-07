#pragma once
#include<iostream>
using namespace std;

template<typename K, typename E>
class BST;

template<typename K,typename E>
class BST_Node{
    public:
        friend class BST<K,E>;
        BST_Node()
            :left(nullptr),right(nullptr){}
        BST_Node(const pair<K,E>& data,BST_Node<K,E>* left,BST_Node<K,E>* right)
            :data(data),left(left),right(right) {}
        BST_Node(const pair<K,E>& data)
            :data(data),left(nullptr),right(nullptr) {}
    private:
        pair<K,E> data;
        BST_Node<K,E>* left;
        BST_Node<K,E>* right;
};

template<typename K,typename E>
class BST{
    public:
        BST():root(nullptr){}

        void Insert(const pair<K,E>& thePair){
            if(!root) root = new BST_Node<K,E>(thePair);
            
            BST_Node<K,E>* p;
            for(BST_Node<K,E>* now = root; now != nullptr ;){
                p = now;
                if(thePair.first < now->data.first) now = now->left;
                else if(thePair.first > now->data.first) now = now->right;
                else{
                    now->data.second = thePair.second;
                    return;
                }
            }
            if(p->data.first > thePair.first){
                p->left = new BST_Node<K,E>(thePair);
            }else{
                p->right = new BST_Node<K,E>(thePair);
            }

        }

        friend ostream& operator<<(ostream& os,const BST<K,E>& bst){
            bst.printTree(os,bst.root);
            return os;
        }

        pair<K,E>* Get(const K& key) const{
            // return get(key,root);
            for(BST_Node<K,E>* now = root;now!=nullptr;){
                if(now->data.first < key){
                    now = now->right;
                }else if(now->data.first > key){
                    now = now->right;
                }else{
                    return &now->data;
                }
            }
            return nullptr;
        }

        void Delete(const K& key){
            if(!root) return;
            BST_Node<K,E> *p,* pp = nullptr;
            bool isLeft;
            for( p = root ;p != nullptr;){
                if(p->data.first > key) {
                    pp = p;
                    p = p->left;
                    isLeft = true;
                }
                else if(p->data.first < key) {
                    pp = p;
                    p = p->right;
                    isLeft=false;
                }
                else{
                    if(!pp){
                        
                    }

                    break;
                }
            }
            if(p==pp && !p->left && !p->right){
                delete p;
                root = nullptr;
                return;
            }
            if(!p->left || !p->right){
                if(!pp){
                    root = p->left ? p->left : p->right;
                }else{
                    (isLeft ? pp->left : pp->right) = (p->left ? p->left : p->right);
                }
                delete p;
            }
            else{ 
                BST_Node<K,E>* toSwap = p->left,* toSwapP = p;
                while(toSwap->right !=nullptr) {
                    toSwapP =toSwap;
                    toSwap = toSwap->right;
                }
                p->data = toSwap->data;
                if(toSwapP != p) toSwapP->right= toSwap->left;
                else toSwapP->left = toSwap->left;
                delete toSwap;
            }
            
        }

        void ThreeWayJoin(BST<K,E>& small, const pair<K,E>& mid, BST<K,E> & big){
            root = new BST_Node<K,E>(mid,small.root,big.root);
            small.root = big.root = nullptr;
        }

        void TwoWayJoin(BST<K,E>& small,BST<K,E>& big){
            if(small.root == nullptr){
                
                root = big.root;
                big.root = nullptr;
                return;
            }
            if(big.root == nullptr){
                root = small.root;
                small.root = nullptr;
                return;
            }

            BST_Node<K,E>* p ,* pp;
            pp = p = small.root;
            while(p->right != nullptr){
                pp = p;
                p = p->right;
            }
            
            root = new BST_Node<K,E>(p->data,small.root,big.root);

            if(p != small.root) pp->right = p->left;
            else root->left = p->left;

            small.root = big.root = nullptr;
            
            delete p;

        }

        void Split(const K& key,BST<K,E>& small,pair<K,E>* mid,BST<K,E>& big){
            BST_Node<K,E> *sHead = new BST_Node<K,E>();
            BST_Node<K,E> *s =sHead;
            BST_Node<K,E> *bHead = new BST_Node<K,E>();
            BST_Node<K,E> *b = bHead;
            BST_Node<K,E> *current = root;
            while(current){
                if(current->data.first < key){
                    s = s->right = current;
                    current = current->right;
                }else if(current->data.first > key){
                    b = b->left = current;
                    current = current->left;
                }else{
                    mid->first = current->data.first;
                    mid->second = current->data.second;
                    s->right = current->left;
                    b->left = current->right;
                    small.root = sHead->right;
                    big.root = bHead->left;

                    delete current;
                    delete sHead;
                    delete bHead;
                    root = nullptr;
                    return;
                }
            }
            small.root = sHead->right;
            big.root = bHead->left;
            
            delete sHead;
            delete bHead;
            root = nullptr;
        }

    private:
        pair<K,E>* get(const K& key,BST_Node<K,E>* now) const{
            if(now == nullptr) return nullptr;
            if(now->data.first > key){
                return get(key,now->left);
            }
            else if(now->data.first < key){
                return get(key,now->right);
            }else{
                return &now->data;
            }
        }
        void printTree(ostream& os,BST_Node<K,E>* now) const{
            if(now == nullptr) return;
            os<<"["<<now->data.first<<","<<now->data.second<<"] ";
            printTree(os,now->left);
            printTree(os,now->right);
        }
        BST_Node<K,E>* root;
};