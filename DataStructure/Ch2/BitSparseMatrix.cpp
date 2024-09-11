#include "BitSparseMatrix.h"
using std::fill;
using std::copy;

BitSparseMatrix::BitSparseMatrix()
{
}

BitSparseMatrix::BitSparseMatrix(int rows, int cols)
    :rows(rows),cols(cols),terms(0),capacity(1)
{
    fill(bits,bits+32,0);
    sm=new int[capacity];
}

BitSparseMatrix::BitSparseMatrix(const BitSparseMatrix &right)
    :rows(right.rows),cols(right.cols),terms(right.terms),capacity(right.capacity)
{
    copy(right.bits,right.bits+32,bits);
    sm=new int[right.capacity];
    copy(right.sm,right.sm+terms,sm);
}



BitSparseMatrix BitSparseMatrix::operator+(const BitSparseMatrix &b) const
{
    BitSparseMatrix added(rows,cols);
    int posA=0,posB=0,posC=0;
    for(int i=0;i<rows;i++){
        int nowRowA=bits[i];
        int nowRowB=b.bits[i];
        if(nowRowA==0 && nowRowB==0)continue;
        for(int j=0;j<cols;j++){
            if((nowRowA&0x8000) !=0 && (nowRowB&0x8000) !=0){
                added.NewTermDirect(i,j,added.terms,sm[posA]+b.sm[posB]);
                posA++; posB++;
            }else if((nowRowA&0x8000) ==0 && (nowRowB&0x8000) !=0){
                added.NewTermDirect(i,j,added.terms,b.sm[posB]);
                posB++;
            }else if((nowRowA&0x8000) !=0 && (nowRowB&0x8000) ==0){
                added.NewTermDirect(i,j,added.terms,sm[posA]);
                posA++;
            }
            nowRowA<<=1; nowRowB<<=1;
        }
    }
    return added;
}

int oneCountInBit(int bitStr,int digits){
    int count=0;
    while(digits!=0){
        if((bitStr & 0x8000)==1){
            count++;
        }
        bitStr<<=1;
    }
    return count;
}


void BitSparseMatrix::NewTerm(int row, int col, int val)
{
    if(terms>=capacity){
        capacity*=2;
        int* temp=new int[capacity];
        copy(sm,sm+terms,temp);
        delete[] sm;
        sm=temp;
    }
    int totalCountOfOneBit=0;
    bool isEnd=false;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            if(i==row && j==col){
                isEnd=true;
                break;
            }
            if((bits[i]&(0x8000>>j))!=0){
                totalCountOfOneBit++;
            }
        }
        if(isEnd){
            break;
        }
    }
    std::cout<<totalCountOfOneBit<<std::endl;
    for(int i=terms;i>totalCountOfOneBit;i--){
        sm[i]=sm[i-1];
    }
    sm[totalCountOfOneBit]=val;
    bits[row]=bits[row]| ((0x8000)>>col);
    terms++;
}

void BitSparseMatrix::NewTermDirect(int row, int col,int term, int val)
{
    if(terms>=capacity){
        capacity*=2;
        int* temp=new int[capacity];
        copy(sm,sm+terms,temp);
        delete[] sm;
        sm=temp;
    }
    sm[term]=val;
    bits[row]=bits[row]| ((0x8000)>>col);
    terms++;
}

void BitSparseMatrix::PrintBits() const
{
    for(int i=0;i<rows;i++){
        int nowRow=bits[i];
        for(int j=0;j<cols;j++){
            if((nowRow&(0x8000>>j))!=0){
                std::cout<<1<<" ";
            }
            else{
                std::cout<<0<<" ";
            }
        }
        std::cout<<std::endl;
    }
}

void BitSparseMatrix::PrintSm() const
{
    std::cout<<"[ "; 
    for(int i=0;i<terms;i++){
        std::cout<<sm[i]<<" ";
    }
     std::cout<<"]"; 
    std::cout<<std::endl;
}

ostream &operator<<(ostream &os, const BitSparseMatrix &sm)
{
}
