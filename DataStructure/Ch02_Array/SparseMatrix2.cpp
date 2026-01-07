#include"SparseMatrix2.h"

SparseMatrix2 SparseMatrix2::Transpose() const
{
    SparseMatrix2 ret(cols,rows,terms);
    int currentIndex = 0;
    for(int i=0;i<cols;i++){
        for(int j=0;j<terms;j++){
            if(i==arr[j].col){
                ret.arr[currentIndex++]=MatrixTerm(i,arr[j].row,arr[j].element);
            }
        }
    }
    return ret;
}

SparseMatrix2 SparseMatrix2::FastTranspose() const
{
    int* colStart=new int[cols];
    int* colSize=new int[cols];
    
    for(int i=0;i<terms;i++){
        colSize[arr[i].col]++;
    }
    colStart[0]=0;
    for(int i=1;i<cols;i++){
        colStart[i]=colStart[i-1]+ colSize[i-1];
    }
    SparseMatrix2 transposed(cols,rows,terms);
    for(int i=0;i<terms;i++){
        int& nowStart=colStart[arr[i].col];
        transposed.arr[nowStart]=MatrixTerm(arr[i].col,arr[i].row,arr[i].element);
        nowStart++;
    }
    return transposed;
}

SparseMatrix2 SparseMatrix2::operator+(const SparseMatrix2 &right) const
{
    int posA=0;
    int posB=0;
    int posC=0;
    SparseMatrix2 added(rows,cols,0);
    using namespace std;
    while((posA<terms) && (posB<right.terms)){
        const MatrixTerm& termA=arr[posA];
        const MatrixTerm& termB=right.arr[posB];
        if(termA.row>termB.row){
            added.arr[posC]=MatrixTerm(termB.row,termB.col,termB.element);
            posB++;
            posC++;
        }
        else if(termA.row<termB.row){
            added.arr[posC]=MatrixTerm(termA.row,termA.col,termA.element);
            posA++;
            posC++;
        }
        else{
            if(termA.col>termB.col){
                added.arr[posC]=MatrixTerm(termB.row,termB.col,termB.element);
                posB++;
                posC++;
            }
            else if(termA.col<termB.col){
                added.arr[posC]=MatrixTerm(termA.row,termA.col,termA.element);
                posA++;
                posC++;
            }else{
                added.arr[posC]=MatrixTerm(termA.row,termA.col,termA.element+termB.element);
                posA++;
                posB++;
                posC++;
            }
        }
        added.terms++;
    }

    for(;posA<terms;posA++){
        const MatrixTerm& termA=arr[posA];
        added.arr[posC]=MatrixTerm(termA.row,termA.col,termA.element);
        added.terms++;
        posC++;
    }
    for(;posB<right.terms;posB++){
        const MatrixTerm& termB=right.arr[posB];
        added.arr[posC]=MatrixTerm(termB.row,termB.col,termB.element);
        added.terms++;
        posC++;
    }

    return added;
}


SparseMatrix2 SparseMatrix2::operator*(const SparseMatrix2 &right) 
{   
    SparseMatrix2 c(rows,right.cols,0);
    SparseMatrix2 bXpose=right.FastTranspose();
    if(terms==capacity){
        Change1DSize(terms+1);
    }
    bXpose.Change1DSize(bXpose.terms+1);
    arr[terms].row=rows;
    bXpose.arr[bXpose.terms].row=bXpose.rows;
    bXpose.arr[bXpose.terms].col=-1;

    int currRowIndex=0;
    int currRowA=arr[0].row;
    int currRowBegin=0;

    //A<terms
    
    int sum=0;

    while(currRowIndex<terms){
        int currColIndex=0;
        int currColB=bXpose.arr[0].row;
        while(currColIndex<=bXpose.terms){
            if(arr[currRowIndex].row!=currRowA){
                c.StoreSum(currRowA,currColB,sum);
                sum=0;
                currRowIndex=currRowBegin;
                while(bXpose.arr[currColIndex].row==currColB)
                    currColIndex++;
                currColB=bXpose.arr[currColIndex].row;
            }
            else if(bXpose.arr[currColIndex].row!=currColB){
                c.StoreSum(currRowA,currColB,sum);
                sum=0;
                currColB=bXpose.arr[currColIndex].row;
                currRowIndex=currRowBegin;
            }
            else{
                if(arr[currRowIndex].col > bXpose.arr[currColIndex].col){
                    currColIndex++;
                }
                else if(arr[currRowIndex].col < bXpose.arr[currColIndex].col){
                    currRowIndex++;
                }
                else{
                    sum+=arr[currRowIndex].element*bXpose.arr[currColIndex].element;
                    currColIndex++;
                    currRowIndex++;
                }
            }
        }
        while(arr[currRowIndex].row==currRowA) currRowIndex++;
        currRowA=arr[currRowIndex].row;
        currRowBegin=currRowIndex;
    }
    
    return c;
}

void SparseMatrix2::StoreSum(int row, int col, int sum)
{
    if(terms==capacity){
        Change1DSize(2*capacity);
    }
    arr[terms++]=MatrixTerm(row,col,sum);
}

void SparseMatrix2::Change1DSize(int newSize)
{
    MatrixTerm* temp=new MatrixTerm[newSize];
    std::copy(arr,arr+terms,temp);
    delete[] arr;
    arr=temp;
    capacity=newSize;
}

ostream& operator<<(ostream &os, const SparseMatrix2 &sm)
{
    for(int i=0;i<sm.terms;i++){
        const MatrixTerm& term=sm.arr[i];
        os<<"("<<term.row<<","<<term.col<<") : "<<term.element<<std::endl;
    }
    return os;
}
