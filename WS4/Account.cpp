
#include <iostream>
#include "Account.h"

#include <iomanip>
#include <string.h>

using namespace std;

namespace seneca {

    void Account::cpyName(const char* src) {
      int i;
      for (i = 0; src && src[i] && i < NameMaxLen; i++) {
         m_holderName[i] = src[i];
      }
      m_holderName[i] = char(0);
   }
   bool Account::isValidNumber(int number) const {
      return number >= 10000 && number <= 99999;
   }
   Account::Account(const char* holderName) {
      m_holderName[0] = char(0);
      m_number = -1;
      m_balance = 0.0;
      if (holderName && holderName[0]) {
         cpyName(holderName);
         m_number = 0;
      }
   }
   Account::Account(const char* holderName, int number, double balance ) {
      m_holderName[0] = char(0);
      m_number = -1;
      m_balance = 0.0;
      if (holderName && holderName[0] && isValidNumber(number) && balance > 0) {
         cpyName(holderName);
         m_number = number;
         m_balance = balance;
      }
   }
   std::ostream& Account::display() const{

      if (*this) {
         cout << " ";
         cout.fill(' ');
         cout.width(NameMaxLen);
         cout.setf(ios::left);
         cout << m_holderName;
         cout.unsetf(ios::left);
         cout << " | ";
         cout << m_number;
         cout << " | ";
         cout.width(12);
         cout.precision(2);
         cout.setf(ios::right);
         cout.setf(ios::fixed);
         cout << m_balance;
         cout.unsetf(ios::right);
         cout << " ";
      }
      else if(~*this) {
         cout << " ";
         cout.fill(' ');
         cout.width(30);
         cout.setf(ios::left);
         cout << m_holderName;
         cout.unsetf(ios::left);
         cout << " |  NEW  |         0.00 ";
      }
      else {
         cout << " Bad Account                    | ----- | ------------ ";
      }
      return cout;
   }
   Account::operator bool() const {

       return isValidNumber(m_number) && m_balance >= 0 && m_holderName[0] != '\0';
   }
   Account::operator int() const {

       return m_number;
   }
   Account::operator double() const {

       return m_balance;
   }
   Account::operator const char *() const {

      return m_holderName;
   }
   char &Account::operator[](int index) {

       int len = static_cast<int>(strlen(m_holderName));

       if (len == 0) return m_holderName[0];

       if (index < 0) index = 0;
       else index %= len;

       return m_holderName[index];
   }
   const char Account::operator[](int index) const {

       index %= NameMaxLen;

       return m_holderName[index];
   }
   Account &Account::operator=(int new_account) {

       if (m_number == 0) {

          if (isValidNumber(new_account)) m_number = new_account;
          else m_number = -1;
       }
       return *this;
   }
   Account &Account::operator=(double account_balance) {

       if (account_balance > 0) m_balance = account_balance;
       else m_balance = 0.0;

       return *this;
   }
   Account &Account::operator+=(double deposit) {

       if (deposit > 0) m_balance += deposit;

       return *this;
   }
   Account &Account::operator-=(double withdrawal) {

       if (withdrawal > 0 && withdrawal <= m_balance) m_balance -= withdrawal;

       return *this;
   }
   Account &Account::operator<<(Account &right) {

       if (this != &right) {

          bool valid_left = (isValidNumber(m_number) && m_balance >= 0 && m_holderName[0] != '\0');
          bool valid_right = (isValidNumber(right.m_number) && right.m_balance >= 0 && right.m_holderName[0] != '\0');

          if (valid_left && valid_right) {

             m_balance += right.m_balance;
             right.m_balance = 0.0;
          }
       }
       return *this;
   }
   Account &Account::operator>>(Account &left) {

       if (this != &left) {

          bool valid_left = (isValidNumber(left.m_number) && left.m_balance >= 0 && left.m_holderName[0] != '\0');
          bool valid_right = (isValidNumber(m_number) && m_balance >= 0 && m_holderName[0] != '\0');

          if (valid_left && valid_right) {

             left.m_balance += m_balance;
             m_balance = 0.0;
          }
       }
       return *this;
   }
   bool Account::operator~() const {

       if (m_number == 0) return true;

       return false;
   }
   Account &Account::operator++() {

       if (isValidNumber(m_number) && m_balance > 0 && m_holderName[0] != '\0') m_balance += 1.0;

       return *this;
   }
   Account Account::operator++(int) {

       Account back_up = *this;

       if (isValidNumber(m_number) && m_balance > 0 && m_holderName[0] != '\0') m_balance += 1.0;

       return back_up;
   }
   Account &Account::operator--() {

       if (isValidNumber(m_number) && m_balance > 0 && m_holderName[0] != '\0') m_balance -= 1.0;

       return *this;
   }
    Account Account::operator--(int) {

        Account back_up = *this;

        if (isValidNumber(m_number) && m_balance > 0 && m_holderName[0] != '\0') m_balance -= 1.0;

       return back_up;
    }
}


