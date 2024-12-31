<<<<<<< HEAD
#include<iostream>
=======
#include"VectorPolynomial.h"
>>>>>>> 8b560217051041b4a57b9cd669cfab64d6453ed3
using namespace std;
<<<<<<< HEAD

int main(){
    cout<<"a";
=======
int main() {
	VectorPolynomial pol1;
	pol1.NewTerm(Term(1, 3));
	pol1.NewTerm(Term(2, 3));
	pol1.NewTerm(Term(4, 3));
	cout << pol1;
>>>>>>> 8b560217051041b4a57b9cd669cfab64d6453ed3
}