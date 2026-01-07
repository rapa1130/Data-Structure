#pragma once
#include<iostream>
using namespace std;

enum Node_Type{Operand, Operator};

class Node{
public:
    Node(const string& str)
        :str(str)
    {
        char ch=str[0];
        switch (ch)
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            type=Node_Type::Operator;
            break;
        default:
            type=Node_Type::Operand;
            break;
        }
    }
    Node_Type type;
    string str;
};