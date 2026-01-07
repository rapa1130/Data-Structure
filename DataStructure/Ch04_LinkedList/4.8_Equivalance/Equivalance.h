#pragma once

#include<iostream>
#include<vector>
#include<string>   
using namespace std;


struct E_Node{
    E_Node(int data,E_Node* link) : data(data),link(link) {}
    int data;
    E_Node* link;
    ~E_Node(){
        cout<<"Hello"<<endl;
    }
};

class Equivalance{
    public:
        friend istream& operator>>(istream& is,Equivalance& equ);
        void GetEquivalent(){
            vector<E_Node*> first(n);
            vector<bool> out(n);
            fill(first.begin(),first.end(),nullptr);
            fill(out.begin(),out.end(),false);

            
            for(int equIndex=0 ; equIndex<equTerms.size() ; equIndex++){
                int i=equTerms[equIndex].first;
                int j=equTerms[equIndex].second;
                first[i] = new E_Node(j,first[i]);
                first[j] = new E_Node(i,first[j]);
            }

            for(int i=0;i<n;i++){
                if(!out[i]){
                    cout<<"["<<i;
                    out[i]=true;
                    E_Node* top=nullptr;
                    E_Node* x = first[i];
                    while(true){
                        while(x){
                            if(!out[x->data]){
                                out[x->data] = true;
                                cout<<", "<<x->data;
                                E_Node* y = x->link;
                                x->link = top;
                                top = x;
                                x = x->link;
                            }
                            else{
                                x = x->link;
                            }
                        }
                        if(!top) break;
                        x = first[top->data];
                        top = top->link;
                    }
                    cout<<"] ";
                }
            }                        
            out.~vector();
        }
        void PrintEquTerms()const{
            using std::cout;
            using std::endl;
            for(auto iter=equTerms.begin();iter!=equTerms.end();++iter){
                cout<<iter->first<<","<<iter->second<<" ";
            }
        }
    private:
        int n;
        vector<pair<int,int>> equTerms;
};

istream& operator>>(istream& is,Equivalance& equ)
{
    using std::cout;
    using std::endl;
    int range=INT32_MIN;
    string str = "";
    while(true){
        cin>>str;
        if(str=="F"){
            break;
        }
        int leftIndex = str[0]-'0';
        int rightIndex = str[2]-'0';
        equ.equTerms.push_back(pair<int,int>(leftIndex,rightIndex));
        range=max(max(leftIndex,rightIndex),range);
    }
    equ.n = range;
    return is;
}
