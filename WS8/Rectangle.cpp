#include "Rectangle.h"
#include "Utils.h"

namespace seneca {

    Rectangle::Rectangle() : LblShape(), m_height(0), m_width(0) {}

    Rectangle::Rectangle(const char *label, int width, int height) : LblShape(label) {

        m_width = width;
        m_height = height;
        if (m_height < 3) m_height = 3;
        if (m_width < ut.strlen(LblShape::label()) + 2) m_width = ut.strlen(LblShape::label()) + 2;
    }
    void Rectangle::getSpecs(std::istream &is) {

        LblShape::getSpecs(is);
        is >> m_width;
        is.ignore(1, ',');
        is >> m_height;
        is.ignore(1000, '\n');
    }
    void Rectangle::draw(std::ostream &os) const {

        if (m_width > 0 && m_height > 0) {
            //top border
            os << '+';
            for (size_t i = 0; i < m_width - 2; ++i) os << '-';
            os << "+\n";
            //label row
            os << '|';
            os.setf(std::ios::left);
            os.width(m_width - 2);
            os << label();
            os.unsetf(std::ios::left);
            os << "|\n";
            //middle empty rows
            for (size_t i = 0; i < m_height - 3; ++i) {
                os << '|';
                for (size_t j = 0; j < m_width - 2; ++j) os << ' ';
                os << '|' << '\n';
            }
            //bottom border
            os << '+';
            for (size_t i = 0; i < m_width - 2; ++i) os << '-';
            os << '+';
        }
    }

}
