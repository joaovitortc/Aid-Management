/* Citation and Sources...
MAIN APPLICATION FOR FINAL PROJECT
Milestone 2 and 5
Module: AidMan
Filename: AidMan.cpp
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
#include <iostream>
#include <fstream>
#include <string.h>
#include "Perishable.h"
#include "Item.h"
#include "AidMan.h"
#include "Utils.h"
#include "Date.h"

using namespace std;
using namespace sdds;

/*
* Prints the header of the menu
*/
int AidMan::menu() {
	cout << "Aid Management System" << endl;
	cout << "Date: " << Date() << endl;
	cout << "Data file: ";
	
	if (fileName == nullptr) {
		cout << "No file" << endl;
	}
	else {
		cout << fileName << endl;
	}

	cout << "---------------------------------" << endl;

	return mainMenu.run();
}

AidMan::AidMan(const char* filename) : mainMenu("List Items\tAdd Item\tRemove Item\tUpdate Quantity\tSort\tShip Items\tNew/Open Aid Database") {

	if (filename != nullptr) {
		fileName = nullptr;
		alocpy(fileName, filename);
	}
	else {
		fileName = nullptr;
	}

}

AidMan::~AidMan() {
	deallocate();
}

/*
* Main function of the application
* Each choice of the user will call functions implemented on this file
*/
void AidMan::run() {
	int userEntry = -1;

	while (userEntry != 0) {
		
		userEntry = menu();

		if (userEntry != 7 && fileName == nullptr) {
			userEntry = 7;
		}

		switch (userEntry) {
		case 0:
			cout << "Exiting Program!" << endl;
			break;
		case 1:
			cout << "\n****List Items****\n";
			details(list());
			break;
		case 2:
			cout << "\n****Add Item****\n";
			addItem();
			break;
		case 3:
			cout << "\n****Remove Item****\n";
			removeItem();
			break;
		case 4:
			cout << "\n****Update Quantity****\n";
			updateQuantity();
			break;
		case 5:
			cout << "\n****Sort****\n";
			sort();
			break;
		case 6:
			cout << "\n****Ship Items****\n";
			shippingItems();
			break;
		case 7:
			cout << "\n****New/Open Aid Database****\n";
			load();
			break;
		}
	}

	save();

}

void AidMan::save() {
	if (fileName != nullptr) {
		ofstream os(fileName);

		int i;
		for (i = 0; i < noProducts; i++) {
			products[i]->save(os);
			os << '\n';
		}

		os.close();
	}
}

void AidMan::deallocate() {
	int i;
	for (i = 0; i < noProducts; i++) {
		delete products[i];
		products[i] = nullptr;
	}

	delete[] fileName;
	fileName = nullptr;

	noProducts = 0;
}

bool AidMan::load() {
	save();
	deallocate();

	char tempFile[1024]{};
	cout << "Enter file name: ";
	cin >> tempFile;

	alocpy(fileName, tempFile);

	ifstream file(fileName);

	if (!file) {
		cout << "Failed to open " << fileName << "for reading!" << endl;
		cout << "Would you like to create a new data file?" << endl;
		cout << "1- Yes!" << endl;
		cout << "0 - Exit" << endl;
		cout << ">";
		int number = 0;
		cin >> number;

		if (number == 1) {
			ofstream file(fileName);
			file.close();
		}
	}
	else {
		while (!file.eof()) {
			char peeked = file.peek();

			if (peeked == '1' || peeked == '2' || peeked == '3')
			{ //Perishable Item
				products[noProducts] = new Perishable;
			}
			else if (peeked == '4' || peeked == '5' || peeked == '6' || peeked == '7' || peeked == '8' || peeked == '9')
			{  //just an Item
				products[noProducts] = new Item;
			}
			else
			{ //error
				file.setstate(ios::failbit);
			}

			if (file) {
				products[noProducts]->load(file);

				if (products[noProducts]) {
					noProducts++;
				}
				else {
					delete products[noProducts];
				}
			}
			
		}
	}

	if (noProducts > 0) {
		cout << noProducts << " records loaded!" << endl << endl;
		return true;
	}
	else {
		return false;
	}

}

