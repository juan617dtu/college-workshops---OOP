//
// Created by masti on 1/2/2026.
//

#ifndef MENU_H
#define MENU_H
#include <iostream>

#include "constants.h"

namespace seneca {

    class Menu;

    class MenuItem {

        char* m_content{};
        unsigned int m_indentation{};
        unsigned int m_indentation_size{};
        int m_row{};

        MenuItem(const char* content, unsigned int indentation, unsigned int indentation_size, int objects_num);
        ~MenuItem();
        MenuItem(const MenuItem& other) = delete;
        MenuItem& operator=(const MenuItem& other) = delete;
        operator bool() const;
        std::ostream& display(std::ostream& ostr = std::cout) const;

        friend class Menu;
    };
    class Menu {

        unsigned int m_indentation{};
        unsigned int m_indentation_size{};
        unsigned int m_menu_objects_num{};
        MenuItem m_title;
        MenuItem m_exit_opt;
        MenuItem m_sel_prompt;
        MenuItem* m_menu_items[MaximumNumberOfMenuItems];

    public:

        Menu(const char* title, const char* exit_opt = "Exit", unsigned int indent_num = 0,
            unsigned int indent_size = 3);
        Menu& operator<<(const char* content);
        Menu(const Menu& other) = delete;
        Menu& operator=(const Menu& other) = delete;
        ~Menu();
        size_t select() const;
    };
    size_t operator<<(std::ostream& ostr, const Menu& m);
}
#endif //MENU_H
