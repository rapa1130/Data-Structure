#include<iostream>
#include"Ch2/SparseMatrix.h"
using namespace std;


int main() {
    SparseMatrix sm(3,4);
    sm.NewTerm(2,1,99);
    sm.NewTerm(0,1,7);
    cout<<sm;
    sm=sm.FastTranspose();
    cout<<sm;
}