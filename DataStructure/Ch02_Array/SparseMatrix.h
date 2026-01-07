#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include<iostream>

using std::istream;
using std::ostream;

class SparseMatrix;

class MatrixTerm{
public:
    MatrixTerm(int col,int row,int val);
    MatrixTerm();
private:
    friend SparseMatrix;
    friend ostream& operator<<(ostream& os,const SparseMatrix& sm);
    friend istream& operator>>(istream& is,SparseMatrix& sm); 
    int col;
    int row;
    int val;
};

class SparseMatrix{
public:
    SparseMatrix();
    SparseMatrix(int row,int col);
    SparseMatrix(int row,int col,int terms);
    SparseMatrix Transpose() const;
    SparseMatrix FastTranspose() const;
    SparseMatrix Add(const SparseMatrix& b) const;
    SparseMatrix Mul(const SparseMatrix& b) ;
    SparseMatrix Mul2(SparseMatrix& b) ;
    friend ostream& operator<<(ostream& os,const SparseMatrix& sm);
    friend istream& operator>>(istream& is,SparseMatrix& sm);
    void NewTerm(int row,int col,int val);
private:
public:
    void StoreSum(int sum,int row,int col);
    void ChangeSizeID(const int newSize);
    int cols;
    int rows;
    int terms;
    int capacity;
    MatrixTerm* sm;
};

ostream& operator<<(ostream& os,const SparseMatrix& sm);
istream& operator>>(istream& is,SparseMatrix& sm);


#endif