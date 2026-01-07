#include"String.h"
#include<iostream>
#include<algorithm>
String::String()
    :capacity(10),size(0)
{
    str=new char[capacity];
}

String::String(const char *arr)
    :String()
{
    
    int index=0;
    for(;arr[index]!='\0';index++){
        push_back(arr[index]);
    }
    size=index;
}

int String::Length() const
{
    return size;
}

char &String::operator[](int index)
{
    return str[index];
}

char String::operator[](int index) const
{
    return str[index];
}

bool String::operator==(const String &right)
{
    if(right.size!=size){
        return false;
    }
    for(int i=0;i<size;i++){
        if(str[i]!=right[i]){
            return false;
        }
    }
    return true;
}

bool String::operator!=(const String &right)
{
    return !((*this)==right);
}

int String::Find(const String &pat)
{
    int start;
    for(start=0;start<size-pat.size+1;start++){
        int j=0;
        for(;j<pat.size && str[start+j]==pat[j];j++);
        if(j==pat.size){
            return j;
        }
    }
    return -1;
}

int String::kmp(String pat)
{
    pat.fail_func();
    int lengthP=pat.size;
    int lengthS=size;
    int posP=0,posS=0;
    while(posP<lengthP && posS < lengthS){
        if(str[posS]==pat.str[posP]){
            posS++;
            posP++;
        }
        else{
            if(posP==0)posS++;
            else posP=pat.f[posP-1]+1;
        }
    }
    if(lengthP == posP) return posS-lengthP;
    else return -1;
}

void String::fail_func()
{
    f=new int[size];
    f[0]=-1;
    for(int j=1;j<size;j++){
        int i=f[j-1];
        while(str[i+1]!=str[j] && i>=0)i=f[i];
        if(str[i+1]==str[j])f[j]=i+1;
        else f[j]=-1;
    }
}

void String::Print_Fail()
{
    for(int i=0;i<size;i++){
        std::cout<<f[i]<<" ";
    }
    std::cout<<std::endl;
}

void String::push_back(const char &val)
{
    if(capacity==size){
        capacity*=2;
        char* temp=new char[capacity];
        std::copy(str,str+size,temp);
        delete[] str;
        str=temp;
    }
    str[size++]=val;
}
