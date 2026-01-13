#include "Professor.h"

#include <iomanip>

#include "Utils.h"

namespace seneca {
    Professor::Professor() {

        m_subject_name = nullptr;
        m_sections_number = 0;
    }
    Professor::Professor(const char *name, const char *subject_name, int sections_num, size_t employee_num, double salary) {

        Employee(name, employee_num, salary);
        m_subject_name = ut.alocpy(subject_name);
        m_sections_number = sections_num;
    }
    Professor::~Professor() {

        delete[] m_subject_name;
    }
    double Professor::devPay() const {

        return salary() / 100 * m_sections_number;
    }
    std::istream& Professor::read(std::istream& istr) {

        if (istr.peek() == '\n') istr.ignore();
        Employee::read(istr);
        if (!istr) return istr;
        istr.ignore();

        char line[1024];
        istr.getline(line, 1024, ',');
        delete[] m_subject_name;
        m_subject_name = ut.alocpy(line);
        istr >> std::ws >> m_sections_number;
        if (!istr) return istr;
        return istr;
    }
    std::ostream& Professor::write(std::ostream& ostr) const {

        Employee::write(ostr);
        ostr << " " << std::setw(20);
        ostr.setf(std::ios::left);
        if (m_subject_name) {
            char buffer[21]{};
            ut.strcpy(buffer, m_subject_name, 20);
            ostr << buffer;
        }
        ostr.unsetf(std::ios::left);
        ostr << " | " << std::setw(5);
        ostr.setf(std::ios::right);
        ostr << m_sections_number << " | "
        << std::setw(8) << std::fixed << std::setprecision(2) << devPay() << " |";
        ostr.unsetf(std::ios::right);

        return ostr;
    }
    std::ostream& Professor::title(std::ostream& ostr) const {

        Employee::title(ostr);
        ostr << " Teaching Subject     | Sec # | $Dev Pay |";
        return ostr;
    }
    std::ostream& operator<<(std::ostream& ostr, const Professor& P ) {
        return P.write( ostr );
    }
    std::istream& operator>>( std::istream& istr, Professor& P ) {
        return P.read( istr );
    }
}
