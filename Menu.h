/* Citation and Sources...
Final Project Milestone 2
Module: Menu
Filename: Menu.h
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_MENU_H
#define SDDS_MENU_H

#define MAX_OPTIONS 15

namespace sdds {
	class Menu {
		char* options;
		int noOptions;
	public:
		Menu(const char*);
		Menu(Menu&) = delete;
		Menu& operator=(Menu&) = delete;
		~Menu();
		int run() const;
		void printMenu() const;

	};

	int findOptions(const char* s);
	
}




#endif