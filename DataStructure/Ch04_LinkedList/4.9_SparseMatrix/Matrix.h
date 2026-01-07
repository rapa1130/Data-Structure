#pragma once
#include<iostream>
using namespace std;

class MatrixNode;
class Matrix;


struct Triple{
    int row, col, val;
    Triple(int row,int col,int val) : row(row),col(col),val(val) {}
    Triple(){}
};


class MatrixNode{
    public:
        friend class Matrix;
        friend istream& operator>>(istream& is,Matrix& matrix);
        friend ostream& operator<<(ostream& os, const Matrix& matrix);
        MatrixNode(bool b,Triple* triple){
            head=b;
            if(head){ next = right = down = this; }
            else{
                this->triple = *triple;
            }
        }
        bool operator>(const MatrixNode& b) const{
            if(triple.row == b.triple.row){
                return triple.col > b.triple.col;
            }else{
                return triple.row > b.triple.row;
            }
        }
        bool operator<(const MatrixNode& b) const{
             if(triple.row == b.triple.row){
                return triple.col < b.triple.col;
            }else{
                return triple.row < b.triple.row;
            }
        }
        bool operator==(const MatrixNode& b) const{
            return triple.row == b.triple.row && triple.col == b.triple.col;
        }
    private:
        bool head;
        MatrixNode* right;
        MatrixNode* down;
        union
        {
            Triple triple;
            MatrixNode* next;
        };
};


class Matrix{
    //입력 함수
    public:
        friend istream& operator>>(istream& is,Matrix& matrix);
        friend ostream& operator<<(ostream&, const Matrix& matrix);
        Matrix operator+(const Matrix& right) const;
        MatrixNode* GetNode(bool b,Triple* s){
            if(av){
                MatrixNode* node = av;
                av=av->right;
                node->head=b;
                node->triple=*s;
                return node;
            }else{
                return new MatrixNode(b,s);
            }
        }
        ~Matrix(){
            if(!headerNode) return;
            MatrixNode* x = headerNode->right;
            headerNode->right = av;
            av = headerNode;
            while(x != headerNode){
                MatrixNode* y = x->right;
                x->right = av;
                av = y;
                x = x->next;
            }
            headerNode = nullptr;                     
        }
    private:
        static MatrixNode* av;
        MatrixNode* headerNode;

};

Matrix Matrix::operator+(const Matrix& b) const{
    //matrix both are same row and col.
    
    Matrix c;
    int row = headerNode->triple.row;
    int col = headerNode->triple.col;
    Triple h(row,col,0);
    c.headerNode = c.GetNode(false,&h);
    //added.headerNode->next
    int p = max(row,col);
    MatrixNode** cHead= new MatrixNode*[p];
    for(int i=0;i<p;i++){
        cHead[i]->next =
        cHead[i]->down = 
        cHead[i]->right=
        cHead[i] = c.GetNode(true,nullptr);
    }
    
    MatrixNode* ahPtr = headerNode->right;
    MatrixNode* bhPtr = b.headerNode->right;
    MatrixNode* aPtr = ahPtr->right;
    MatrixNode* bPtr = bhPtr->right;

    int currentRow = 0;
    MatrixNode* cPtr = cHead[0];

    //루프 연결 처리 필요(down, right 모두)
    int newRow;
    MatrixNode* newNode;
    while(ahPtr != headerNode || bhPtr != b.headerNode){
        if(ahPtr == aPtr){
            ahPtr = ahPtr->next;
            aPtr = ahPtr->right;
            continue;
        }
        if(bhPtr == bPtr){
            bhPtr = bhPtr->next;
            bPtr = bhPtr->right;
            continue;
        }
        if(ahPtr == headerNode || *aPtr > *bPtr){
            newNode = c.GetNode(false,&(bPtr->triple));
            newRow = bPtr->triple.row;
            bPtr = bPtr->right; 
        }else if(bhPtr == b.headerNode || *aPtr < *bPtr){
            newNode = c.GetNode(false,&(aPtr->triple));
            newRow = aPtr->triple.row;
            aPtr = aPtr->right;
        }else{
            Triple t;
            t.row = aPtr->triple.row;
            t.col = aPtr->triple.col;
            t.val = aPtr->triple.val + bPtr->triple.val;
            newNode = c.GetNode(false,&t);
            newRow = aPtr->triple.row;
            aPtr = aPtr->right;
            bPtr = bPtr->right; 
        }
        if(currentRow != newRow){
            cPtr->right = cHead[currentRow];
            currentRow = newRow;
            cPtr = cHead[currentRow];
        }
        cPtr = cPtr->right = newNode;
        cHead[newRow]->next = cHead[newRow]->next->down = newNode;
        
        c.headerNode->triple.val++;
    }
    cPtr->right = cHead[currentRow];
    for(int i=0;i<p;i++){
        cHead[i]->next->down = cHead[i];
    }
    for(int i=0;i<p-1;i++){
        cHead[i]->next = cHead[i+1];
    }
    cHead[p-1]->next = c.headerNode;
    c.headerNode->right = cHead[0];
    delete[] cHead;
    return c;
}

ostream& operator<<(ostream& os, const Matrix& matrix){
    cout<<"Matrix____"<<endl;
    int row = matrix.headerNode->triple.row;
    int col = matrix.headerNode->triple.col;
    cout<<"row:"<<row<<" col:"<<col<<" val:"<<matrix.headerNode->triple.val<<endl;
    int** toPrint=new int*[row];
    for(int i=0;i<row;i++){
        toPrint[i]=new int[col];
        fill_n(toPrint[i],col,0);
    }
    MatrixNode* nowRow = matrix.headerNode->right;
    
    while(nowRow != matrix.headerNode){
        for(MatrixNode* now = nowRow->right;now !=nowRow;now=now->right){
            toPrint[now->triple.row][now->triple.col] = now->triple.val;
        }
        nowRow=nowRow->next;
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<toPrint[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"___________"<<endl;
    return os;
}

istream& operator>>(istream& is,Matrix& matrix){
    Triple s;
    cin>>s.row>>s.col>>s.val;
    int p = max(s.row,s.col);
    matrix.headerNode = matrix.GetNode(false, &s); //Get Node
    if(p==0){
        matrix.headerNode->right = matrix.headerNode;
        return is;        
    }
    
    MatrixNode** head = new MatrixNode*[p];
    for(int i=0; i < p; i++) 
    {
        head[i] = matrix.GetNode(true , nullptr);
        //right, down 루프 연결.
    }

    int currentRow = 0;
    MatrixNode* last = head[0];

    for(int i=0;i<s.val;i++){
        Triple t;
        is >> t.row >> t.col >> t.val;
        if(t.row > currentRow){
            last->right = head[currentRow];
            currentRow=t.row;
            last = head[currentRow];
        }
        last = last->right = matrix.GetNode(false,&t);
        head[t.col]->next = head[t.col]->next->down = last;
    }
    last->right = head[currentRow];
    for(int i=0;i<s.col;i++){
        head[i]->next->down = head[i];
    }
    for(int i=0; i<p-1; i++){
        head[i]->next = head[i+1];
    }
    head[p-1]->next = matrix.headerNode;
    matrix.headerNode->right = head[0];
    delete[] head;
    return is;
}
MatrixNode* Matrix::av = nullptr;
