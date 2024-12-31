#pragma once
#include<vector>
#include<iostream>
using std::vector;
using std::ostream;
struct Term {
	float coefficient;
	int exponent;
	Term() :exponent(0), coefficient(0) {}
	Term(int exponent, float coefficient)
		:exponent(exponent), coefficient(coefficient)
	{}
	Term(const Term& term)
		:exponent(term.exponent), coefficient(term.coefficient)
	{}
};


class VectorPolynomial {
public:

	//add
	VectorPolynomial operator+(const VectorPolynomial& right)const ;
	//multiply
	VectorPolynomial operator*(const VectorPolynomial& right)const;
	//eval
	float eval()const;
	//Constructor
	VectorPolynomial();
	//Destructor
	~VectorPolynomial();
	//newTerm
	friend ostream& operator<<(ostream& os, const VectorPolynomial& poly);
	void NewTerm(const Term& term);
private:
	vector<Term> terms;
};

ostream& operator<<(ostream& os, const VectorPolynomial& poly);