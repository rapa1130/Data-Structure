#ifndef SPARSEM_MATRIX_2_H
#define SPARSEM_MATRIX_2_H

#include<iostream>
using std::ostream;

struct MatrixTerm{
    int row;
    int col;
    int element;
    MatrixTerm(int row,int col,int element)
    :row(row),col(col),element(element){}
    MatrixTerm()
    :row(-1),col(-1){}
};

class SparseMatrix2{
public:
    SparseMatrix2()
    :rows(0),cols(0),terms(0),capacity(1)
    {
        arr=new MatrixTerm[capacity];
    }
    SparseMatrix2(int rows,int cols):rows(rows),cols(cols),terms(0),capacity(1){
        arr=new MatrixTerm[capacity];
    }
    SparseMatrix2(int rows,int cols,int terms):rows(rows),cols(cols),terms(terms),capacity(terms+10){
        arr=new MatrixTerm[capacity];
    }
    SparseMatrix2 Transpose() const;
    SparseMatrix2 FastTranspose() const;
    SparseMatrix2 operator+(const SparseMatrix2& right) const;
    SparseMatrix2 operator*(const SparseMatrix2& right) ;    
    friend ostream& operator<<(ostream& os,const SparseMatrix2& sm);
    void StoreSum(int row,int col,int sum);
private:
    int rows;
    int cols;
    int terms;
    int capacity;
    MatrixTerm* arr;

    
    void Change1DSize(int newSize);
};

//ostream& operator<<(ostream& os,const SparseMatrix2& sm);
#endif