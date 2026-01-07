#pragma once
#include"../4.4_CircularList/CircularListFake.h"

struct Term{
    int coef;
    int exp;
    Term(int coef,int exp) : coef(coef),exp(exp){}
    Term(){}
};


class Polynomial{
    public:
        Polynomial() : poly(Term(0,-1)) {}
        void InsertBack(int coef,int exp){
            poly.PushBack(Term(coef,exp));
        }
        void InsertBack(const Term& term){
            poly.PushBack(term);
        }
        Polynomial operator+(const Polynomial& right)const{
            CircularLinkedList<Term>::Iterator ai(poly.Begin());
            CircularLinkedList<Term>::Iterator bi(right.poly.Begin());
            Polynomial ret;
            while(true){
                if(ai->exp == bi->exp){
                    if(ai->exp == -1) return ret;
                    int sum = ai->coef + bi->coef;
                    if(sum) ret.InsertBack(sum , ai->exp);
                    ai++; bi++;
                }else if(ai->exp > bi->exp){
                    ret.InsertBack(*ai);
                    ai++;
                }else{
                    ret.InsertBack(*bi);
                    bi++;
                }
            }
            return ret;
        }
        Polynomial operator*(const Polynomial& right) const{
            Polynomial ret;

            for(auto ai=poly.Begin();ai!=poly.End();ai++){
                Polynomial intermediate;
                for(auto bi=right.poly.Begin();bi!=right.poly.End();bi++){
                    int exp=ai->exp + bi->exp;
                    int coef= ai->coef * bi->coef;
                    intermediate.InsertBack(coef,exp);
                }
                ret = ret + intermediate;
                
                cout<<"ret:";
                ret.Print();
            }
            return ret;
        }
        Polynomial operator=(const Polynomial& right){
            poly = right.poly;
            return *this;
        }
        void Print() const{
            for(auto iter=poly.Begin();iter!=poly.End();iter++){
                cout<<iter->coef<<" X^"<<iter->exp<<" + ";
            }
            cout<<endl;
        }
        float eval(float x){
            CircularLinkedList<Term> reversed = poly.Reverse();
            float ret=0.0f;
            int nowSquared=1;
            int prevExp=0;
            for(CircularLinkedList<Term>::Iterator iter=reversed.Begin();iter!=reversed.End(); ++iter){
                nowSquared *= powl(x,iter->exp - prevExp);
                ret += (iter->coef * nowSquared);
                prevExp=iter->exp;
            }

            return ret;
        }
    private:
        CircularLinkedList<Term> poly;
};