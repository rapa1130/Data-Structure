#pragma once
#include<iostream>
struct Term {
	float coefficient;
	int exponent;
};
using std::istream;
using std::ostream;

class Polynomial {
public:
	Polynomial();
	Polynomial Add(const Polynomial& right) const;
	Polynomial Mul(const Polynomial& right) const;
	float Eval(float f)const;
private:
	Term* terms;
	int capacity;
	int size;
};
istream& operator>>(istream& is,const Polynomial& pol);
ostream& operator>>(ostream& os,const Polynomial& pol);
