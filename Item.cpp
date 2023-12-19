/* Citation and Sources...
Final Project Milestone 4
Module: Item
Filename: Item.cpp
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include "Item.h"
#include "Utils.h"

using namespace std;

namespace sdds {

	Item::operator const char* () const {
		return itemDescription;
	}

	bool Item::linear() const{
		return outputLinear;
	}

	Item::Item() {
		price = 0;
		quantityOnHand = 0;
		neededQuantity = 0;
		SKU = 0;
		itemDescription = nullptr;
		outputLinear = false;
	}

	Item& Item::operator=(Item& from) {

		if (this != &from) { //check for self-assignment
			price = from.price;
			quantityOnHand = from.quantityOnHand;
			neededQuantity = from.neededQuantity;
			SKU = from.SKU;
			outputLinear = from.outputLinear;
			alocpy(itemDescription, from.itemDescription);
		}
		return *this;
	}

	Item::Item(Item& src) {
		itemDescription = nullptr;
		*this = src;
	}

	Item::~Item() {
		delete[] itemDescription;
		itemDescription = nullptr;
	}

	void Item::clear() {
		status.clear();
	}

	int Item::operator-=(int qty) {
		return quantityOnHand -= qty;
	}

	int Item::operator+=(int qty) {
		return quantityOnHand += qty;
	}

	Item::operator double()const {
		return price;
	}

	Item::operator bool()const {
		return ((bool)status && itemDescription != nullptr); //returns true if the status description is null
	}

	int Item::qtyNeeded()const {
		return neededQuantity;
	}

	int Item::qty()const {
		return quantityOnHand;
	}

	void Item::linear(bool isLinear) {
		outputLinear = isLinear;
	}

	ofstream& Item::save(ofstream& ofstr) {

		if (status) {
			ofstr << SKU << "\t" << itemDescription << "\t" << quantityOnHand << "\t" << neededQuantity << "\t";
			ofstr.precision(2);
			ofstr << fixed << price;
		}

		return ofstr;
	}

	ifstream& Item::load(ifstream& ifstr) {
		char tempDescription[BUFFER_SIZE]{};

		ifstr >> SKU;

		ifstr.ignore(1, '\t');

		ifstr.get(tempDescription, sizeof(tempDescription) + 1, '\t');

		ifstr.ignore(1, '\t');

		ifstr >> quantityOnHand;

		ifstr.ignore(1, '\t');

		ifstr >> neededQuantity;

		ifstr.ignore(1, '\t');

		ifstr >> price;

		ifstr.ignore(1, '\n');

		if (ifstr) {
			alocpy(itemDescription, tempDescription);
		}
		else {
			status = "Input file stream read failed!";
		}

		return ifstr;

	}

	ostream& Item::display(ostream& ostr) {
		const int numOfChars = 35;

		if (status) {

			if (outputLinear) {
				char substring[numOfChars + 1]{};

				strncpy(substring, itemDescription, numOfChars);
				substring[numOfChars] = '\0';

				ostr.fill(' ');
				ostr << setw(5) << left << SKU << " | ";
				ostr << setw(35) << left << substring << " | ";
				ostr << setw(4) << right << quantityOnHand << " | ";
				ostr << setw(4) << right << neededQuantity << " | ";
				ostr << fixed << setprecision(2) << setw(7) << right << price << " |";
			}
			else {
				ostr << "AMA Item:" << endl;
				ostr << SKU << ": " << itemDescription << endl;
				ostr << "Quantity Needed: " << neededQuantity << endl;
				ostr << "Quantity Available: " << quantityOnHand << endl;
				ostr << fixed << setprecision(2);
				ostr << "Unit Price: $" << price << endl;
				ostr << "Needed Purchase Fund: $" << (price * (neededQuantity - quantityOnHand)) << endl;
			}

		}
		else {
			ostr << (const char*)status;
		}

		return ostr;
	}

	int Item::readSku(std::istream& istr) {
		cout << "SKU: ";

		int tempSku = ut.getint(40000, 99999);

		SKU = tempSku;

		return SKU;
	}


	istream& Item::read(istream& istr) {
		char tempDescription[BUFFER_SIZE]{};

		status.clear();

		cout << "AMA Item:" << endl;

		cout << "SKU: " << SKU << endl;

		istr.ignore(1, '\n');

		cout << "Description: ";
		
		istr.get(tempDescription, sizeof(tempDescription), '\n');

		istr.ignore(1, '\n');

		cout << "Quantity Needed: ";
		neededQuantity = ut.getint(1, 9999);

		cout << "Quantity On Hand: ";
		quantityOnHand = ut.getint(0, neededQuantity);

		cout << "Unit Price: $";
		price = ut.getdouble(0.0, 9999.0);


		if (istr) {
			alocpy(itemDescription, tempDescription);
		}
		else {
			status = "Console entry failed!";
		}

		return istr;
	}

	bool Item::operator==(int sku)const {
		return SKU == sku;

	}

	bool Item::operator==(const char* description) const {
		bool valid = false;

		if (description != nullptr && itemDescription != nullptr) {
			if (strstr(itemDescription, description)) {
				valid = true;
			}
		}

		return valid;
	}

	int Item::getSKU() const {
		return SKU;
	}
}