
#include "Polynomial.h"


Polynomial::Polynomial()
	:capacity(capacity),size(size)
{
	terms = new Term[capacity];
}

Polynomial Polynomial::Add(const Polynomial& right) const
{

}

Polynomial Polynomial::Mul(const Polynomial& right) const
{
	
}

float Polynomial::Eval(float f) const
{

}

istream& operator>>(istream& is, const Polynomial& pol)
{
}

ostream& operator>>(ostream& os, const Polynomial& pol)
{
}
