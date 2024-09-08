
#include "Polynomial.h"
#include<algorithm>
using namespace std;
Polynomial::Polynomial()
	:capacity(1),size(0)
{
	terms = new Term[1];
}

Polynomial Polynomial::Add(const Polynomial& right) const
{
	Polynomial added;
	int posA=0,posB=0;
	while(posA<size && posB< right.size){
		if(terms[posA].exponent>right.terms[posB].exponent){
			added.NewTerm(right.terms[posB].coefficient,right.terms[posB].exponent);
			posB++;
		}
		else if(terms[posA].exponent<right.terms[posB].exponent){
			added.NewTerm(terms[posA].coefficient,terms[posA].exponent);
			posA++;
		}else{
			float addedCoefficient=terms[posA].coefficient+right.terms[posB].coefficient;
			added.NewTerm(addedCoefficient,terms[posA].exponent);
			posA++; posB++;
		}
	}
	for(;posA<size;posA++){
		added.NewTerm(terms[posA].coefficient,terms[posA].exponent);
	}
	for(;posB<right.size;posB++){
		added.NewTerm(right.terms[posB].coefficient,right.terms[posB].exponent);
	}

	return added;
}


float Polynomial::Eval(float f) const
{
	int result=0;
	int nowPow=1;
	int prevExp=0;
	for(int i=0;i<size;i++){
		Term& term=terms[i];
		int diffExp=term.exponent-prevExp;
		for(int i=0;i<diffExp;i++){
			nowPow*=f;
		}
		result+=term.coefficient*nowPow;
		prevExp=term.exponent;
	}
	return result;
}

istream& operator>>(istream& is, Polynomial& pol)
{
	int termCount;
	is>>termCount;
	float coefficient;
	int exponent;
	while(termCount-->0){
		is>>coefficient>>exponent;
		pol.NewTerm(coefficient,exponent);
	}
	return is;
}

ostream &operator<<(ostream &os, const Polynomial &pol)
{
	for(int i=0;i<pol.size;i++){
		os<<pol.terms[i].coefficient<<"X^"<<pol.terms[i].exponent<<" ";
		if(i!=pol.size-1){
			if(pol.terms[i+1].coefficient>0){
				os<<"+";
			}
			
		}
	}
	return os;
}

Polynomial Polynomial::Mul(const Polynomial& right) const
{
	Polynomial multiplied;
	for(int i=0;i<size;i++){
		int nowPos=0;
		for(int j=0;j<right.size;j++){
			int exp=terms[i].exponent+right.terms[j].exponent;
			float cof=terms[i].coefficient*right.terms[j].coefficient;
			for(;nowPos<multiplied.size;nowPos++){
				if(multiplied.terms[nowPos].exponent==exp){
					multiplied.terms[nowPos].coefficient+=cof;
					break;
				}
			}
			if(nowPos>=multiplied.size){
				multiplied.NewTerm(cof,exp);
				if(multiplied.size>=2){
					Term& last=multiplied.terms[multiplied.size-1];
					Term& prevLast=multiplied.terms[multiplied.size-2];
					if(last.exponent<prevLast.exponent){
						swap(last,prevLast);
					}
				}
			}

		}
	}
	return multiplied;
}


void Polynomial::NewTerm(float coefficient, int exponent)
{
	if(size>=capacity){
		capacity*=2;
		Term* temp=new Term[capacity];
		copy(terms,terms+size,temp);
		delete[] terms;
		terms=temp;
	}
	terms[size]=Term(coefficient,exponent);
	size++;
}
