//
// Created by masti on 1/6/2026.
//

#ifndef FOOD_H
#define FOOD_H
#include "Billable.h"

namespace seneca {

    class Food : public Billable {

        bool m_ordered{};
        bool m_child{};
        char* m_customize{};

    public:

        Food() = default;
        ~Food();
        Food(const Food& other);
        Food& operator=(const Food& other);
        std::ostream &print(std::ostream &ostr = std::cout) const override;
        bool order() override;
        bool ordered()const override;
        std::ifstream& read(std::ifstream& file) override;
        double price() const override;
    };
}

#endif //FOOD_H
