#pragma once
#include<vector>
#include<string>
#include<map>
#include"Node.h"
#include"../3.2_Stack/Stack.h"
using namespace std;

vector<string> Split(const string& str,const string& sep){
    vector<string> ret;
    int index=0;
    while(true){
        int finded=str.find_first_of(sep,index);
        ret.push_back(str.substr( index,(finded-index)));
        if(finded==-1) break;
        index=finded + 1;
    }
    return ret;
}

bool IsOperator(const string& str){
    char front=str.front();
    switch (front)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        return true;
        break;
    default:
        return false;
        break;
    }
}



class Expression{
public:
    void InOrderToPrefix(){
        vector<Node> newOperands; 
        Stack<string> opStack;
        opStack.Push("#");
        icp['(']=0;
        isp['(']=8;

        icp[')']=0;
        isp[')']=8;

        for(int i=operands.size()-1;i>=0;i--){
            if(operands[i].type==Node_Type::Operand) newOperands.push_back(operands[i]);
            else if(operands[i].str[0] == '('){
                for(;opStack.Top()[0] != ')';opStack.Pop()) newOperands.push_back(opStack.Top());
                opStack.Pop();
            }
            else{
                for(;isp[opStack.Top()[0]] <= icp[operands[i].str[0]];opStack.Pop()){
                    newOperands.push_back(opStack.Top());
                }
                opStack.Push(operands[i].str);
            }
        }
        for(;opStack.Top()[0]!='#';opStack.Pop()) newOperands.push_back(opStack.Top());
        reverse(newOperands.begin(),newOperands.end());
        operands=newOperands;
    }
    void InOrderToPostfix2(){
        Stack<string> opStack;
        vector<Node> newOperands;

        opStack.Push("#");
        for(int i=0;i<operands.size();i++){
            if(operands[i].type == Node_Type::Operand) newOperands.push_back(operands[i].str);
            else if(operands[i].str[0]==')'){
                for( ; opStack.Top()[0] != '(' ; opStack.Pop()) newOperands.push_back(opStack.Top());
                opStack.Pop();
            }
            else{
                for(;icp[operands[i].str[0]] >=isp[opStack.Top()[0]] ;opStack.Pop()) newOperands.push_back(opStack.Top());
                opStack.Push(operands[i].str);
            }
        }
        for(;opStack.Top()!=string("#");opStack.Pop()){
            newOperands.push_back(opStack.Top());
        }
        
        operands=newOperands;
    }
    void InOrderToPostfix(){
        Stack<string> opStack;
        vector<Node> newOperands;
        for(int i=0;i<operands.size();i++){
            if(operands[i].type == Node_Type::Operand){
                newOperands.push_back(operands[i]);
            }else{
                if(opStack.isEmpty()){
                    opStack.Push(operands[i].str);
                }
                else if(operands[i].str[0]==')'){
                    while(opStack.Top()[0]!='('){ //검증 필요
                        newOperands.push_back(opStack.Top());
                        opStack.Pop();
                    }
                    opStack.Pop();
                }
                else{
                    char topOp=opStack.Top()[0];
                    char exOp=operands[i].str[0];
                    if(isp[topOp]<=icp[exOp]){
                        newOperands.push_back(Node(to_string(topOp)));
                        opStack.Pop();
                        opStack.Push(operands[i].str);
                    }else{
                        //newOperands.push_back(operands[i])
                        opStack.Push(operands[i].str);
                    }
                }
            }
        }
        newOperands.push_back(opStack.Top());
        for(int i=0;i<newOperands.size();i++){
            cout<<newOperands[i].str<<" ";
        }
        cout<<endl;
        operands=newOperands;
    }
    Expression(const string& str){
        vector<string> splited=Split(str," ");
        for(int i=0;i<splited.size();i++){
            operands.push_back(Node(splited[i]));
        }
        icp['+']=isp['+']=3;
        icp['-']=isp['-']=3;
        icp['*']=isp['*']=2;
        icp['/']=isp['/']=2;

        icp['(']=0;
        isp['(']=8;

        icp[')']=0;
        isp[')']=0;

        isp['#']=8;
    }
    Node GetElement(int index)const{
        return operands[index];
    }
    int Size() const{
        return operands.size();
    }
    map<char,int> icp;
    map<char,int> isp;
private:
    vector<Node> operands;
   
};