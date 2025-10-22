//
// Created by masti on 10/17/2025.
//
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>

namespace seneca {

    const int NameMaxLen = 30;
    class Account {
      double m_balance;
      int m_number;
      char m_holderName[NameMaxLen + 1];
      void cpyName(const char* src); // copies the src into the m_holderName array
      bool isValidNumber(int number)const; // returns true if number is a valid account number
   public:
        Account(const char* holderName = nullptr);
        Account(const char* holderName, int number, double balance);
        std::ostream& display()const;
        operator bool() const;
        operator int() const;
        operator double() const;
        operator const char*() const;
        char& operator[](int index);
        const char operator[](int index) const;
        Account& operator=(int new_account);
        Account& operator=(double account_balance);
        Account& operator+=(double deposit);
        Account& operator-=(double withdrawal);
        Account& operator<<(Account& right);
        Account& operator>>(Account& left);
        bool operator~() const;
        Account& operator++();  // prefix increment
        Account operator++(int); //postfix increment
        Account& operator--(); //prefix decrement
        Account operator--(int); //postfix decrement
    };
}
#endif //ACCOUNT_H
