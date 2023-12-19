/* Citation and Sources...
Final Project Milestone 4
Module: Perishable
Filename: Perishable.cpp
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cstring>
#include "Perishable.h"
#include "Utils.h"

using namespace std;

namespace sdds {
	Perishable::Perishable() : expiryDate() {
		pDescription = nullptr;
	}

	//rule of three
	Perishable& Perishable::operator=(Perishable& from) {

		if (this != &from) { //check for self-assignment
			Item::operator=(from);
			expiryDate = from.expiryDate;
			alocpy(pDescription, from.pDescription);
		}
		return *this;
	}

	
	Perishable::Perishable(Perishable& src) { 
		pDescription = nullptr;
		*this = src;
	}

	Perishable::~Perishable() {
		delete[] pDescription;
		pDescription = nullptr;
	}

	const Date& Perishable::expiry() const {
		return expiryDate;
	}

	int Perishable::readSku(istream& istr) {
		cout << "SKU: ";

		int tempSku = ut.getint(10000, 39999);

		SKU = tempSku;

		return SKU;
	}

	ofstream& Perishable::save(ofstream& ofstr) {
		if (status) {
			Item::save(ofstr);

			ofstr << "\t";

			if (pDescription != nullptr && strcmp(pDescription, "") != 0) {
				ofstr << pDescription;
			}

			ofstr << "\t";

			expiryDate.formatted(false);
			ofstr << expiryDate;

		}
		return ofstr;
	}


	ifstream& Perishable::load(ifstream& ifstr) {
		Item::load(ifstr);

		char tempDescription[BUFFER_SIZE]{};

		if (ifstr.peek() != '\t') {
			ifstr.get(tempDescription, sizeof(tempDescription), '\t');
		}
		else {
			delete[] pDescription;
			pDescription = nullptr;
		}

		ifstr.ignore(1, '\t');

		ifstr >> expiryDate;

		ifstr.ignore(1, '\n');

		if (!ifstr) {
			status = "Input file stream read (perishable) failed!";
		}
		else {
			alocpy(pDescription, tempDescription);
		}

		return ifstr;
	}

	ostream& Perishable::display(ostream& ostr) {
		if (status) {
			if (linear()) {
				Item::display(ostr);
				if (pDescription != nullptr && strcmp(pDescription, "") != 0) {
					ostr << "*";
				}
				else {
					ostr << " ";
				}
				
				expiryDate.formatted(true);
				ostr << expiryDate;

			}
			else {
				ostr << "Perishable ";
				Item::display(ostr);
				ostr << "Expiry date: ";

				expiryDate.formatted(true);
				ostr << expiryDate << endl;

				if (pDescription != nullptr && strcmp(pDescription, "") != 0) {
					ostr << "Handling Instructions: " << pDescription << endl;
				}

			}
		}
		else {
			ostr << status;
		}

		return ostr;
	}

	istream& Perishable::read(istream& istr) {
		char tempDescription[BUFFER_SIZE]{};

		Item::read(istr);

		delete[] pDescription;
		pDescription = nullptr;

		cout << "Expiry date (YYMMDD): ";

		istr >> expiryDate;

		istr.ignore(1000, '\n');

		cout << "Handling Instructions, ENTER to skip: ";

		if (istr.peek() != '\n') {
			istr.get(tempDescription, sizeof(tempDescription), '\n');
			alocpy(pDescription, tempDescription);
		}

		if (!istr) {
			status = "Perishable console date entry failed!";
		}

		return istr;
	}
}