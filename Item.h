/* Citation and Sources...
Final Project Milestone 4
Module: Item
Filename: Item.h
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Status.h"

#define BUFFER_SIZE 1024

namespace sdds {

	class Item : public iProduct {
	private:
		double price;
		int quantityOnHand;
		int neededQuantity;
		char* itemDescription;
		bool outputLinear;
	protected:
		Status status;
		int SKU;
		bool linear() const;

	public:
		Item();

		//rule of three
		Item& operator=(Item& from);
		Item(Item& src);
		virtual ~Item();

		void clear();

		virtual int readSku(std::istream& istr) override;
		
		virtual int operator-=(int qty) override;
	
		virtual int operator+=(int qty) override;
		
		virtual operator double()const override;
		
		virtual operator bool()const override;

		operator const char* () const;
		
		virtual int qtyNeeded()const override;
		
		virtual int qty()const override;
		
		virtual void linear(bool isLinear) override;
	
		virtual std::ofstream& save(std::ofstream& ofstr) override;
	
		virtual std::ifstream& load(std::ifstream& ifstr) override;
	
		virtual std::ostream& display(std::ostream& ostr) override;
	
		virtual std::istream& read(std::istream& istr) override;
	
		virtual bool operator==(int sku)const override;

		virtual bool operator==(const char* description) const override;

		virtual int getSKU() const override;
	};
}

#endif