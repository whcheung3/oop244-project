/* ------------------------------------------------------
Final Project Milestone 56
Module: Utils
Filename: Utils.h
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
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H
namespace sdds
{
    const int sdds_testYear = 2022;
    const int sdds_testMon = 03;
    const int sdds_testDay = 31;
    class Utils
    {
        bool m_testMode = false;

    public:
        void getSystemDate(int *year = nullptr, int *mon = nullptr, int *day = nullptr);
        int daysOfMon(int mon, int year) const;
        void testMode(bool testmode = true);
        void alocpy(char *&destination, const char *source);
        int getint(const char *prompt = nullptr) const;
        int getint(int min, int max, const char *prompt = nullptr, const char *errMes = nullptr) const;
        double getdouble(const char *prompt = nullptr) const;
        double getdouble(double min, double max, const char *prompt = nullptr, const char *errMes = nullptr) const;
    };
    extern Utils ut;
}

#endif // !SDDS_UTILS_H
