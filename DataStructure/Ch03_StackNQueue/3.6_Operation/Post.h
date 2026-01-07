#pragma once
#include<iostream>
#include"../3.2_Stack/Stack.h"
#include"Expression.h"
using namespace std;


int Operation(const string& leftOp,const string& rightOp,const string& Op){
    char front=Op.front();
    switch (front)
    {
    case '+':
        return stoi(leftOp) + stoi(rightOp);
        break;
    case '-':
        return stoi(leftOp) - stoi(rightOp);
        break;
    case '*':
        return stoi(leftOp) * stoi(rightOp);
        break;
    case '/':
        return stoi(rightOp) / stoi(leftOp);
        break;
    default:
        return INT32_MIN;
        break;
    }
}

string PopStack(Stack<string>& stack){
    string ch=stack.Top();
    stack.Pop();
    return ch;
}

int InOrder(string& expressionStr){
    Expression expression(expressionStr);
    // expression.InOrderToPostfix();
    expression.InOrderToPostfix2();
    Stack<string> stack;

    for(int i=0;i<expression.Size();i++){
        const Node& node = expression.GetElement(i);
        if(node.type == Node_Type::Operand){
            stack.Push(node.str);
        }
        else{
            const string& leftOp = PopStack(stack);
            const string& rightOp = PopStack(stack);
            
            int result = Operation(leftOp,rightOp,node.str);
            stack.Push(to_string(result));
        }
    }
    return stoi(stack.Top());
}


int Postfix(string& expressionStr){
    Expression expression(expressionStr);
    Stack<string> stack;

    for(int i=0;i<expression.Size();i++){
        const Node& node = expression.GetElement(i);
        // cout<<"Operand:"<<node.str<<" Type:"<<node.type<<endl;
        if(node.type == Node_Type::Operand){
            stack.Push(node.str);
        }
        else{
            const string& leftOp = PopStack(stack);
            const string& rightOp = PopStack(stack);
            int result = Operation(leftOp,rightOp,node.str);
            stack.Push(to_string(result));
        }
    }
    return stoi(stack.Top());

}

int Prefix(string& expressionStr){
    Expression expression(expressionStr);
    expression.InOrderToPrefix();
    cout<<endl;
    Stack<string> stack;
    for(int i = expression.Size()-1 ; i>=0 ; i--){
        const Node& node = expression.GetElement(i);
        if(node.type== Node_Type::Operand){
            stack.Push(node.str);
        }else{
            const string& leftOp = PopStack(stack);
            const string& rightOp = PopStack(stack);
            int result = Operation(rightOp,leftOp,node.str);
            stack.Push(to_string(result));
        }
    }
    return stoi(stack.Top());
}