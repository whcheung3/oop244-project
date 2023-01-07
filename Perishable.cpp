/* ------------------------------------------------------
Final Project Milestone 56
Module: Perishable
Filename: Perishable.cpp
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
#include <cstring>
#include <string>
#include <fstream>
#include "Perishable.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    void Perishable::setEmpty()
    {
        delete[] m_handling;
        m_handling = nullptr;
    }

    void Perishable::set(Date expiry, const char *handling)
    {
        m_expiry = expiry;

        if (handling != nullptr)
            ut.alocpy(m_handling, handling);
        else
            setEmpty();
    }

    Perishable::Perishable() : Item() { set(); }

    Perishable::Perishable(const Perishable &perishable) : Item(perishable) { set(perishable.m_expiry, perishable.m_handling); }

    Perishable &Perishable::operator=(const Perishable &perishable)
    {
        if (this != &perishable)
        {
            (Item &)*this = perishable;
            set(perishable.m_expiry, perishable.m_handling);
        }
        return *this;
    }

    Perishable::~Perishable() { setEmpty(); }

    const Date &Perishable::expiry() const { return m_expiry; }

    int Perishable::readSku(istream &istr) { return m_sku = ut.getint(10000, 39999, "SKU: "); }

    ofstream &Perishable::save(ofstream &ofstr) const
    {
        if (m_state) // if the state of the Item is good
        {
            Item::save(ofstr); // call the save of the Base class
            ofstr << "\t";
            if (m_handling != nullptr && m_handling[0] != '\0') // if handling instructions exist and the attribute is not empty
                ofstr << m_handling;
            ofstr << "\t";
            Date tempDate = m_expiry; // for printing formatted date only
            tempDate.formatted(false);
            tempDate.write(ofstr);
        }
        return ofstr;
    }

    ifstream &Perishable::load(ifstream &ifstr)
    {
        string handling;

        Item::load(ifstr); // call the load of the Base class
        delete[] m_handling;
        m_handling = nullptr;

        if (ifstr.peek() != '\t') // if the very first character is not a Tab
        {
            getline(ifstr, handling, '\t');
            ut.alocpy(m_handling, handling.c_str());
        }
        if (ifstr.peek() == '\t')
            ifstr.ignore();
        ifstr >> m_expiry;
        if (ifstr.peek() == '\n') // ignores the newline
            ifstr.ignore();

        if (ifstr.fail()) // if the ifstream object has failed
            m_state = "Input file stream read (perishable) failed!";

        return ifstr;
    }

    ostream &Perishable::display(ostream &ostr) const
    {
        if (!m_state) // if the state is bad
            ostr << m_state;
        else
        {
            if (linear())
            {
                Item::display(ostr); // display of the base class is called

                if (m_handling != nullptr && m_handling[0] != '\0') // if handling instructions are not null and not empty
                    ostr << "*";
                else
                    ostr << " ";
                ostr << m_expiry;
            }
            else
            {
                ostr << "Perishable ";
                Item::display(ostr); // display the base class
                ostr << "Expiry date: ";
                ostr << m_expiry;
                ostr << endl;
                if (m_handling != nullptr && m_handling[0] != '\0')
                    ostr << "Handling Instructions: " << m_handling << endl;
            }
        }
        return ostr;
    }

    istream &Perishable::read(istream &istr)
    {
        Item::read(istr); // read of the base class is called

        string handling;
        delete[] m_handling;
        m_handling = nullptr;

        cout << "Expiry date (YYMMDD): ";
        istr >> m_expiry;
        cout << "Handling Instructions, ENTER to skip: ";
        istr.ignore(1000, '\n');
        if (istr.peek() != '\n') // if the very first character is not '\n'
        {
            getline(istr, handling, '\n');
            ut.alocpy(m_handling, handling.c_str());
        }

        if (istr.fail()) // if istream object is in a fail state
            m_state = "Perishable console date entry failed!";

        return istr;
    }
}
