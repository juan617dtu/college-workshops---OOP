//
// Created by masti on 1/6/2026.
//

#include "Food.h"
#include "Utils.h"
#include "Menu.h"
#include <iomanip>
#include <fstream>

namespace seneca {

    Food::Food(const Food &other) {

        *this = other;
    }
    Food& Food::operator=(const Food &other) {

        if (this != &other) {
            delete[] m_customize;
            m_customize = nullptr;
            m_ordered = other.m_ordered;
            m_child =  other.m_child;
            Billable::operator=(other);
            if (other.m_customize) {
                m_customize = new char[ut.strlen(other.m_customize) + 1];
                ut.strcpy(m_customize, other.m_customize);
            }
        }
        return *this;
    }
    bool Food::order() {

        Menu menu("Food Size Selection", "Back", 3);
        menu << "Adult" << "Child";
        int selection = menu.select();
        if (selection != 0) {
            m_child = selection == 2;
            m_ordered = true;
            std::cout << "Special instructions\n> ";
            char input[1024];
            std::cin.getline(input, 1024);
            if (ut.isspace(input)) {
                delete [] m_customize;
                m_customize = nullptr;
            }
            else ut.alocpy(m_customize, input);
        }
        else {
            m_ordered = false;
            delete [] m_customize;
            m_customize = nullptr;
        }
        return m_ordered;
    }
    bool Food::ordered() const {

        return m_ordered;
    }
    double Food::price() const {

        if (m_ordered and m_child) return Billable::price() * 0.5;
        return Billable::price();
    }
    std::ostream &Food::print(std::ostream &ostr) const {

        ostr << std::setw(28) << std::left << std::setfill('.') << *this;
        if (ordered() and m_child) ostr << "Child";
        else if (ordered() and !m_child) ostr << "Adult";
        else ostr << ".....";
        ostr << std::setw(7) << std::right << std::setfill(' ') << std::fixed << std::setprecision(2) << price();
        if (m_customize && &ostr == &std::cout) {
            ostr << " >> ";
            for (size_t i = 0; i < 30 and m_customize[i] != '\0'; ++i) ostr << m_customize[i];
        }
        return ostr;
    }
    std::ifstream &Food::read(std::ifstream &file) {

        char name[100];
        double price;
        if (file.getline(name, 100, ',') and file >> price) {
            file.ignore(1000, '\n');
            Billable::name(name);
            Billable::price(price);
            m_child = false;
            m_ordered = false;
            delete[] m_customize;
            m_customize = nullptr;
        }
        return file;
    }
    Food::~Food() {

        delete[] m_customize;
        m_customize = nullptr;
    }
}