int AidMan::list(const char* sub_desc) {
	int productsPrinted = 0;

	cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
	cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

	if (sub_desc == nullptr) {
		int i;
		for (i = 0; i < noProducts; i++) {
			cout << "   " <<  i + 1 << " | ";
			products[i]->linear(true);
			products[i]->display(cout);
			cout << endl;
		}

		productsPrinted = i; //here productsPrinted will be = noProducts
	}
	else {
		int i;
		for (i = 0; i < noProducts; i++) {

		    //dereferencing the pointer of each product and casting it to char (using overloaded operator to return description)
			//comparing strings and displaying only the product that has sub_desc included in itemDescription.

			if (strstr(static_cast<const char*>(*products[i]), sub_desc)) {
				cout << "   " << i + 1 << " | ";
				products[i]->linear(true);
				products[i]->display(cout);
				cout << endl;
				productsPrinted++; //here productsPrinted will be only the matching 
			}
		}
	}

	cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

	if (productsPrinted == 0) {
		cout << "The list is emtpy!" << endl;
	}

	return productsPrinted;

}

void AidMan::details(int noItemsPrinted) {

	cin.ignore(1000, '\n'); //clear buffer

	if (noItemsPrinted > 1) {
		cout << "Enter row number to display details or <ENTER> to continue:" << endl;
		cout << "> ";

		if (cin.peek() != '\n') {
			int index = ut.getint(1, noItemsPrinted);
			index--; //get the correct index

			products[index]->linear(false);
			products[index]->display(cout);

			cout << "\n";
		}
	}
	cout << "\n";
}

int AidMan::search(int sku) const {
	for (int i = 0; i < noProducts; i++) {
		if (products[i]->getSKU() == sku) {
			return i;
		}
	}
	return -1;
}

/*
   Deal with all the logic to add a product to the products array
*/
void AidMan::addItem() {

	if (noProducts != sdds_max_num_items) {
		Menu tempMenu("Perishable\tNon-Perishable");
		int choice = tempMenu.run();

		switch (choice) {
		case 0:
			cout << "Aborted\n";
			return;
		case 1:
			products[noProducts] = new Perishable;
			break;
		case 2:
			products[noProducts] = new Item;
			break;
		}

		products[noProducts]->readSku(cin);

		if (search(products[noProducts]->getSKU()) == -1) {
			products[noProducts]->read(cin);

			if (products[noProducts]) {
				noProducts++;
			}
			else {
				delete products[noProducts];
			}
		}
		else {
			cout << "Sku: " << products[noProducts]->getSKU() << " is already in the system, try updating quantity instead.\n";
			delete products[noProducts];
		}
		
	}
	else {
		cout << "Database full!";
	}

	cout << "\n";
}

/* 
*  Remove a product of the given index
*/
void AidMan::remove(int index) {

	delete products[index];
	products[index] = nullptr;

	for (int i = index; i < noProducts - 1; i++) {

		products[i] = products[i + 1];
		products[i + 1] = nullptr;

	}

	noProducts--;
}

/*
* Deal with all the logic of removing an item by calling the remove(index) function
*/

void AidMan::removeItem() {
	char tempDescription[BUFFER_SIZE];
	int tempSku = 0;

	//get Cstring to find items
	cout << "Item description: ";
	cin >> tempDescription;

	list(tempDescription); //list all items that have that Cstring

	tempSku = ut.getint(10000, 99999, "Enter SKU: ");

	int searchIndex = search(tempSku); //Search that SKU

	if (searchIndex == -1) {
		cout << "SKU not found!" << endl;
	}
	else {
		cout << "Following item will be removed: " << endl;
		products[searchIndex]->linear(false);
		products[searchIndex]->display(cout);
		cout << endl;

		cout << "Are you sure?\n" << "1- Yes!\n" << "0- Exit\n" << "> ";
		int choice = ut.getint(0, 1); //get user choice

		if (!choice) { //user wants to exit
			cout << "Aborted!\n";
		}
		else { //user wants to remove the item
			remove(searchIndex);
			cout << "Item removed!\n\n";
		}
		
	}

}

