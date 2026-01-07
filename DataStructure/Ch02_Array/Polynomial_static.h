#ifndef POLYNOMIAL_STATIC_H
#define POLYNOMIAL_STATIC_H
#include<iostream>
using std::ostream;
using std::istream;


struct Term{
    float coefficient;
    int exponent;
    Term(float coefficient,int exponent) :coefficient(coefficient),exponent(exponent){}
    Term():coefficient(0),exponent(0){}
    Term(const Term& term)
    :coefficient(term.coefficient),exponent(term.exponent){}
};

class Polynomial_static{
    public:
        Polynomial_static():start(free),finish(free-1){}
        Polynomial_static operator+(const Polynomial_static& right);
        Polynomial_static operator-(const Polynomial_static& right);
        Polynomial_static operator*(const Polynomial_static& right);
        float eval(float x)const;
        friend istream& operator>>(istream& is,Polynomial_static& pol);
        friend ostream& operator<<(ostream& os,const Polynomial_static& pol);
        void NewTerm(const Term& term);

    private:
        static Term* terms;
        static int free;
        static int capacity;
        int start,finish;
};

#endif