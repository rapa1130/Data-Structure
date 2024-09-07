#pragma once
#include<iostream>
struct Term {
	float coefficient;
	int exponent;
	Term(){}
	Term(float coefficient,int exponent)
	:coefficient(coefficient),exponent(exponent){}
};
using std::istream;
using std::ostream;

class Polynomial {
public:
	Polynomial();
	Polynomial Add(const Polynomial& right) const;
	Polynomial Mul(const Polynomial& right) const;
	void NewTerm(float coefficient,int exponent);
	float Eval(float f)const;
	friend istream& operator>>(istream& is,Polynomial& pol);
	friend ostream& operator<<(ostream& os,const Polynomial& pol);
private:
	Term* terms;
	int capacity;
	int size;
};
istream& operator>>(istream& is,const Polynomial& pol);
ostream& operator<<(ostream& os,const Polynomial& pol);
