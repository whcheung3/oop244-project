/* ------------------------------------------------------
Final Project Milestone 56
Module: iProduct
Filename: iProduct.h
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
#ifndef SDDS_I_PRODUCT_H
#define SDDS_I_PRODUCT_H
#include <iostream>
#include <fstream>
using namespace std;
namespace sdds
{
    class iProduct
    {
    public:
        // destructor
        virtual ~iProduct() = 0;
        // to read the Stock-Keeping Unit from console before main data entry
        virtual int readSku(istream &istr) = 0;
        // to reduce the quantity on hand
        virtual int operator-=(int qty) = 0;
        // to increase the quantity on hand
        virtual int operator+=(int qty) = 0;
        // returns the price of the produce
        virtual operator double() const = 0;
        // returns if the iProduct is in a good state
        virtual operator bool() const = 0;
        // returns the number of products needed
        virtual int qtyNeeded() const = 0;
        // retuns the quantity on hand
        virtual int qty() const = 0;
        // determines if the iProduct is displayed in a linear format or descriptive format
        virtual void linear(bool isLinear) = 0;
        // saves the iProduct into a file
        virtual ofstream &save(ofstream &ofstr) const = 0;
        // loads an iProduct from a file
        virtual ifstream &load(ifstream &ifstr) = 0;
        // displays the iProduct on the screen
        virtual ostream &display(ostream &ostr) const = 0;
        // reads the iProduct from the console
        virtual istream &read(istream &istr) = 0;
        // return true if the sku is a match to the iProduct's sku
        virtual bool operator==(int sku) const = 0;
        // rtrns true if the description is found in the iPorduct's description
        virtual bool operator==(const char *description) const = 0;
    };

    istream &operator>>(istream &istr, iProduct &prod);
    ostream &operator<<(ostream &ostr, const iProduct &prod);
}

#endif // !SDDS_I_PRODUCT_H
