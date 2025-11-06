//
// Created by masti on 11/4/2025.
//

#ifndef PROFESSOR_H
#define PROFESSOR_H
#include "Employee.h"

namespace seneca {

    class Professor : public Employee {

        char* m_subject_name{};
        int m_sections_number{};

    public:

        Professor();
        Professor(const char* name, const char* subject_name, int sections_num, size_t employee_num, double salary);
        ~Professor();
        double devPay() const;
        std::istream& read(std::istream& istr = std::cin);
        std::ostream& write(std::ostream& ostr = std::cout) const;
        std::ostream& title(std::ostream& ostr = std::cout) const;
    };
    std::ostream& operator<<( std::ostream& ostr, const Professor& P );
    std::istream& operator>>( std::istream& istr, Professor& P );
}
#endif //PROFESSOR_H
