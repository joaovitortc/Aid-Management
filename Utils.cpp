/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
/* Citation and Sources...
Final Project Milestone 1
Module: Utils
Filename: Utils.cpp
Version 2.0
Author	Joao Vitor Topanotti da Cunha
Revision History
----------------------------------------------------------
Added getDouble()
-----------------------------------------------------------
Added functions:
alocpy, and getInt()
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "Utils.h"
#include <string.h>
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }

   int Utils::getint(const char* prompt) {
       int temp = 0;
       bool valid = false;

       while (!valid) {
           if (prompt != nullptr) {
               std::cout << prompt;
          }
           if (!(std::cin >> temp)) {
               // Invalid input, clear the error state of the stream
               std::cin.clear();
               std::cin.ignore(1000, '\n');
               std::cout << "Invalid Integer, retry: ";
           }
           else {
               valid = true;
           }
       }
       return temp;
   }

   int Utils::getint(int min, int max, const char* prompt, const char* errMes) {
       bool valid = false;
       int value = 0;

       while (!valid) {
           value = ut.getint(prompt);
           if (value > max || value < min) {
               // Invalid input, clear the error state of the stream
               std::cin.clear();
               std::cin.ignore(1000, '\n');
               
               if (errMes != nullptr) {
                   std::cout << ", retry: ";
               }
               else {
                   std::cout << "Value out of range [" << min << "<=" << "val" << "<=" << max << "]: ";
               }
           }
           else {
               valid = true;
           }
       }
       return value;

   }

   double Utils::getdouble(const char* prompt) {
       double temp = 0;
       bool valid = false;

       while (!valid) {
           if (prompt != nullptr) {
               std::cout << prompt;
           }
           if (!(std::cin >> temp)) {
               // Invalid input, clear the error state of the stream
               std::cin.clear();
               std::cin.ignore(1000, '\n');
               std::cout << "Invalid number, retry: ";
           }
           else {
               valid = true;
           }
       }
       return temp;
   }

   double Utils::getdouble(double min, double max, const char* prompt, const char* errMes) {
       bool valid = false;
       double value = 0;

       while (!valid) {
           value = ut.getdouble(prompt);
           if (value > max || value < min) {
               // Invalid input, clear the error state of the stream
               std::cin.clear();
               std::cin.ignore(1000, '\n');

               if (errMes != nullptr) {
                   std::cout << ", retry: ";
               }
               else {
                   std::cout << "Value out of range [" << min << "<=" << "val" << "<=" << max << "]: ";
               }
           }
           else {
               valid = true;
           }
       }
       return value;

   }

   void alocpy(char*& destination, const char* source) {
       delete[] destination;
       destination = nullptr;

       if (source != nullptr) {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
       }

   }
   
}