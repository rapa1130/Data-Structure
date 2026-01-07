#pragma once
#include"../4.3_TplChian/TemplateLL.h"

struct Term{
    int coef;
    int exp;
    Term(int coef,int exp) : coef(coef),exp(exp){}
};


class Polynomial{
    public:
        Polynomial() : poly(){}
        //insertBack?
        void InsertBack(int coef,int exp){
            poly.PushBack(Term(coef,exp));
        }
        void InsertBack(const Term& term){
            poly.PushBack(term);
        }
        Polynomial operator+(const Polynomial& right) const{
            Polynomial ret;
            LinkedList<Term>::ChainIterator ai(poly.Begin());
            LinkedList<Term>::ChainIterator bi(right.poly.Begin());

            while(ai!=poly.End() && bi !=right.poly.End()){
                if(ai->exp == bi->exp){
                    int sum=ai->coef + bi->coef;
                    if(sum)ret.InsertBack(Term(sum,ai->exp));
                    ai++; bi++;
                }else if(ai->exp > bi->exp){
                    ret.InsertBack(*ai);
                    ai++;
                }else{
                    ret.InsertBack(*bi);
                    bi++;
                }
            }
            for(;ai!=poly.End();ai++){
                ret.InsertBack(*ai);
            }
            for(;bi!=right.poly.End();bi++){
                ret.InsertBack(*bi);
            }
            return ret;
        }
        void Print() const{
            for(LinkedList<Term>::ChainIterator iter=poly.Begin();iter!=poly.End();iter++){
                cout<<iter->coef<<"X^"<<iter->exp<<" + ";
            }
            cout<<endl;
        }
    private:
        LinkedList<Term> poly;
};