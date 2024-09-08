#include "SparseMatrix.h"
#include<iostream>
using std::copy;
using std::fill;
SparseMatrix::SparseMatrix()
{
}

SparseMatrix::SparseMatrix(int row, int col)
    :rows(row),cols(col),terms(0),capacity(rows * cols)
{
    sm=new MatrixTerm[capacity];
}

SparseMatrix::SparseMatrix(int row, int col, int terms)
    :rows(row),cols(col),terms(terms),capacity(rows * cols)
{
    sm=new MatrixTerm[capacity];
}

SparseMatrix SparseMatrix::Transpose() const
{
    SparseMatrix transposed(cols,rows);
    for(int nowCol=0;nowCol<cols;nowCol++){
        for(int nowTerm=0;nowTerm<terms;nowTerm++){
            if(nowCol==sm[nowTerm].col){
                transposed.NewTerm(nowCol,sm[nowTerm].row,sm[nowTerm].val);
            }
        }
    }
    return transposed;
}

SparseMatrix SparseMatrix::FastTranspose() const
{
    int* start=new int[cols];
    int* size=new int[cols];

    fill(size,size+cols,0);
    for(int i=0;i<terms;i++){
        size[sm[i].col]++;
    }

    start[0]=0;
    for(int i=1;i<cols;i++){
        start[i]=start[i-1]+size[i-1];
    }

    SparseMatrix transposed(cols,rows,terms);
    for(int i=0;i<terms;i++){
        int transStart=start[sm[i].col];
        transposed.sm[transStart].row=sm[i].col;
        transposed.sm[transStart].col=sm[i].row;
        transposed.sm[transStart].val=sm[i].val;
        start[sm[i].col]++;
    }
    delete[] start;
    delete[] size;
    return transposed;
}

SparseMatrix SparseMatrix::Add(const SparseMatrix &b) const
{
    return SparseMatrix();
}

SparseMatrix SparseMatrix::Mul(const SparseMatrix &b) const
{
    return SparseMatrix();
}

void SparseMatrix::NewTerm(int row, int col, int val)
{
    if(terms>=capacity){
        capacity*=2;
        MatrixTerm* temp=new MatrixTerm[capacity];
        copy(sm,sm+terms,temp);
        delete[] sm;
        sm=temp;
    }
    sm[terms++]=MatrixTerm(col,row,val);
}

ostream &operator<<(ostream &os, const SparseMatrix &sm)
{
    int** printMatrix=new int*[sm.rows];
    for(int i=0;i<sm.rows;i++){
        printMatrix[i]=new int[sm.cols]{0};
    }
    for(int i=0;i<sm.terms;i++){
        MatrixTerm& nowTerm=sm.sm[i];
        int col=nowTerm.col;
        int row=nowTerm.row;
        printMatrix[row][col]=nowTerm.val;
    }
    for(int i=0;i<sm.rows;i++){
        for(int j=0;j<sm.cols;j++){
            os<<printMatrix[i][j]<<" ";
        }
        os<<'\n';
    }
    return os;
}

istream &operator>>(istream &is, SparseMatrix &sm)
{
    int row,col,val;
    is>>row>>col>>val;
    sm.NewTerm(row,col,val);
}

MatrixTerm::MatrixTerm(int col, int row, int val) 
    : col(col), row(row), val(val) {}

MatrixTerm::MatrixTerm() :row(0),col(0),val(0) {}
