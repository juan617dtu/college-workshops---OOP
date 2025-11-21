#include "LblShape.h"
#include "Utils.h"

namespace seneca {

    const char* LblShape::label() const {

        return m_label;
    }
    LblShape::LblShape() {
        // m_label already initialized to nullptr
    }
    LblShape::LblShape(const char *label) {

        ut.alocpy(m_label, label);
    }
    void LblShape::getSpecs(std::istream& is) {

        char temp[81]{};
        is.getline(temp, 81, ',');
        ut.alocpy(m_label, temp);
    }
    LblShape::~LblShape() {

        delete[] m_label;
        m_label = nullptr;
    }


}

