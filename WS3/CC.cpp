#include "CC.h"
#include "cstr.h"
#include <iostream>
using namespace std;

namespace seneca {

    void CC::aloCopy(const char* name) {
        deallocate();
        if (name) {
            size_t len = strlen(name);
            carholders_name = new char[len + 1];
            strcpy(carholders_name, name);
        }
    }
    void CC::deallocate() {

        delete[] carholders_name;
        carholders_name = nullptr;
    }
    void CC::display(const char* name, unsigned long long number, short expYear, short expMon, short cvv) const{

        char lname[31]{};
        strcpy(lname, name, 30); // declared in "cstr.h"
        cout << "| ";
        cout.width(30);
        cout.fill(' ');
        cout.setf(ios::left);
        cout << lname << " | ";
        prnNumber(number);
        cout << " | " << cvv << " | ";
        cout.unsetf(ios::left);
        cout.setf(ios::right);
        cout.width(2);
        cout << expMon << "/" << expYear << " |" << endl;
        cout.unsetf(ios::right);
    }
    bool CC::validate(const char *name, unsigned long long cardNo, short cvv, short expMon, short expYear) const {

        if (name != nullptr && strlen(name) > 2 && cardNo >= 4000000000000000ull && cardNo <= 4099999999999999ull
            && cvv >= 100 && cvv <= 999 && expMon >= 1 && expMon <= 12 && expYear >= 24 && expYear <= 32) {
            return true;
        }
        return false;
    }
    void CC::prnNumber(unsigned long long no) const {

        cout << no / 1000000000000ull << " ";
        no %= 1000000000000ull;
        cout.fill('0');
        cout.width(4);
        cout.setf(ios::right);
        cout << no / 100000000ull << " ";
        no %= 100000000ull;
        cout.width(4);
        cout << no / 10000ull << " ";
        no %= 10000ull;
        cout.width(4);
        cout << no;
        cout.unsetf(ios::right);
        cout.fill(' ');
    }
    void CC::set() {

        carholders_name = nullptr;
        credit_card_number = 0;
        cvv = 0;
        expiry_month = 0;
        expiry_year = 0;
    }
     bool CC::isEmpty() const {

        if (carholders_name == nullptr) return true;

        return false;
    }
    void CC::set(const char *cc_name, unsigned long long cc_no, short cvv, short expMon, short expYear) {

        set();

        if (validate(cc_name, cc_no, cvv, expMon, expYear)) {

            aloCopy(cc_name);
            credit_card_number = cc_no;
            this->cvv = cvv;
            expiry_month = expMon;
            expiry_year = expYear;
        }
    }
    void CC::display() const {

        if (isEmpty()) cout << "Invalid Credit Card Record\n";
        else display(carholders_name, credit_card_number, expiry_year, expiry_month, cvv);
    }
    CC::CC() {

        set();
    }
    CC::CC(const char *name, unsigned long long cardNo, short cvv, short expMon, short expYear) {

        set();

        if (validate(name, cardNo, cvv, expMon, expYear)) {

            aloCopy(name);
            credit_card_number = cardNo;
            this->cvv = cvv;
            expiry_month = expMon;
            expiry_year = expYear;
        }
    }
    CC::~CC() {

        deallocate();
    }
}
