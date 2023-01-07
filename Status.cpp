/* ------------------------------------------------------
Final Project Milestone 56
Module: Status
Filename: Status.cpp
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
#include "Status.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    void Status::setEmpty()
    {
        delete[] m_desc;
        m_desc = nullptr;
        m_code = 0;
    }

    void Status::set(const char *desc, int code)
    {
        m_code = code; // default code is 0

        if (desc != nullptr)
            ut.alocpy(m_desc, desc);
        else
            setEmpty();
    }

    Status::Status(const char *desc) { set(desc); }

    Status::Status(const Status &status) { set(status.m_desc, status.m_code); }

    Status &Status::operator=(const Status &status)
    {
        if (this != &status)
            set(status.m_desc, status.m_code);
        return *this;
    }

    Status::~Status() { setEmpty(); }

    Status &Status::operator=(const int code)
    {
        m_code = code;
        return *this;
    }

    Status &Status::operator=(const char *desc)
    {
        ut.alocpy(m_desc, desc);
        return *this;
    }

    Status::operator int() const { return m_code; }

    Status::operator const char *() const { return m_desc; }

    Status::operator bool() const { return m_desc == nullptr; } // no description is valid state

    Status &Status::clear()
    {
        setEmpty(); // deallocates the description and sets the code to zero
        return *this;
    }

    ostream &operator<<(ostream &ostr, const Status &status)
    {
        if (!status) // if invalid state
        {
            if (int(status) != 0) // print the code only if it is not zero
                ostr << "ERR#" << int(status) << ": ";
            ostr << (const char *)(status);
        }
        return ostr;
    }
}
