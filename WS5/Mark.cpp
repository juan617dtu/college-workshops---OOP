//
// Created by masti on 10/22/2025.
//
/***********************************************************************/
#include <iostream>
#include <cmath> // for round function
#include "Mark.h"

#include <iomanip>
using namespace std;
namespace seneca {
   bool Mark::isValid()const {
      return  (m_value >= 0 && m_value <= 100);
   }
   Mark::Mark(int value, char type) {
      *this = type;
      m_value = double(value);
   }

   Mark::Mark(double value) {
      m_type = MARK;
      m_value = value;
   }

   Mark& Mark::operator+=(const Mark& M) {
      m_value += M.m_value;
      return *this;
   }

   Mark& Mark::operator-=(const Mark& M) {
      m_value -= M.m_value;
      return *this;
   }

   Mark Mark::operator+(const Mark& M) const {
      return Mark(*this) += M;
   }

   Mark Mark::operator-(const Mark& M)const {
      return Mark(*this) -= M;
   }

   Mark& Mark::operator/=(int other) {
      m_value = m_value / other;
      return *this;
   }

   Mark Mark::operator/(int other) const {
      return Mark(m_value / other);
   }

   Mark& Mark::operator=(int value) {
      m_value = value;
      return *this;
   }

   Mark& Mark::operator=(char type) {
      m_type = MARK;
      if (type == GRADE || type == GPA) {
         m_type = type;
      }
      return *this;
   }

   double Mark::raw() const {
      return m_value;
   }

   Mark::operator int() const {
      int value = -1;
      if (isValid()) {
         value = int(std::round(m_value < 0 ? 0 : m_value));
      }
      return value;
   }
   Mark::operator bool() const {
      return isValid();
   }


   // returns the GPA not the m_value!!!
   Mark::operator double() const {
      double gpa = 0;
      if (!isValid()) gpa = -1;
      else gpa = m_value * 0.04;
      return gpa;
   }

   Mark::operator const char* () const {
      // removes the constantness of m_grade!
      // You will learn this at the end of the semester.
      char* grade = const_cast<char*>(m_grade);

      int value = int(*this);
      grade[1] = grade[2] = '\0';
      if (value < 0 || value > 100) grade[0] = 'X';
      else if (value >= 90) grade[0] = 'A', grade[1] = '+';
      else if (value >= 80) grade[0] = 'A';
      else if (value >= 75) grade[0] = 'B', grade[1] = '+';
      else if (value >= 70) grade[0] = 'B';
      else if (value >= 65) grade[0] = 'C', grade[1] = '+';
      else if (value >= 60) grade[0] = 'C';
      else if (value >= 55) grade[0] = 'D', grade[1] = '+';
      else if (value >= 50) grade[0] = 'D';
      else grade[0] = 'F';
      return m_grade;
   }

   // student helper function implementations go here
   std::ostream& Mark::display(std::ostream& os) const {

      if (!isValid()) {

         if (m_type == GRADE) os << "**";
         else os << "***";
      }
      else {

         if (m_type == GPA) os << right << fixed << setprecision(1) << setw(3) << double(*this);

         else if (m_type == MARK) {

            os.fill('_');
            os << right << setw(3) << int(*this);
         }
         else if (m_type == GRADE) {

            os.fill(' ');
            os << left << setw(3) << (const char*)(*this);
         }
         else os << "***";
      }
      return os;
   }
   std::ostream &display(const Mark &mark, char display_type, std::ostream &os) {

      Mark temp = mark;
      temp.display(os);
      if (display_type != MARK) {
         os << ": ";
         temp = display_type;
         temp.display(os);
      }
      return os;
   }
   std::ostream &operator<<(std::ostream &os, const Mark &mark) {

      return mark.display(os);
   }
   std::istream &operator>>(std::istream &is, Mark &mark) {

      int value;
      bool valid =  false;

      while (!valid) {

         if (!(is >> value)) {

            cout << "Invalid integer, try again.\n> ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
         }
         char next_char = is.peek();
         if (next_char != '\n' && next_char != EOF) {

            cout << "Invalid trailing characters. Please enter only an integer.\n> ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
         }
         if (value < 0 || value > 100) {

            cout << "Invalid mark. Enter a value between 0 and 100.\n> ";
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
         }
         valid = true;
      }
      mark = value;
      return is;
   }
   std::ifstream& operator>>(std::ifstream &is, Mark &mark) {

      int value;
      char type, comma;

      if (is >> value >> comma >> type) {

         if (comma == ',') mark = Mark(value, type);
      }
      return is;
   }
   double operator+(double value, const Mark &mark) {

      return value + mark.raw();
   }
   int operator+(int value, const Mark &mark) {

      return value + int(mark);
   }
   double operator-(double value, const Mark &mark) {

      return value - mark.raw();
   }
   int operator-(int value, const Mark &mark) {

      return value - int(mark);
   }
   double operator/(double value, Mark &mark) {

      return value / mark.m_value;
   }
   int operator/(int value, Mark &mark) {

      return value / (int)mark.m_value;
   }

}