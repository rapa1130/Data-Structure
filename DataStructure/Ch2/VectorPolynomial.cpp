#include "VectorPolynomial.h"

VectorPolynomial VectorPolynomial::operator+(const VectorPolynomial& right) const
{
	int posA = 0, posB = 0;
	vector<Term> ret;
	while (posA < terms.size() && posB < right.terms.size()) {
		if (terms[posA].exponent > right.terms[posB].exponent) {
			ret.push_back(Term(right.terms[posB]));
			posB++;
		}
		else if (terms[posA].exponent < right.terms[posB].exponent) {
			ret.push_back(Term(terms[posA]));
			posA++;
		}
		else {
			Term newTerm(terms[posA].exponent, terms[posA].coefficient + right.terms[posB].coefficient);
			ret.push_back(newTerm);
			posA++;
			posB++;
		}
	}
	for (; posA < terms.size(); posA++) {
		ret.push_back(terms[posA]);
	}
	for (; posB < right.terms.size(); posB++) {
		ret.push_back(terms[posB]);
	}
	VectorPolynomial newPoly;
	newPoly.terms = ret;
	return newPoly;
}

VectorPolynomial VectorPolynomial::operator*(const VectorPolynomial& right) const
{
	return VectorPolynomial();
}

float VectorPolynomial::eval() const
{
	return 0.0f;
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