/* Citation and Sources...
Final Project Milestone 4
Module: Perishable
Filename: Perishable.h
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds {
	class Perishable : public Item {
		Date expiryDate;
		char* pDescription = nullptr;
	public:
		Perishable();

		//rule of three
		Perishable& operator=(Perishable& from);
		Perishable(Perishable& src);
		virtual ~Perishable() override;

		const Date& expiry() const;

		virtual int readSku(std::istream& istr) override;

		virtual std::ofstream& save(std::ofstream& ofstr) override;

		virtual std::ifstream& load(std::ifstream& ifstr) override;

		virtual std::ostream& display(std::ostream& ostr) override;

		virtual std::istream& read(std::istream& istr) override;

	};
}









#endif