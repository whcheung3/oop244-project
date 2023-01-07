/* ------------------------------------------------------
Final Project Milestone 56
Module: Aid Management
Filename: AidMan.h
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
#ifndef SDDS_AID_MAN_H
#define SDDS_AID_MAN_H
#include <iostream>
#include "Menu.h"
#include "iProduct.h"
using namespace std;
namespace sdds
{
    const int sdds_max_num_items = 100;

    class AidMan
    {
        char *m_fileName = nullptr;
        Menu m_mainMenu;
        iProduct *m_iProduct[sdds_max_num_items] = {};
        int m_numOfiProd;
        unsigned int menu() const;
        void setEmpty();
        void set(const char *fileName = nullptr);

        void save() const;
        void deallocate();
        int search(int sku) const;
        void remove(int index);

        int list(const char *sub_desc = nullptr); // Menu Item 1 (List Items)
        void add();                               // Menu Item 2 (Add Item)
        void remove();                            // Menu Item 3 (Remove Item)
        void update();                            // Menu Item 4 (Update Quantity)
        void sort();                              // Menu Item 5 (Sort)
        void ship();                              // Menu Item 6 (Ship Items)
        bool load();                              // Menu item 7 (New/Open Aid Database)
        void exit();                              // Menu Item 0 (Exit)

    public:
        AidMan();
        AidMan(const AidMan &aidMan);
        AidMan &operator=(const AidMan &aidMan);
        ~AidMan();
        void run();
    };
}
#endif // !SDDS_AID_MAN_H
