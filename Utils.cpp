/* ------------------------------------------------------
Final Project Milestone 56
Module: Utils
Filename: Utils.cpp
Version 1.0
Author	Wing Ho Cheung
Revision History
-----------------------------------------------------------
Date        Reason
2022/04/06  Preliminary release
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstring>
#include "Utils.h"
using namespace std;
namespace sdds
{
   Utils ut;
   void Utils::testMode(bool testmode)
   {
      m_testMode = testmode;
   }
   void Utils::getSystemDate(int *year, int *mon, int *day)
   {
      if (m_testMode)
      {
         if (day)
            *day = sdds_testDay;
         if (mon)
            *mon = sdds_testMon;
         if (year)
            *year = sdds_testYear;
      }
      else
      {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day)
            *day = lt.tm_mday;
         if (mon)
            *mon = lt.tm_mon + 1;
         if (year)
            *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year) const
   {
      int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
      int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }

   // allocate memory in destination and copies the source into it
   void Utils::alocpy(char *&destination, const char *source)
   {
      delete[] destination;
      destination = nullptr;
      if (source != nullptr)
      {
         destination = new char[strlen(source) + 1];
         strcpy(destination, source);
      }
   }

   // get valid Integer
   int Utils::getint(const char *prompt) const
   {
      int val;

      if (prompt != nullptr) // display the prompt if not null
         cout << prompt;

      while (1) // loop until a valid integer is entered
      {
         cin >> val; // foolproof entry of an integer

         if (cin.fail()) // display error message if the user enters an invalid integer
         {
            cout << "Invalid Integer, retry: ";
            cin.clear();
            cin.ignore(1000, '\n');
         }
         else
            break;
      }
      return val;
   }

   // get valid Integer within range
   int Utils::getint(int min, int max, const char *prompt, const char *errMes) const
   {
      int val = getint(prompt); // reuse the previous getint()

      while (1) // loop until an acceptable value is entered
      {
         if (val >= min && val <= max)
            break;

         else // display error message if the entered integer is not within the acceptable range
         {
            if (errMes != nullptr)
               cout << errMes << ", retry: ";
            else
               cout << "Value out of range [" << min << "<=val<=" << max << "]: ";

            cin >> val;
         }
      }
      cin.clear();
      cin.ignore(1000, '\n');
      return val;
   }

   // get valid Double
   double Utils::getdouble(const char *prompt) const
   {
      double val;

      if (prompt != nullptr) // display the prompt if not null
         cout << prompt;

      while (1) // loop until a valid integer is entered
      {
         cin >> val; // foolproof entry of an integer

         if (cin.fail()) // display error message if the user enters an invalid integer
         {
            cout << "Invalid number, retry: ";
            cin.clear();
            cin.ignore(1000, '\n');
         }
         else
            break;
      }
      return val;
   }

   // get valid Double within range
   double Utils::getdouble(double min, double max, const char *prompt, const char *errMes) const
   {
      double val = getdouble(prompt); // reuse the previous getint()

      while (1) // loop until an acceptable value is entered
      {
         if (val >= min && val <= max)
            break;

         else // display error message if the entered integer is not within the acceptable range
         {
            if (errMes != nullptr)
               cout << errMes << ", retry: ";
            else
            {
               cout << "Value out of range [";
               cout.setf(ios::fixed);
               cout.precision(2);
               cout << min << "<=val<=" << max << "]: ";
            }
            cin >> val;
         }
      }
      cin.clear();
      cin.ignore(1000, '\n');
      return val;
   }
}