void AidMan::updateQuantity() {
	char tempDescription[BUFFER_SIZE];
	int tempSku = 0;

	//get Cstring to find items
	cout << "Item description: ";
	cin >> tempDescription;

	list(tempDescription); //list all items that have that Cstring

	tempSku = ut.getint(10000, 99999, "Enter SKU: "); //get a valid SKU

	int searchIndex = search(tempSku); //Search that SKU

	if (searchIndex == -1) {
		cout << "SKU not found!" << endl;
	}
	else {
		cout << "1- Add\n2- Reduce\n0- Exit\n> ";

		int choice = ut.getint(0,2);
		int tempQty = 0;

		switch (choice) {
		case 0:
			cout << "Aborted!\n\n";
			return;
		case 1:
			//adding items
			if (products[searchIndex]->qty() != products[searchIndex]->qtyNeeded()) {
				cout << "Quantity to add: ";
				tempQty = ut.getint(1, products[searchIndex]->qtyNeeded() - products[searchIndex]->qty()); //from 1 up to the maximum amount needed to fulfill the needed quantity
				*products[searchIndex] += tempQty;
				cout << tempQty << " items added!\n";
			}
			else {
				cout << "Quantity Needed already fulfilled!\n";
			}

			break;
		case 2:

			//reducing items
			if (products[searchIndex]->qty() != 0) { 
				cout << "Quantity to reduce: ";
				tempQty = ut.getint(1, products[searchIndex]->qty()); //from 1 up to the quantity on hand
				*products[searchIndex] -= tempQty;
				cout << tempQty << " items removed!\n";
			}
			else {
				cout << "Quantity on hand is zero!\n";
			}
			break;
		}

		cout << "\n";
	}

}
/*
	Sort an array of pointers by:
		1- Finding the value that will be used to sort (qtyNeeded - qty) for each product
		2- Store the index of the highest difference product
		3- Store the product of that index in a temp array
		4- Set the product in the original array to nullptr
		5- Then, calls the remove() function to remove that item that has been placed in the temp array
		6- By the end of it, it will generate a sorted temp array and an empty products array
		7- Just copy the temp array over to the original array
*/
void AidMan::sort() {
	int indexHighestDiff = 0;
	int tempNoProducts = noProducts;

	iProduct* tempProducts[sdds_max_num_items]{};

	for (int k = 0; k < tempNoProducts; k++) {
		int difference = products[0]->qtyNeeded() - products[0]->qty();

		for (int i = 0; i < noProducts; i++) {

			if (products[i]->qtyNeeded() - products[i]->qty() >= difference) {
				difference = products[i]->qtyNeeded() - products[i]->qty();
				indexHighestDiff = i;
			}
		}

		tempProducts[k] = products[indexHighestDiff];
		products[indexHighestDiff] = nullptr;
		remove(indexHighestDiff);

	}

	//Copy from temp array to the original array

	for (int i = 0; i < tempNoProducts; i++) {
		products[i] = tempProducts[i];
		tempProducts[i] = nullptr;
		noProducts++;
	}

	cout << "Sort completed!\n\n";
}

void AidMan::shippingItems() {
	ofstream file("shippingOrder.txt");
	int noItemsShipped = 0;

	if (file) {
		file << "Shipping Order, Date: " << Date() << endl;
		file << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

		for (int i = 0; i < noProducts; i++) {
			if (products[i]->qty() == products[i]->qtyNeeded()) { //if the quantity is ready to ship
				file << "   " << noItemsShipped + 1 << " | ";
				products[i]->linear(true);
				file << *products[i] << endl;                      // print it to the file
				remove(i);                                         // and remove it from the products array
				noItemsShipped++;
			}
		}

		file << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
	} 
	else {
		cout << "Unable to open file" << endl;
	}

	cout << "Shipping Order for " << noItemsShipped << " times saved!" << endl << endl;

	file.close();
}

