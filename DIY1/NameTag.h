//
// Created by masti on 1/19/2026.
//

#ifndef NAMETAG_H
#define NAMETAG_H
#include <cstddef>

namespace seneca {

    class NameTag {

        char m_name[51]{};
        unsigned int m_frame{};

    public:

        void set(const char* name);
        void set_frame_width(unsigned int frame_width);
        std::size_t name_length() const;
        void print() const;
    };
}
#endif //NAMETAG_H
