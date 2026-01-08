//
// Created by masti on 1/6/2026.
//

#ifndef BILLABLE_H
#define BILLABLE_H
#include <iostream>

namespace seneca {

    class Billable {

        char* m_name{};
        double m_price{};

    protected:

        void price(double value);
        void name(const char* name);

    public:

        Billable() = default;
        Billable(const Billable& other);
        Billable& operator=(const Billable& other);
        virtual ~Billable();
        virtual double price() const;
        virtual std::ostream& print(std::ostream& ostr=std::cout)const = 0;
        virtual bool order() = 0;
        virtual bool ordered()const = 0;
        virtual std::ifstream& read(std::ifstream& file) = 0;
        friend double operator+(double money, const Billable& B);
        friend double& operator+=(double& money, const Billable& B);
        operator const char*() const;
    };
}
#endif //BILLABLE_H
