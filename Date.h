/* Citation and Sources...
Final Project Milestone 1
Module: Date
Filename: Date.h
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <iostream>
#include "Status.h"

#define MAX_YEAR 2030

namespace sdds {

	class Date {
		int year;
		int month;
		int day;
		Status status;
		bool format;

		bool validate();
		int uniqueValue() const;
	public:
		//constructors
		Date();
		Date(int y, int mon, int d);

		//comparison operators
		bool operator<(Date& comp) const;
		bool operator>(Date& comp) const;
		bool operator<=(Date& comp) const;
		bool operator>=(Date& comp) const;
		bool operator==(Date& comp) const;
		bool operator!=(Date& comp) const;

		//accessors
		const Status& state() const;
		operator bool();               
		                                        
		//modifier
		Date& formatted(bool b);

		//write/read
		std::ostream& write(std::ostream&) const;
		std::istream& read(std::istream& is);

		Date& operator=(Date& from);
		Date(Date& src);

};
	std::ostream& operator<<(std::ostream& os, const Date& date);
	std::istream& operator>>(std::istream& is, Date& date);
	

}

#endif