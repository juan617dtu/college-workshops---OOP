//
// Created by masti on 1/8/2026.
//

#include "Ordering.h"
#include "Menu.h"
#include "Utils.h"
#include <iomanip>
#include <fstream>

namespace seneca {

    std::ostream &Ordering::bill_title_print(std::ostream &ostr) const {

        ostr << "Bill # " << std::setw(3) << std::setfill('0') << m_bill_sn << " =============================\n";
        return ostr;
    }
    std::ostream &Ordering::print_totals(std::ostream &ostr, double total_amount) const {

        const double tax = total_amount * Tax;
        const double total = total_amount + tax;
        ostr << std::fixed << std::setprecision(2) << std::right << std::setw(27)
        << "Total:" << std::setw(13) << total_amount << "\n";
        ostr << std::setw(25) << "Tax:" << std::setw(15) << tax << "\n";
        ostr << std::setw(31) << "Total+Tax:" << std::setw(9) << total << "\n";
        ostr << "========================================\n";
        return ostr;
    }
    size_t Ordering::countRecords(const char *file) const {

        size_t new_line_counter = 0;
        std::ifstream data(file);
        int ch;
        while ((ch = data.get()) != EOF) {
            if (ch == '\n') new_line_counter++;
        }
        return new_line_counter;
    }
    Ordering::Ordering(const char *drinks_file, const char *foods_file) {

        size_t drinks_size = countRecords(drinks_file);
        size_t foods_size = countRecords(foods_file);
        std::ifstream drinks_data(drinks_file);
        std::ifstream foods_data(foods_file);
        int food_reads = 0u;
        int drinks_reads = 0u;
        if (drinks_data.is_open() and foods_data.is_open()) {
            m_food_arr = new Food[foods_size];
            m_drink_arr = new Drink[drinks_size];
            for (size_t i = 0; i < drinks_size and drinks_data; ++i) {
                if (m_drink_arr[i].read(drinks_data)) drinks_reads++;
            }
            for (size_t i = 0; i < foods_size and foods_data; ++i) {
                if (m_food_arr[i].read(foods_data)) food_reads++;
            }
        }
        if (drinks_reads != drinks_size or food_reads != foods_size) {
            delete [] m_drink_arr;
            delete [] m_food_arr;
            m_drink_arr = nullptr;
            m_food_arr = nullptr;
        }
        else {
            m_drink_counter = drinks_reads;
            m_food_counter = food_reads;
        }
    }
    Ordering::~Ordering() {

        delete[] m_food_arr;
        delete[] m_drink_arr;
        for (size_t i = 0; i < m_billable_counter; ++i) delete m_bill_items[i];
    }
    Ordering::operator bool() const {

        return m_food_arr and m_drink_arr;
    }
    unsigned int Ordering::noOfBillItems() const {

        return m_billable_counter;
    }
    bool Ordering::hasUnsavedBill() const {

        return m_billable_counter > 0;
    }
    void Ordering::listFoods() const {

        std::cout << "List Of Avaiable Meals\n========================================\n";
        for (size_t i = 0; i < m_food_counter; ++i) {
            m_food_arr[i].print();
            std::cout << "\n";
        }
        std::cout << "========================================\n";
    }
    void Ordering::listDrinks() const {

        std::cout << "List Of Avaiable Drinks\n========================================\n";
        for (size_t i = 0; i < m_drink_counter; ++i) {
            m_drink_arr[i].print();
            std::cout << "\n";
        }
        std::cout << "========================================\n";
    }
    void Ordering::orderFood() {

        Menu food_menu("Food Menu", "Back to Order", 2);
        for (size_t i = 0; i < m_food_counter; ++i) food_menu << m_food_arr[i];
        size_t selection = food_menu.select();
        if (selection != 0) {
            Food* selected_food_item = new Food(m_food_arr[selection - 1]);
            m_bill_items[m_billable_counter] = selected_food_item;
            if (m_bill_items[m_billable_counter]->order()) ++m_billable_counter;
            else delete selected_food_item;
        }
    }
    void Ordering::orderDrink() {

        Menu drink_menu("Drink Menu", "Back to Order", 2);
        for (size_t i = 0; i < m_drink_counter; ++i) drink_menu << m_drink_arr[i];
        size_t selection = drink_menu.select();
        if (selection != 0) {
            Drink* selected_drink_item = new Drink(m_drink_arr[selection - 1]);
            m_bill_items[m_billable_counter] = selected_drink_item;
            if (m_bill_items[m_billable_counter]->order()) ++m_billable_counter;
            else delete selected_drink_item;
        }
    }
    std::ostream &Ordering::printBill(std::ostream &ostr) const {
        double total_price{};
        bill_title_print(ostr);
        for (size_t i = 0; i < m_billable_counter; ++i) {
            m_bill_items[i]->print(ostr) << '\n';
            total_price += m_bill_items[i]->price();
        }
        print_totals(ostr, total_price);
        return ostr;
    }
    void Ordering::resetBill() {

        char bill[50];
        ut.makeBillFileName(bill, m_bill_sn);
        std::ofstream bill_file(bill);
        printBill(bill_file);
        std::cout << "Saved bill number " << m_bill_sn << '\n';
        std::cout << "Starting bill number " << ++m_bill_sn << '\n';
        for (size_t i = 0; i < m_billable_counter; ++i) delete m_bill_items[i];
        m_bill_sn++;
        m_billable_counter = 0;
    }
}