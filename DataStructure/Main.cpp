#include<iostream>
#include"Ch2/SparseMatrix.h"
using namespace std;


int main() {
    SparseMatrix sm1(3,3),sm2(3,3);
    sm1.NewTerm(0,0,1);
    sm1.NewTerm(1,0,1);
    sm1.NewTerm(2,0,1);
    
    sm2.NewTerm(0,0,1);
    sm2.NewTerm(0,1,1);
    sm2.NewTerm(0,2,1);

    cout<<sm1<<endl;
    cout<<"곱하기"<<endl;
    cout<<sm2<<endl;
    SparseMatrix multiplied= sm1.Mul2(sm2);
    cout<<multiplied<<endl;

}