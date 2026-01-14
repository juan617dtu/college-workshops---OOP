#include "Line.h"
//#include "Utils.h"

namespace seneca {

    //Line::Line() : LblShape(), m_length(0) {}

    Line::Line(const char *label, int length) : LblShape(label) {

        if (m_length < length) m_length = length;
    }
    void Line::draw(std::ostream& os) const {

        if (m_length > 0 && label() != nullptr) {
            os << label() << std::endl;
            for (size_t i = 0; i < m_length; ++i) os << '=';
        }
    }
    void Line::getSpecs(std::istream& is) {

        LblShape::getSpecs(is);
        is >> m_length;
        is.ignore(1000, '\n');
    }
}
