#include<iostream>
using std::ostream;

class BitSparseMatrix{
public:
    BitSparseMatrix();
    BitSparseMatrix(int rows,int cols);
    BitSparseMatrix(const BitSparseMatrix& right);
    BitSparseMatrix operator+(const BitSparseMatrix& right) const;
    void NewTerm(int row,int col,int val);
    void NewTermDirect(int row,int col,int term,int val);
    void PrintBits()const;
    void PrintSm()const;

private:
    int capacity;
    int bits[32]={};
    int* sm;
    int cols;
    int rows;
    int terms;
    
    friend ostream& operator<<(ostream& os,const BitSparseMatrix& sm);
};

ostream& operator<<(ostream& os,const BitSparseMatrix& sm);