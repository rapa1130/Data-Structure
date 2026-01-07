#include"Polynomial_static.h"
#include<vector>
using std::vector;

int Polynomial_static::capacity=100;
int Polynomial_static::free=0;
Term* Polynomial_static::terms=new Term[100];

Polynomial_static Polynomial_static::operator+(const Polynomial_static &right)
{
    Polynomial_static ret;
    int posA=start;
    int posB=right.start;
    while(posA<=finish && posB<=right.finish){
        if(terms[posA].exponent<terms[posB].exponent){
            ret.NewTerm(terms[posA]);
            posA++;
            
        }
        else if(terms[posA].exponent>terms[posB].exponent){
            ret.NewTerm(terms[posB]);
            posB++;

        }else{
            int exp=terms[posA].exponent;
            float cof=terms[posA].coefficient+terms[posB].coefficient;
            ret.NewTerm(Term(cof,exp));
            posA++;
            posB++;
        }
    }
    for(;posA<=finish;posA++){
        ret.NewTerm(terms[posA]);
    }
    for(;posB<=right.finish;posB++){
        ret.NewTerm(terms[posB]);
    }
    return ret;
}

Polynomial_static Polynomial_static::operator-(const Polynomial_static &right)
{
    Polynomial_static ret;
    int posA=start;
    int posB=right.start;
    while(posA<=finish && posB<=right.finish){
        if(terms[posA].exponent<terms[posB].exponent){
            ret.NewTerm(terms[posA]);
            posA++;
            
        }
        else if(terms[posA].exponent>terms[posB].exponent){
            ret.NewTerm(Term(-terms[posB].coefficient,terms[posB].exponent));
            posB++;

        }else{
            int exp=terms[posA].exponent;
            float cof=terms[posA].coefficient-terms[posB].coefficient;
            if(!(abs(cof)<=1e-10)){
                ret.NewTerm(Term(cof,exp));
            }
            posA++;
            posB++;
        }
    }
    for(;posA<=finish;posA++){
        ret.NewTerm(terms[posA]);
    }
    for(;posB<=right.finish;posB++){
        ret.NewTerm(Term(-terms[posB].coefficient,terms[posB].exponent));
    }
    return ret;
}

Polynomial_static Polynomial_static::operator*(const Polynomial_static &right)
{
    int resultStart=free;
    Polynomial_static resultTemp;
    for(int i=start;i<=finish;i++){
        Term& nowLeft=terms[i];
        Polynomial_static intermediate;
        for(int j=right.start;j<=right.finish;j++){
            Term& nowRight=terms[j];
            int exp=nowLeft.exponent+nowRight.exponent;
            float cof=nowLeft.coefficient*nowRight.coefficient;
            intermediate.NewTerm(Term(cof,exp));
        }
        resultTemp=intermediate+resultTemp;
    }
    free=resultStart;
    Polynomial_static ret;
    for(int i=resultTemp.start;i<=resultTemp.finish;i++){
        ret.NewTerm(resultTemp.terms[i]);
    }
    return ret;
}

float Polynomial_static::eval(float x) const
{
    float nowX=1;
    float ret=0;
    int lastExp=0;
    for(int i=start;i<=finish;i++){
        nowX*=powl(x,(terms[i].exponent-lastExp));
        ret+=terms[i].coefficient*nowX;
        lastExp=terms[i].exponent;
    }
    return ret;
}

void Polynomial_static::NewTerm(const Term &term)
{
    if(free>=capacity){
        capacity*=2;
        Term* newTerms=new Term[capacity];
        for(int i=0;i<capacity;i++){
            newTerms[i]=terms[i];
        }
        delete[] terms;
        terms=newTerms;
    }
    terms[free]=term;
    free++;
    finish++;
}

istream &operator>>(istream &is, Polynomial_static &pol)
{
    
    // TODO: 여기에 return 문을 삽입합니다.
}

ostream &operator<<(ostream &os, const Polynomial_static &pol)
{
    for(int i=pol.finish;i>=pol.start;i--){
        const Term& nowTerm=pol.terms[i];
        os<<nowTerm.coefficient<<"x^"<<nowTerm.exponent;
        if(i!=pol.start){
            os<<" + ";
        }
    }
    return os;
}
