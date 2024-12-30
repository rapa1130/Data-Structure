#include"VectorPolynomial.h"
using namespace std;
int main() {
	VectorPolynomial pol1;
	pol1.NewTerm(Term(1, 3));
	pol1.NewTerm(Term(2, 3));
	pol1.NewTerm(Term(4, 3));
	cout << pol1;
}