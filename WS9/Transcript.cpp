//
// Created by masti on 11/21/2025.
//

#include "Transcript.h"

#include "Utils.h"

namespace seneca {

    Transcript::Transcript(char *name, unsigned int number) {

        if (name) {
            m_student_name = new char[ut.strlen(name) + 1];
            ut.strcpy(m_student_name, name);
        }
        else { m_student_name = nullptr; }

        m_student_id = number;
    }
    Transcript::Transcript(const Transcript &other) : Marks(other) {

        if (other.m_student_name) {
            m_student_name = new char[ut.strlen(other.m_student_name) + 1];
            ut.strcpy(m_student_name, other.m_student_name);
        }
        else { m_student_name = nullptr; }

        m_student_id = other.m_student_id;
    }
    Transcript &Transcript::operator=(const Transcript &other) {

        if (this != &other) {
            Marks::operator=(other);
            delete[] m_student_name;
            if (other.m_student_name) {
                m_student_name = new char[ut.strlen(other.m_student_name) + 1];
                ut.strcpy(m_student_name, other.m_student_name);
            }
            else { m_student_name = nullptr; }

            m_student_id = other.m_student_id;
        }
        return *this;
    }
    Transcript::~Transcript() {

        delete[] m_student_name;
        m_student_name = nullptr;
        //Marks::~Marks() C++ automatically calls the base class destructor after the derived one finishes.
    }
    std::ostream &Transcript::display(std::ostream &ostr) const {

        ostr << m_student_name << " (" << m_student_id << ")\n"
        << "--------------------------------------------------------------------------\n";
        Marks::display(ostr);
        return ostr;
    }
}
