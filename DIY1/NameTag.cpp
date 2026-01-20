//
// Created by masti on 1/19/2026.
//

#include "NameTag.h"
#include <iostream>

namespace seneca {

    std::size_t NameTag::name_length() const {

        std::size_t i = 0;
        while (m_name[i] != '\0' and i < 50) ++i;
        return i;
    }

    void NameTag::set(const char *name) {

        std::size_t i = 0;
        for (; name[i] != '\0' and i < 50; ++i) m_name[i] = name[i];
        m_name[i] = '\0';
    }
    void NameTag::set_frame_width(unsigned int width_frame) {

        m_frame = width_frame;
    }
    void NameTag::print() const {

        if (!m_name[0]) return;
        unsigned int width = m_frame;
        if (width == 0) width = name_length() + 4;
        unsigned int spaces = width - (name_length() + 4);
        for (int i = 0u; i < width; ++i) std::cout << '*';
        std::cout << "\n* " << std::left << m_name;
        for (int i = 0u; i < spaces; ++i) std::cout << ' ';
        std::cout << " *\n";
        for (int i = 0u; i < width; ++i) std::cout << '*';
        std::cout << '\n';
    }
}
