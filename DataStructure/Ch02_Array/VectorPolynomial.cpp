#include "VectorPolynomial.h"

VectorPolynomial VectorPolynomial::operator+(const VectorPolynomial& right) const
{
	int posA = 0, posB = 0;
	VectorPolynomial ret;
	
	while (posA < terms.size() && posB < right.terms.size()) {
		if (terms[posA].exponent > right.terms[posB].exponent) {
			ret.NewTerm(right.terms[posB]);
			posB++;
		}
		else if (terms[posA].exponent < right.terms[posB].exponent) {
			ret.NewTerm(terms[posA]);
			posA++;
		}
		else {
			ret.NewTerm(Term(terms[posA].exponent, terms[posA].coefficient + right.terms[posB].coefficient));
			posA++;
			posB++;
		}
	}
	for (; posA < terms.size(); posA++) {
		ret.NewTerm(terms[posA]);
	}
	for (; posB < right.terms.size(); posB++) {
		ret.NewTerm(right.terms[posB]);
	}
	
	return ret;
}

VectorPolynomial VectorPolynomial::operator*(const VectorPolynomial& right) const
{
	VectorPolynomial multiplied;
	for(int i=0;i<terms.size();i++){
		Term leftTerm=terms[i];
		VectorPolynomial intermediate;
		for(int j=0;j<right.terms.size();j++){
			Term rightTerm=right.terms[j];
			int exp=leftTerm.exponent+rightTerm.exponent;
			int cof=leftTerm.coefficient*rightTerm.coefficient;
			intermediate.NewTerm(Term(exp,cof));
		}
		multiplied=multiplied+intermediate;
	}
	return multiplied;
}

VectorPolynomial& VectorPolynomial::operator=(const VectorPolynomial &right)
{
	if(&right==this){
		return *this;
	}
	terms.clear();
	for(int i=0;i<right.terms.size();i++){
		terms.push_back(right.terms[i]);
	}
	return *this;
}

float VectorPolynomial::eval(float x) const
{
	float result=0.0f;
	float nowX=1;
	int lastExponent=0;
	for(int i=0;i<terms.size();i++){
		nowX*=powl(x,(terms[i].exponent-lastExponent));
		lastExponent=terms[i].exponent;
		result+=nowX*terms[i].coefficient;
	}
	return result;
}

VectorPolynomial::VectorPolynomial()
{
}

VectorPolynomial::~VectorPolynomial()
{
}

void VectorPolynomial::NewTerm(const Term& term)
{
	terms.push_back(term);
}

ostream& operator<<(ostream& os, const VectorPolynomial& poly) {
	for (int i = poly.terms.size()-1; i>=0; i--) {
		os << poly.terms[i].coefficient << "x^" << poly.terms[i].exponent;
		if (i != 0) {
			os << " + ";
		}
	}
	return os;
}