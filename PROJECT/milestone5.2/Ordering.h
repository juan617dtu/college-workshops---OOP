#ifndef ORDERING_H
#define ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"

namespace seneca {

    class Ordering {

        unsigned int m_food_counter{};
        unsigned int m_drink_counter{};
        unsigned int m_billable_counter{};
        size_t m_bill_sn{ 1 };
        Food* m_food_arr{};
        Drink* m_drink_arr{};
        Billable* m_bill_items[MaximumNumberOfMenuItems]{};
        std::ostream& bill_title_print(std::ostream& ostr) const;
        std::ostream& print_totals(std::ostream& ostr, double total_amount) const;
        size_t countRecords(const char* file) const;

    public:

        Ordering(const char* drinks_file, const char* foods_file);
        ~Ordering();
        operator bool() const;
        unsigned int noOfBillItems() const;
        bool hasUnsavedBill() const;
        void listFoods() const;
        void listDrinks() const;
        void orderFood();
        void orderDrink();
        std::ostream& printBill(std::ostream& ostr) const;
        void resetBill();
    };
}
#endif //ORDERING_H

