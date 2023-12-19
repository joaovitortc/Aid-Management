/* Citation and Sources...
Final Project Milestone 4
Module: iProduct
Filename: iProduct.cpp
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include "iProduct.h"


using namespace std;

namespace sdds {

	ostream& operator<<(ostream& ostr, iProduct& product) {
		product.display(ostr);
		return ostr;
	}

	istream& operator>>(istream& istr, iProduct& product) {
		product.read(istr);
		return istr;
	}

}