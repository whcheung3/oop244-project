/* ------------------------------------------------------
Final Project Milestone 56
Module: Date
Filename: Date.h
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
#ifndef SDDS_DATE_H
#define SDDS_DATE_H
#include <iostream>
#include "Status.h"
using namespace std;
namespace sdds
{
    const int c_maxYear = 2030;

    class Date
    {
        int m_year;
        int m_month;
        int m_day;
        Status m_state;
        bool m_formatted = true;
        bool validate();
        int uniqueDateValue() const;
        void set(int year, int month, int day);

    public:
        Date(int year = 0, int month = 0, int day = 0);
        bool operator==(const Date &date) const;
        bool operator!=(const Date &date) const;
        bool operator<(const Date &date) const;
        bool operator>(const Date &date) const;
        bool operator<=(const Date &date) const;
        bool operator>=(const Date &date) const;
        const Status &state() const;
        Date &formatted(bool flag);
        operator bool() const;
        ostream &write(ostream &ostr) const;
        istream &read(istream &istr);
    };

    ostream &operator<<(ostream &ostr, const Date &date);
    istream &operator>>(istream &istr, Date &date);
}

#endif // !SDDS_DATE_H
