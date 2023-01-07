/* ------------------------------------------------------
Final Project Milestone 56
Module: Aid Management
Filename: AidMan.cpp
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
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"
#include "Perishable.h"
using namespace std;
namespace sdds
{
    unsigned int AidMan::menu() const
    {
        cout << "Aid Management System" << endl
             << "Date: " << Date() << endl // print current date
             << "Data file: ";
        if (m_fileName != nullptr)
            cout << m_fileName << endl;
        else
            cout << "No file" << endl;
        cout << "---------------------------------" << endl;
        return m_mainMenu.run(); // run main menu and return selection made
    }

    void AidMan::setEmpty()
    {
        delete[] m_fileName;
        m_fileName = nullptr;
    }

    void AidMan::set(const char *fileName)
    {
        if (fileName != nullptr)
            ut.alocpy(m_fileName, fileName);
        else
            setEmpty();
    }

    AidMan::AidMan()
        : m_mainMenu(7, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n")
    {
        set();
    }

    AidMan::AidMan(const AidMan &aidMan)
        : m_mainMenu(7, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n")
    {
        set(aidMan.m_fileName);
    }

    AidMan &AidMan::operator=(const AidMan &aidMan)
    {
        if (this != &aidMan)
            set(aidMan.m_fileName);
        return *this;
    }

    AidMan::~AidMan() { setEmpty(); }

    void AidMan::save() const
    {
        if (m_fileName != nullptr)
        {
            ofstream ofstr(m_fileName, ios::out);
            for (int i = 0; i < m_numOfiProd; i++)
                m_iProduct[i]->save(ofstr) << endl;
            ofstr.flush();
            ofstr.close();
        }
    }

    void AidMan::deallocate()
    {
        for (int i = 0; m_iProduct[i]; i++)
            delete m_iProduct[i];
        delete[] m_fileName;
        m_fileName = nullptr;
        m_numOfiProd = 0;
    }

    bool AidMan::load()
    {
        bool result = false;
        string fileName;

        save();
        deallocate();
        cout << "\n****New/Open Aid Database****\n"
             << "Enter file name: ";
        getline(cin, fileName, '\n');
        ut.alocpy(m_fileName, fileName.c_str());
        ifstream ifstr(m_fileName);

        if (!ifstr)
        {
            cout << "Failed to open " << m_fileName << " for reading!" << endl
                 << "Would you like to create a new data file?" << endl
                 << "1- Yes!" << endl
                 << "0- Exit" << endl
                 << "> ";
            switch (ut.getint(0, 1))
            {
            case 0:
                delete[] m_fileName;
                m_fileName = nullptr;
                cout << "Aborted!" << endl;
                break;
            case 1:
                ofstream ofstr(m_fileName, ios::out);
                break;
            }
        }
        else
        {
            int i = 0;
            while (i < sdds_max_num_items && ifstr)
            {
                if (ifstr.peek() >= '1' && ifstr.peek() <= '3')
                    m_iProduct[i] = new Perishable; // create a new Perishable item
                else if (ifstr.peek() >= '4' && ifstr.peek() <= '9')
                    m_iProduct[i] = new Item; // create a new Non-perishable item
                else
                    delete m_iProduct[i]; // the loaded item is deleted

                if (m_iProduct[i]) // if good state
                {
                    m_iProduct[i]->load(ifstr); // load the data from the file
                    i++;                        // next available iProduct Pointers added by one
                }
                else
                    ifstr.setstate(ios::badbit); // set into an invalid state
            }
            m_numOfiProd = i; // number of iProduct equals to added index
        }

        if (m_numOfiProd > 0)
        {
            result = true;
            cout << m_numOfiProd << " records loaded!" << endl;
        }
        cout << endl;
        return result;
    }

    int AidMan::list(const char *sub_desc)
    {
        int i = 0;
        if (sub_desc == nullptr) // list all items
        {
            cout << "\n****List Items****" << endl
                 << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl
                 << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            for (i = 0; i < m_numOfiProd; i++)
            {
                cout.setf(ios::right);
                cout.width(4);
                cout << i + 1;
                cout << " | ";
                cout.unsetf(ios::right);
                m_iProduct[i]->linear(true);
                m_iProduct[i]->display(cout) << endl;
            }
            cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            cout << "Enter row number to display details or <ENTER> to continue:" << endl
                 << "> ";
            if (cin.peek() != '\n') // if the very first character is not '\n'
            {
                int idx = ut.getint(1, i) - 1;
                m_iProduct[idx]->linear(false);
                m_iProduct[idx]->display(cout);
                cout << endl;
            }
            else
                cin.ignore();
            cout << endl;
        }
        else // list only matched desc items
        {
            cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl
                 << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
            for (i = 0; i < m_numOfiProd; i++)
            {
                if (*m_iProduct[i] == sub_desc)
                {
                    cout.setf(ios::right);
                    cout.width(4);
                    cout << i + 1;
                    cout << " | ";
                    cout.unsetf(ios::right);
                    m_iProduct[i]->linear(true);
                    m_iProduct[i]->display(cout);
                    cout << endl;
                }
            }
            cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        }

        if (m_numOfiProd == 0)
            cout << "The list is emtpy!" << endl;

        return i;
    }

    int AidMan::search(int sku) const
    {
        int idx = -1;
        for (int i = 0; i < m_numOfiProd; i++) // loop till the total number of iProduct added
        {
            if (*m_iProduct[i] == sku) // if the SKU is a match
                idx = i;               // return the index
        }
        return idx;
    }

    void AidMan::add()
    {
        cout << "\n****Add Item****\n";
        if (m_numOfiProd >= sdds_max_num_items)
            cout << "Database full!" << endl;
        else
            cout << "1- Perishable" << endl
                 << "2- Non-Perishable" << endl
                 << "-----------------" << endl
                 << "0- Exit" << endl
                 << "> ";

        int select = ut.getint(0, 2);
        switch (select)
        {
        case 0:
            cout << "Aborted!" << endl;
            break;
        case 1:
            m_iProduct[m_numOfiProd] = new Perishable; // create a new Perishable item
            break;
        case 2:
            m_iProduct[m_numOfiProd] = new Item; // create a new Non-perishable item
            break;
        }

        if (select == 1 || select == 2)
        {
            int tempSku = m_iProduct[m_numOfiProd]->readSku(cin); // SKU of the item is read from the console
            if (search(tempSku) != -1)                            // if the SKU is found matched with existing Items in the system
            {
                cout << "Sku: " << tempSku << " is already in the system, try updating quantity instead." << endl;
                delete m_iProduct[m_numOfiProd];
                m_iProduct[m_numOfiProd] = nullptr;
            }
            else
            {
                m_iProduct[m_numOfiProd]->read(cin); // rest of the data is read from the console
                m_numOfiProd++;                      // number of iProduct Items is added by one
            }
        }
        cout << endl;
    }

    void AidMan::remove(int index)
    {
        delete m_iProduct[index]; // delete the iProduct at index in iProduct Pointers
        for (int i = index; i < m_numOfiProd; i++)
            m_iProduct[i] = m_iProduct[i + 1]; // shift all the iProducts to left once
        m_numOfiProd--;                        // reduce number of iProduct Items by one
    }

    void AidMan::remove()
    {
        string desc;
        cout << "\n****Remove Item****\n"
             << "Item description: ";
        getline(cin, desc, '\n'); // get a Cstring for a description
        list(desc.c_str());       // list the items containing the description

        int idx = search(ut.getint(10000, 99999, "Enter SKU: "));
        if (idx == -1) // if SKU not found
            cout << "SKU not found!" << endl;
        else // if SKU is found
        {
            cout << "Following item will be removed: " << endl;
            m_iProduct[idx]->linear(false);
            m_iProduct[idx]->display(cout) << endl;
            cout << "Are you sure?" << endl
                 << "1- Yes!" << endl
                 << "0- Exit" << endl
                 << "> ";

            switch (ut.getint(0, 1))
            {
            case 0:
                cout << "Aborted!" << endl;
                break;
            case 1:
                remove(idx);
                cout << "Item removed!" << endl;
                break;
            }
        }
        cout << endl;
    }

    void AidMan::update()
    {
        int amt = -1;
        string desc;
        cout << "\n****Update Quantity****\n"
             << "Item description: ";
        getline(cin, desc, '\n'); // get a Cstring for a description
        list(desc.c_str());       // list the items containing the description

        int idx = search(ut.getint(10000, 99999, "Enter SKU: "));
        if (idx == -1) // if SKU not found
            cout << "SKU not found!" << endl;
        else // if SKU is found
        {
            cout << "1- Add" << endl
                 << "2- Reduce" << endl
                 << "0- Exit" << endl
                 << "> ";

            switch (ut.getint(0, 2))
            {
            case 0:
                cout << "Aborted!" << endl;
                break;
            case 1:
                if (m_iProduct[idx]->qty() == m_iProduct[idx]->qtyNeeded()) // if already fulfilled needed quantity
                    cout << "Quantity Needed already fulfilled!" << endl;
                else
                {
                    amt = ut.getint(1, m_iProduct[idx]->qtyNeeded(), "Quantity to add: ");
                    *m_iProduct[idx] += amt;
                    cout << amt << " items added!" << endl;
                }
                break;
            case 2:
                if (m_iProduct[idx]->qty() == 0) // if already zero quantity
                    cout << "Quaintity on hand is zero!" << endl;
                else
                {
                    amt = ut.getint(1, m_iProduct[idx]->qtyNeeded(), "Quantity to reduce: ");
                    *m_iProduct[idx] -= amt;
                    cout << amt << " items removed!" << endl;
                }
                break;
            }
        }
        cout << endl;
    }

    void AidMan::sort()
    {
        iProduct *temp = nullptr;
        cout << "\n****Sort****\n";
        for (int i = 0; i < m_numOfiProd - 1; i++)
        {
            for (int j = 0; j < m_numOfiProd - i - 1; j++)
            {
                // based on difference between quantity needed and quantity on hand in descending order
                if (m_iProduct[j]->qtyNeeded() - m_iProduct[j]->qty() <
                    m_iProduct[j + 1]->qtyNeeded() - m_iProduct[j + 1]->qty())
                {
                    temp = m_iProduct[j];
                    m_iProduct[j] = m_iProduct[j + 1];
                    m_iProduct[j + 1] = temp;
                }
            }
        }
        cout << "Sort completed!" << endl
             << endl;
    }

    void AidMan::ship()
    {
        int shipped = 0;
        ofstream ofstr("shippingOrder.txt", ios::out);
        cout << "\n****Ship Items****\n";

        ofstr << "Shipping Order, Date: " << Date() << endl
              << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl
              << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
        for (int i = 0; i < m_numOfiProd; i++)
        {
            if (m_iProduct[i]->qtyNeeded() == m_iProduct[i]->qty())
            {
                ofstr.setf(ios::right);
                ofstr.width(4);
                ofstr << shipped + 1;
                ofstr << " | ";
                ofstr.unsetf(ios::right);
                m_iProduct[i]->linear(true);
                m_iProduct[i]->display(ofstr) << endl;
                remove(i);
                shipped++;
            }
        }
        ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl
              << endl;

        cout << "Shipping Order for " << shipped << " times saved!" << endl
             << endl;
    }

    void AidMan::exit()
    {
        cout << "Exiting Program!" << endl;
        save();
        deallocate();
    }

    void AidMan::run()
    {
        int select = -1;
        while (select != 0) // loop until user selects 0
        {
            select = menu();
            if (select != 0 && select != 7 && m_fileName == nullptr) // change the selection to 7 if filename is null
                select = 7;

            switch (select)
            {
            case 0:
                exit();
                break;
            case 1:
                list();
                break;
            case 2:
                add();
                break;
            case 3:
                remove();
                break;
            case 4:
                update();
                break;
            case 5:
                sort();
                break;
            case 6:
                ship();
                break;
            case 7:
                load();
                break;
            }
        }
    }
}
