/* Citation and Sources...
Final Project Milestone 2
Module: Date
Filename: Date.h
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include <string.h>
#include "Menu.h"
#include "Utils.h"

using namespace std;
using namespace sdds;

Menu::Menu(const char* s) {
	options = nullptr;
	noOptions = findOptions(s);
	if (s != nullptr && noOptions <= 14) {
		alocpy(options, s);
	}
}

int sdds::findOptions(const char* s) {
	int options = 0;
	size_t i;

	for (i = 0; i < strlen(s); i++) {
		if (s[i] == '\t') {
			options++;
		}
	}

	return options + 1;
}

Menu::~Menu() {
	delete[] options;
	options = nullptr;
}

int Menu::run() const {

	if (options != nullptr) {
		printMenu();
	}
	else {
		cout << "Invalid Menu!" << endl;
		return 0;
	}

	return ut.getint(0, noOptions);
}

void Menu::printMenu() const {
	size_t i = 1;
	size_t j = 0;

	//that will print only options that are not empty
	// for example: "\t\tHello\tWorld\t\t\t\t" will print 1)Hello 2)World
	while (j != strlen(options)) {
		if (options[j] != '\t') {
			cout << i << "- ";
			while (options[j] != '\t' && j != strlen(options)) {
				cout << options[j];
				j++;
			}
			cout << endl;
			i++;

		}
		else {
			j++;
		}
	}

	cout << "---------------------------------" << endl;
	cout << "0- Exit" << endl << "> ";
}
