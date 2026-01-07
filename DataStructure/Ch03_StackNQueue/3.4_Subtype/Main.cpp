#include<iostream>
#include"Deque.h"
using namespace std;

int main(){
    Deque<int> d;
    for(int i=0;i<20;i++){
        d.Push_Front(i);
    }
    while(!d.IsEmpty()){
        cout<<d.Rear()<<" ";
        d.Pop_Back();
    }
}