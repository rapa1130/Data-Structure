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

SparseMatrix SparseMatrix::Mul(const SparseMatrix &b)
{
    SparseMatrix multiplied(rows,b.cols);
    SparseMatrix bTransposed=b.FastTranspose();
    using std::cout;
    using std::endl;
    
    if(terms == capacity){ ChangeSizeID(terms+1);}
    bTransposed.ChangeSizeID(bTransposed.terms+1);
    sm[terms].row=rows;
    bTransposed.sm[bTransposed.terms].row=b.cols;
    bTransposed.sm[bTransposed.terms].col=-1;

    int currRowIndex = 0;
    int currRowBegin=0;
    int currRowA = sm[0].row;
    int sum=0;
   
    while(currRowIndex < terms){
        int currColIndex=0;
        int currColB=bTransposed.sm[0].row;
        while(currColIndex <= b.terms){
            if(currRowA != sm[currRowIndex].row){
                multiplied.StoreSum(sum,currRowA,currColB);
                sum=0;
                currRowIndex=currRowBegin;
                while(currColB == bTransposed.sm[currColIndex].row){
                    currColIndex++;
                }
                currColB=bTransposed.sm[currColIndex].row;
            }
            else if(currColB != bTransposed.sm[currColIndex].row){
                multiplied.StoreSum(sum,currRowA,currColB);
                sum=0;
                currRowIndex=currRowBegin;
                currColB=bTransposed.sm[currColIndex].row;
            }
            else if(sm[currRowIndex].col < bTransposed.sm[currColIndex].col){
                currRowIndex++;
            }
            else if(sm[currRowIndex].col > bTransposed.sm[currColIndex].col){
                currColIndex++;
            }
            else{ //sm[currRowIndex].col == bTransposed.sm[currColIndex].col
                sum+=sm[currRowIndex].val * bTransposed.sm[currColIndex].val;
                currRowIndex++; currColIndex++;
            }
        }
        while(currRowA==sm[currRowIndex].row){
            currRowIndex++;
        }
        currRowBegin = currRowIndex;
        currRowA = sm[currRowIndex].row;
    }
    return multiplied;
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

void SparseMatrix::StoreSum(int sum, int row, int col)
{
    if(sum!=0){
        if(terms>=capacity){
            ChangeSizeID(capacity * 2);
        }
        sm[terms++] = MatrixTerm(col,row,sum);
    }
}

void SparseMatrix::ChangeSizeID(const int newSize)
{
    if(terms>newSize){
        throw "New size must be <= number of terms";
    }
    MatrixTerm* temp=new MatrixTerm[newSize];
    copy(sm,sm+terms,temp);
    delete[] sm;
    sm=temp;
    capacity=newSize;
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
