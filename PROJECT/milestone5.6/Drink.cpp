#include "Drink.h"
#include "Menu.h"
#include <iomanip>
#include <fstream>

namespace seneca {

    Drink::Drink() : Billable() {
        m_size = '\0';
    }
    std::ostream &Drink::print(std::ostream &ostr) const {

        ostr << std::left << std::setw(28) << std::setfill('.') << *this;
        if (ordered()) {
            switch (m_size) {

                case 'S': ostr << "SML..";
                    break;
                case 'M': ostr << "MID..";
                    break;
                case 'L': ostr << "LRG..";
                    break;
                case 'X': ostr << "XLR..";
                    break;
            }
        }
        else ostr << ".....";
        ostr << std::right << std::setw(7) << std::setfill(' ') << std::fixed << std::setprecision(2) << price();
        return ostr;
    }
    bool Drink::order() {

        Menu menu("Drink Size Selection", "Back", 3);
        menu << "Small" << "Medium" << "Larg" << "Extra Large";
        size_t selection = menu.select();
        switch (selection) {
            case 1:
                m_size = 'S';
                break;
            case 2:
                m_size = 'M';
                break;
            case 3:
                m_size = 'L';
                break;
            case 4:
                m_size = 'X';
                break;
            default:
                m_size = '\0';
                return false;
        }
        return true;
    }
    bool Drink::ordered() const {

        return m_size == 'S' or m_size == 'M' or m_size == 'L' or m_size == 'X';
    }
    std::ifstream &Drink::read(std::ifstream &file) {

        char name[100];
        double price;
        if (file.getline(name, 100, ',') && file >> price) {
            file.ignore(1000, '\n');
            Billable::name(name);
            Billable::price(price);
            m_size = '\0';
        }
        return file;
    }
    double Drink::price() const {

        if (m_size == 'L' or !ordered()) return Billable::price();
        if (m_size == 'S') return Billable::price() * 0.5;
        if (m_size == 'M') return Billable::price() * 0.75;
        return Billable::price() * 1.5 ;
    }
}

