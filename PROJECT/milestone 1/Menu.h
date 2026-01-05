//
// Created by masti on 1/2/2026.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>

namespace seneca {

    class MenuItem {

        char* m_content{};
        unsigned int m_indentation{};
        unsigned int m_indentation_size{};
        int m_objects_num{};

    public:

        MenuItem(char* content, unsigned int indentation, unsigned int indentation_size, int objects_num);
        ~MenuItem();
        MenuItem(const MenuItem& other) = delete;
        MenuItem& operator=(const MenuItem& other) = delete;
        operator bool() const;
        std::ostream& display(std::ostream& ostr = std::cout) const;
    };
}
#endif //MENU_H
