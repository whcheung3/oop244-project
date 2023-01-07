/* ------------------------------------------------------
Final Project Milestone 56
Module: Date
Filename: Date.cpp
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
#include "Date.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    bool Date::validate()
    {
        bool result = false;
        int curYear;
        ut.getSystemDate(&curYear);

        if (m_year >= curYear && m_year <= c_maxYear)
        {
            if (m_month >= 1 && m_month <= 12)
            {
                if (m_day >= 1 && m_day <= ut.daysOfMon(m_month, m_year))
                {
                    result = true; // everything is valid
                }
                else // invalid day
                {
                    m_state = "Invalid day in date";
                    m_state = 3;
                }
            }
            else // invalid month
            {
                m_state = "Invalid month in date";
                m_state = 2;
                return result;
            }
        }
        else // invalid year
        {
            m_state = "Invalid year in date";
            m_state = 1;
            return result;
        }
        return result;
    }

    int Date::uniqueDateValue() const { return m_year * 372 + m_month * 31 + m_day; }

    void Date::set(int year, int month, int day)
    {
        if (year != 0 && month != 0 && day != 0) // if all three values are provided
        {
            m_year = year;
            m_month = month;
            m_day = day;
            validate();
        }
        else // set to the current system date if no initial value is provided
        {
            ut.getSystemDate(&year, &month, &day);
            m_year = year;
            m_month = month;
            m_day = day;
        }
    }

    Date::Date(int year, int month, int day) { set(year, month, day); }

    bool Date::operator==(const Date &date) const { return uniqueDateValue() == date.uniqueDateValue(); }

    bool Date::operator!=(const Date &date) const { return uniqueDateValue() != date.uniqueDateValue(); }

    bool Date::operator<(const Date &date) const { return uniqueDateValue() < date.uniqueDateValue(); }

    bool Date::operator>(const Date &date) const { return uniqueDateValue() > date.uniqueDateValue(); }

    bool Date::operator<=(const Date &date) const { return uniqueDateValue() <= date.uniqueDateValue(); }

    bool Date::operator>=(const Date &date) const { return uniqueDateValue() >= date.uniqueDateValue(); }

    const Status &Date::state() const { return m_state; }

    Date &Date::formatted(bool flag)
    {
        m_formatted = flag;
        return *this;
    }

    Date::operator bool() const { return m_state; }

    ostream &Date::write(ostream &ostr) const
    {
        if (m_formatted) // print in YYYY/MM/DD
        {
            ostr << m_year << "/";
            if (m_month < 10)
                ostr << "0"; // month in 2 spaces padded with zero
            ostr << m_month << "/";
            if (m_day < 10)
                ostr << "0"; // day in 2 spaces padded with zero
            ostr << m_day;
        }
        else // print in YYMMDD
        {
            ostr << m_year % 100;
            if (m_month < 10)
                ostr << "0"; // month in 2 spaces padded with zero
            ostr << m_month;
            if (m_day < 10)
                ostr << "0"; // day in 2 spaces padded with zero
            ostr << m_day;
        }
        return ostr;
    }

    istream &Date::read(istream &istr)
    {
        int intVal = 0;
        int curYear = 0;
        ut.getSystemDate(&curYear);
        istr >> intVal;

        if (intVal > 100 && intVal < 10000) // read as MMDD if four digits integer
        {
            m_year = curYear; // the year is set to the current system year
            m_month = intVal / 100;
            m_day = intVal % 100;
        }
        else if (intVal > 10000 && intVal < 1000000) // read as YYMMDD if six digits integer
        {
            m_year = intVal / 10000 + 2000;
            m_month = (intVal / 100) % 100;
            m_day = intVal % 100;
        }
        else if (intVal > 0 && intVal < 100) // read as error if less than four digits integer
        {
            m_year = curYear;
            m_month = 0;
            m_day = intVal;
        }
        else
            m_state = "Invalid date value";

        if (!validate()) // set istream into a fail state if validation fails
            istr.setstate(ios::badbit);

        return istr;
    }

    ostream &operator<<(ostream &ostr, const Date &date)
    {
        date.write(ostr);
        return ostr;
    }

    istream &operator>>(istream &istr, Date &date)
    {
        date.read(istr);
        return istr;
    }
}
