/* ------------------------------------------------------
Final Project Milestone 56
Module: Menu
Filename: Menu.cpp
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
#include "Menu.h"
#include "Utils.h"
using namespace std;
namespace sdds
{
    void Menu::setEmpty()
    {
        delete[] m_text;
        m_text = nullptr;
        m_numOpt = 0;
    }

    void Menu::set(unsigned int numOpt, const char *text)
    {
        if (numOpt > c_maxNumOpt || text == nullptr) // if the number of options is more than 15 or the CString is null
            setEmpty();                              // the menu is rendered invalid
        else
        {
            ut.alocpy(m_text, text);
            m_numOpt = numOpt;
        }
    }

    Menu::Menu(unsigned int numOpt, const char *text) { set(numOpt, text); }

    Menu::Menu(const Menu &menu) { set(menu.m_numOpt, menu.m_text); }

    Menu &Menu::operator=(const Menu &menu)
    {
        if (this == &menu) // A Menu cannot be copied or assigned to another Menu
            set(menu.m_numOpt, menu.m_text);
        return *this;
    }

    Menu::~Menu() { setEmpty(); }

    unsigned int Menu::run() const
    {
        cout << m_text
             << "0- Exit" << endl
             << "> ";
        return ut.getint(0, m_numOpt);
    }
}
