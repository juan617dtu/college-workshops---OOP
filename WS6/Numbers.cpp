//
// Created by masti on 10/27/2025.
//
#include "Numbers.h"
#include <fstream>

namespace seneca {

    Numbers::~Numbers() {

        save();
        delete[] m_numbers;
        m_numbers = nullptr;
        delete[] m_filename;
        m_filename = nullptr;
    }
    Numbers::Numbers(const Numbers& obj) {

        m_numbers = nullptr;
        m_filename = nullptr;
        m_numCount = 0;
        m_isOriginal = false;

        if (obj.m_numbers != nullptr && obj.m_numCount > 0) {

            m_numbers = new double[obj.m_numCount];

            for (size_t i = 0; i < obj.m_numCount; ++i) m_numbers[i] = obj.m_numbers[i];

            m_numCount = obj.m_numCount;
        }
    }
    Numbers &Numbers::operator=(const Numbers &other) {

        if (this != &other) {

            delete[] m_numbers;

            m_numbers = new double[other.m_numCount];

            for (size_t i = 0; i < other.m_numCount; ++i) m_numbers[i] = other.m_numbers[i];

            m_numCount = other.m_numCount;
        }
        return *this;
    }
    int Numbers::numberCount() const {

        std::ifstream file(m_filename);

        char ch; int new_lines = 0;

        while (file.get(ch)) if (ch == '\n') new_lines++;

        return new_lines;
    }
    bool Numbers::load() {

        size_t i = 0;

        if (m_numCount > 0) {

            m_numbers = new double[m_numCount];
            std::ifstream file(m_filename);
            if (!file) return false;
            while (i < m_numCount && file >> m_numbers[i]) i++;
        }
        return i == m_numCount;
    }
    bool Numbers::save() const{

        if (m_isOriginal && m_numbers != nullptr && m_numCount > 0) {

            std::ofstream file(m_filename);

            if (!file) return false;

            for (size_t i = 0; i < m_numCount; ++i) file << m_numbers[i] << std::endl;

            return true;
        }
        return false;
    }
    Numbers &Numbers::operator+=(double value) {

        if (!isEmpty()) {

            double *temp = new double[m_numCount + 1];
            for (size_t i = 0; i < m_numCount; ++i) temp[i] = m_numbers[i];
            temp[m_numCount++] = value;
            delete[] m_numbers;
            m_numbers = temp;
            sort();
        }
        return *this;
    }
    std::ostream& Numbers::display(std::ostream& ostr) const {

        if (isEmpty()) ostr << "Empty list";
        else {
            ostr.precision(2);
            ostr.setf(std::ios::fixed);
            ostr << "=========================\n";

            if (m_isOriginal) ostr << m_filename << std::endl;
            else ostr << "*** COPY ***\n";

            for (size_t i = 0; i < m_numCount; ++i) {
                ostr << m_numbers[i];
                if (i < m_numCount-1) ostr << ", ";
            }
            ostr << std::endl << "-------------------------\n";
            ostr << "Total of " << m_numCount << " number(s)\n";
            ostr << "Largest number: " << m_numbers[m_numCount-1] << std::endl;
            ostr << "Smallest number: " << m_numbers[0] << std::endl;
            double sum = 0;
            for (size_t i = 0; i < m_numCount; ++i) sum += m_numbers[i];
            ostr << "Average: " << sum / m_numCount << std::endl;
            ostr << "=========================";
        }
        return ostr;
    }
    std::ostream& operator<<(std::ostream& ostr, const Numbers& N) {

        return N.display(ostr);
    }
    std::istream &operator>>(std::istream &istr, Numbers &N) {

        double value;
        istr >> value;
        if (!istr.fail()) N += value;
        return istr;
    }
}
