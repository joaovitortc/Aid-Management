/* Citation and Sources...
Final Project Milestone 1
Module: Date
Filename: Date.cpp
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#include <iostream>
#include <iomanip>
#include "Date.h"
#include "Utils.h"

using namespace std;

namespace sdds {
	bool Date::validate() {
		int tempYear = 0;
		int tempMonth = 0;
		int tempDay = 0;
		bool valid = true;

		ut.getSystemDate(&tempYear, &tempMonth, &tempDay);

		if (month == 0 && day == 0) { // basically checks if month and date are not numbers
			status = "Invalid date value";
			status = 0;
			valid = false;
		}
		else if (year < tempYear || year > MAX_YEAR) {
			status = "Invalid year in date";
			status = 1;
			valid = false;
		}
		else if (month < 1 || month > 12) {
			status = "Invalid month in date";
			status = 2;
			valid = false;
		}
		else if (day < 1 || day > ut.daysOfMon(month, year)) {
			status = "Invalid day in date";
			status = 3;
			valid = false;
		}
		else {
			status.clear();
		}

		return valid;
	}

	int Date::uniqueValue() const {
		return year * 372 + month * 31 + day;
	}

	Date::Date() {
		ut.getSystemDate(&year, &month, &day);
		format = true;
	}

	Date::Date(int y, int mon, int d) {

		year = y;
		month = mon;
		day = d;
		format = true;

		validate();

	}

	//comparison operators
	bool Date::operator<(Date& comp) const {
		return (uniqueValue() < comp.uniqueValue());
	}
	bool Date::operator>(Date& comp) const {
		return uniqueValue() > comp.uniqueValue();
	}
	bool Date::operator<=(Date& comp) const {
		return uniqueValue() <= comp.uniqueValue();
	}
	bool Date::operator>=(Date& comp) const {
		return uniqueValue() >= comp.uniqueValue();
	}
	bool Date::operator==(Date& comp) const {
		return uniqueValue() == comp.uniqueValue();
	}
	bool Date::operator!=(Date& comp) const {
		return uniqueValue() != comp.uniqueValue();
	}

	const Status& Date::state() const {
		return status;
	}

	Date& Date::formatted(bool b) {
		format = b;
		return *this;
	}

	Date::operator bool() {
		return (bool)status;
	}

	std::ostream& Date::write(std::ostream& os) const {

		if (format) {
			os << std::setfill('0') << std::setw(4) << year << "/"
				<< std::setw(2) << month << "/"
				<< std::setw(2) << day;
		}
		else {
			os << std::setfill('0') << std::setw(2) << year % 100
				<< std::setw(2) << month
				<< std::setw(2) << day;
		}

		return os;
	}

	std::istream& Date::read(std::istream& is) {
		int date{};
		int currentYear{};
		int tempYear {};

		ut.getSystemDate(&currentYear);

		is >> date;

		if (date < 9999) {
			month = (int)(date / 100);
			day = date % 100;
			year = currentYear;
		}
		else {
			tempYear = (int)(date / 10000);
			month = (int)(date / 100) - (tempYear * 100);
			day = date % 100;
			year = tempYear + 2000;
		}

		if (!validate()) {
			is.setstate(ios::badbit);
		}

		return is;
	}

	Date& Date::operator=(Date& from) {
		if (this != &from) { //check for self-assignment
			year = from.year;
			month = from.month;
			day = from.day;
			status = from.status;
			format = from.format;
			
		}
		return *this;
	}


	Date::Date(Date& src) {
		*this = src;
	}

}

std::ostream& sdds::operator<<(std::ostream& os, const Date& date)
{
	date.write(os);

	return os;
}

std::istream& sdds::operator>>(std::istream& is, Date& date)
{
	date.read(is);

	return is;
} 