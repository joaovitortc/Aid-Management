/* Citation and Sources...
Final Project Milestone 1
Module: Status
Filename: Status.h
Version 1.0
Author	Joao Vitor Topanotti da Cunha
Revision History
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H

#include <iostream>

namespace sdds {

	class Status {
		char* description;
		int code;
	public:
		Status(char* descriptionSrc = nullptr);
		~Status();
		Status(Status& src);
		Status& operator=(Status& from);
		Status& operator=(int codeTo);
		Status& operator=(const char* desc);
		
		//casting
		operator int() const;
		operator const char* () const;
		operator bool() const;

		Status& clear();
		friend std::ostream& operator<<(std::ostream& os, const Status& obj) {
			if (!obj) {
				if ((int)obj != 0) {
					os << "ERR#" << (int)obj << ": ";
				}
				os << (const char*)obj;
			}

			return os;
		}
	};
	

}


#endif