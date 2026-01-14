//
// Created by masti on 1/6/2026.
//

#ifndef DRINK_H
#define DRINK_H
#include "Billable.h"

namespace seneca {

    class Drink : public Billable {

        char m_size{};

    public:

        Drink();
        std::ostream& print(std::ostream& ostr=std::cout)const override;
        bool order() override;
        bool ordered()const override;
        std::ifstream& read(std::ifstream& file) override;
        double price() const override;
    };
}
#endif //DRINK_H
