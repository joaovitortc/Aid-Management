/* Citation and Sources...
Final Project Milestone 2 and 5
Module: AidMan
Filename: AidMan.h
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
11/06 - Finished V01 Milestone 2

11/20 - Finished V02 for M5 part 1
11/22 - Finished V03 for M5 part 2
11/23 - Finished V04 for M5 part 3
11/23 - Finished V05 for M5 part 4
11/24 - Finished V06 for M5 part 5

11/28 - Finished final version for Final Project M5 part 6
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_AIDMAN_H
#define SDDS_AIDMAN_H

#include "Menu.h"
#include "iProduct.h"

const int sdds_max_num_items = 100;

namespace sdds {
	class AidMan {
		char* fileName;
		Menu mainMenu;

		iProduct* products[sdds_max_num_items]{};
		int noProducts{};

		int menu();
	public:
		AidMan(const char* filename = nullptr);
		~AidMan();
		AidMan(AidMan&) = delete;
		AidMan& operator=(AidMan&) = delete;
		void run();

		void save();
		void deallocate();

		//menu 7
		bool load();

		//list items
		int list(const char* sub_desc = nullptr);
		void details(int noItensPrinted);

		//add item
		int search(int sku) const;
		void addItem();

		//remove item
		void remove(int index);
		void removeItem();

		//update quantity
		void updateQuantity();

		//sort
		void sort();

		//shipping
		void shippingItems();
	};
}








#endif