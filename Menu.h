/* ------------------------------------------------------
Final Project Milestone 56
Module: Menu
Filename: Menu.h
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
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
using namespace std;
namespace sdds
{
    const int c_maxNumOpt = 15;

    class Menu
    {
        char *m_text = nullptr;
        unsigned int m_numOpt;
        void setEmpty();
        void set(unsigned int numOpt, const char *text);

    public:
        Menu(unsigned int numOpt, const char *text);
        Menu(const Menu &menu);
        Menu &operator=(const Menu &menu);
        ~Menu();
        unsigned int run() const;
    };
}
#endif // !SDDS_MENU_H
