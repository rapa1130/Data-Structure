#include<iostream>
#include"Ch2/BitSparseMatrix.h"
using namespace std;


int main() {
    BitSparseMatrix bsm1(6,6),bsm2(6,6);
    
    bsm1.NewTerm(0,1,15);
    bsm1.NewTerm(0,2,10);
    
    bsm1.PrintBits();
    bsm1.PrintSm();
    
    bsm2.NewTerm(0,1,4);
    bsm2.NewTerm(0,3,22);
    bsm2.NewTerm(0,0,2);

    bsm2.PrintBits();
    bsm2.PrintSm();
    
    cout<<"[계산결과]"<<endl;
    BitSparseMatrix bsmAdd=bsm1+bsm2;
    bsmAdd.PrintBits();
    bsmAdd.PrintSm();
}