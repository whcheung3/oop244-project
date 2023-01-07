/* ------------------------------------------------------
Final Project Milestone 56
Module: Item
Filename: Item.cpp
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
#include "Item.h"
#include "Status.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    void Item::setEmpty()
    {
        delete[] m_description;
        m_description = nullptr;
    }

    void Item::set(double price, int qty, int qtyNeeded, const char *description, bool linear, Status state, int sku)
    {
        m_price = price;
        m_qty = qty;
        m_qtyNeeded = qtyNeeded;
        m_sku = sku;
        m_state = state;
        m_linear = linear;
        if (description != nullptr)
            ut.alocpy(m_description, description);
        else
            setEmpty();
    }

    bool Item::linear() const { return m_linear; }

    Item::Item() { set(); }

    Item::Item(const Item &item) { set(item.m_price, item.m_qty, item.m_qtyNeeded, item.m_description, item.m_linear, item.m_state, item.m_sku); }

    Item &Item::operator=(const Item &item)
    {
        if (this != &item)
            set(item.m_price, item.m_qty, item.m_qtyNeeded, item.m_description, item.m_linear, item.m_state, item.m_sku);
        return *this;
    }

    Item::~Item() { setEmpty(); }

    int Item::qtyNeeded() const { return m_qtyNeeded; }

    int Item::qty() const { return m_qty; }

    Item::operator double() const { return m_price; }

    Item::operator bool() const { return m_sku > 0 && m_state; }

    int Item::operator-=(int qty) { return m_qty -= qty; }

    int Item::operator+=(int qty) { return m_qty += qty; }

    void Item::linear(bool isLinear) { m_linear = isLinear; }

    Status Item::clear() { return m_state = 0; } // set the state back to good by resetting

    bool Item::operator==(int sku) const { return m_sku == sku; }

    bool Item::operator==(const char *description) const { return strstr(m_description, description) != nullptr; } // searche for the appearance of the received Cstring

    ofstream &Item::save(ofstream &ofstr) const
    {
        if (m_state) // if the state of the Item is good
        {
            ofstr << m_sku << "\t" << m_description << "\t" << m_qty << "\t" << m_qtyNeeded << "\t";
            ofstr.setf(ios::fixed);
            ofstr.precision(2); // written with 2 digits after the decimal point
            ofstr << m_price;
        }
        return ofstr;
    }

    ifstream &Item::load(ifstream &ifstr)
    {
        string description;

        delete[] m_description;
        m_description = nullptr;

        ifstr >> m_sku;
        if (ifstr.peek() == '\t')
            ifstr.ignore();
        getline(ifstr, description, '\t');
        ut.alocpy(m_description, description.c_str());
        if (ifstr.peek() == '\t')
            ifstr.ignore();
        ifstr >> m_qty;
        if (ifstr.peek() == '\t')
            ifstr.ignore();
        ifstr >> m_qtyNeeded;
        if (ifstr.peek() == '\t')
            ifstr.ignore();
        ifstr >> m_price;

        ifstr.ignore(1); // a single character is discarded from the file

        if (ifstr.fail()) // if ifstream is in a bad state
            m_state = "Input file stream read failed!";

        return ifstr;
    }

    ostream &Item::display(ostream &ostr) const
    {
        char *tempDesc = nullptr;
        if (!m_state) // if the state is bad
            ostr << m_state;
        else
        {
            if (linear())
            {
                ostr.setf(ios::left); // align left
                ostr.width(5);
                ostr << m_sku;
                ostr << " | ";
                if (strlen(m_description) > 35) // only the first 35 characters will be printed
                {
                    ut.alocpy(tempDesc, m_description); // copy the m_desc and allocate to tempDesc
                    tempDesc[35] = '\0';                // cut the tempDesc to only first 35 char
                    ostr << tempDesc;                   // print the shortened tempDesc
                    delete[] tempDesc;                  // deallocate the tempDesc
                    tempDesc = nullptr;
                }
                else
                {
                    ostr.width(35);
                    ostr << m_description;
                }

                ostr.setf(ios::right); // align right
                ostr << " | ";
                ostr.width(4);
                ostr << m_qty;
                ostr << " | ";
                ostr.width(4);
                ostr << m_qtyNeeded;
                ostr << " | ";
                ostr.width(7);
                ostr.setf(ios::fixed);
                ostr.precision(2); // display in 2 d.p.
                ostr << m_price;
                ostr << " |";
                cout.unsetf(ios::right);
            }
            else
            {
                ostr << "AMA Item:" << endl
                     << m_sku << ": " << m_description << endl
                     << "Quantity Needed: " << m_qtyNeeded << endl
                     << "Quantity Available: " << m_qty << endl;
                ostr.setf(ios::fixed);
                ostr.precision(2);
                ostr << "Unit Price: $" << m_price << endl
                     << "Needed Purchase Fund: $" << m_price * (m_qtyNeeded - m_qty) << endl;
            }
        }
        return ostr;
    }

    int Item::readSku(istream &istr) { return m_sku = ut.getint(40000, 99999, "SKU: "); }

    istream &Item::read(istream &istr)
    {
        string description;

        delete[] m_description;
        m_description = nullptr;
        m_state = 0;

        cout << "AMA Item:" << endl
             << "SKU: " << m_sku << endl
             << "Description: ";
        getline(istr, description, '\n');
        ut.alocpy(m_description, description.c_str());
        m_qtyNeeded = ut.getint(1, 9999, "Quantity Needed: ");
        m_qty = ut.getint(0, m_qtyNeeded, "Quantity On Hand: ");
        m_price = ut.getdouble(0.0, 9999.0, "Unit Price: $");

        if (istr.fail()) // if the istream fails during reading
            m_state = "Console entry failed!";

        return istr;
    }
}
