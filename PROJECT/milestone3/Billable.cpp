#include "Billable.h"
#include "Utils.h"

namespace seneca {

    void Billable::price(double value) {

        m_price = value;
    }
    void Billable::name(const char *name) {

        delete[] m_name;
        m_name = nullptr;
        if (name) m_name = ut.alocpy(name);
    }
    Billable::Billable(const Billable &other) {

        m_name = nullptr;
        m_price = other.m_price;
        name(other.m_name);
    }
    Billable& Billable::operator=(const Billable &other) {

        if (this != &other) {
            delete[] m_name;
            m_name = nullptr;
            m_price = other.m_price;
            if (other.m_name) {
                m_name = new char[ut.strlen(other.m_name) + 1];
                ut.strcpy(m_name, other.m_name);
            }
        }
        return *this;
    }
    Billable::~Billable() {

        delete[] m_name;
        m_name = nullptr;
    }
    double Billable::price() const {

        return m_price;
    }
    double operator+(double money, const Billable &B) {

        return money + B.price();
    }
    double& operator+=(double &money, const Billable &B) {

        money += B.price();
        return money;
    }
    Billable::operator const char *() const {

        return m_name;
    }
}

