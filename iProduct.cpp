/* ------------------------------------------------------
Final Project Milestone 56
Module: iProduct
Filename: iProduct.cpp
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
#include "iProduct.h"
using namespace std;
namespace sdds
{
    iProduct::~iProduct() {}

    istream &operator>>(istream &istr, iProduct &iprod)
    {
        iprod.read(istr);
        return istr;
    }

    ostream &operator<<(ostream &ostr, const iProduct &iprod)
    {
        iprod.display(ostr);
        return ostr;
    }
}
