#ifndef CC_H
#define CC_H

namespace seneca {

    class CC {

        char* carholders_name{};
        short cvv{}, expiry_month{}, expiry_year{};
        unsigned long long credit_card_number{};
        void aloCopy(const char* name);
        void deallocate();
        void display(const char* name, unsigned long long number, short expYear, short expMon, short cvv) const;
        bool validate(const char* name, unsigned long long cardNo, short cvv, short expMon, short expYear) const;
        void prnNumber(unsigned long long no) const;

    public:

        void set();
        bool isEmpty() const;
        void set(const char* cc_name, unsigned long long cc_no, short cvv, short expMon, short expYear);
        void display() const;
        CC();
        CC(const char* name, unsigned long long cardNo, short cvv, short expMon = 12, short expYear = 26);
        ~CC();
    };
}
#endif //CC_H
