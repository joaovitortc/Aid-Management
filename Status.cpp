/* Citation and Sources...
Final Project Milestone 1
Module: Status
Filename: Status.cpp
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Status.h"
#include "Utils.h"

namespace sdds {

	Status::Status(char* descriptionTo) {
		description = nullptr;
		if (descriptionTo != nullptr) {
			alocpy(description, descriptionTo);
		}
		code = 0;
	}

	Status::Status(Status& src) {
		description = nullptr;

		*this = src;
	}

	Status::~Status() {
		delete[] description;
		description = nullptr;
	}

	Status& Status::operator=(Status& from) {

		if (this != &from) { //check for self-assignment
			code = from.code;
			alocpy(description, from.description);
		}
		return *this;
	}

	Status& Status::operator=(int codeTo) {
		code = codeTo;

		return *this;
	}

	Status& Status::operator=(const char* desc) {
		alocpy(description, desc);

		return *this;
	}

	Status::operator int() const {
		return code;
	}

	Status::operator const char* () const {
		return description;
	}

	Status::operator bool() const {
		return description == nullptr;
	}

	Status& Status::clear() {

		if (description) {
			delete[] description;
			description = nullptr;
		}
		code = 0;

		return *this;
	}

}