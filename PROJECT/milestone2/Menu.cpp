#include "Menu.h"
#include "Utils.h"
#include "constants.h"
#include <iomanip>

namespace seneca {

    MenuItem::MenuItem(const char *content, unsigned int indentation, unsigned int indentation_size, int objects_num) {

        if (content and ut.strlen(content) > 0 and !ut.isspace(content) and indentation <= 4 and indentation_size <= 4
            and objects_num <= (int)MaximumNumberOfMenuItems) {
            m_content = new char[ut.strlen(content)+1];
            ut.strcpy(m_content,content);
            m_indentation = indentation;
            m_indentation_size = indentation_size;
            m_row = objects_num;
            return;
        }
        m_content = nullptr;
        m_indentation = 0;
        m_indentation_size = 0;
        m_row = 0;
    }
    MenuItem::~MenuItem() {

        delete [] m_content;
        m_content = nullptr;
    }
    /*MenuItem::MenuItem(const MenuItem &other) {

        *this = other;
    }
    MenuItem& MenuItem::operator=(const MenuItem& other) {

        if (this != &other) {
            delete [] m_content;
            m_content = nullptr;
            m_indentation = other.m_indentation;
            m_indentation_size = other.m_indentation_size;
            m_objects_num = other.m_objects_num;
            if (other.m_content) {
                m_content = new char[ut.strlen(other.m_content)+1];
                ut.strcpy(m_content,other.m_content);
            }
        }
        return *this;
    }*/
    MenuItem::operator bool() const {

        if (m_content == nullptr) return false;
        return true;
    }
    std::ostream &MenuItem::display(std::ostream &ostr) const {

        if (!m_content) {
            ostr << "??????????";
            return ostr;
        }
        unsigned int spaces = m_indentation * m_indentation_size;
        for (auto i = 0u; i < spaces; ++i) ostr << ' ';
        if (m_row >= 0) {
            ostr.width(2);
            ostr << std::right << m_row << "- ";
        }
        const char* temp = m_content;
        while (*temp && ut.isspace(*temp)) temp++;
        ostr << temp;
        return ostr;
    }
    Menu::Menu(const char *title, const char *exit_opt, unsigned int num, unsigned int size) :
    m_indentation(num), m_indentation_size(size),
    m_title(title, num, size, -1),
    m_exit_opt(exit_opt, num, size, 0),
    m_sel_prompt("> ", num, size, -1)
    {
        for (auto & i : m_menu_items) i = nullptr;
    }
    Menu &Menu::operator<<(const char *content) {

        if (m_menu_objects_num < MaximumNumberOfMenuItems) {
            m_menu_items[m_menu_objects_num] =
                new MenuItem(content, m_indentation, m_indentation_size,
                    static_cast<int>(m_menu_objects_num + 1));
            ++m_menu_objects_num;
        }
        return *this;
    }
    Menu::~Menu() {

        for (auto & i : m_menu_items) {
            delete i;
            i = nullptr;
        }
    }
    size_t Menu::select() const {

        if (m_title) m_title.display() << '\n';
        for (size_t i = 0; i < m_menu_objects_num; ++i) {
            if (m_menu_items[i]) m_menu_items[i]->display() << '\n';
        }
        m_exit_opt.display() << '\n';
        m_sel_prompt.display();
        int choice = ut.getInt(0, static_cast<int>(m_menu_objects_num));
        return static_cast<size_t>(choice);
    }
    size_t operator<<(std::ostream &ostr, const Menu &m) {

        if (&ostr == &std::cout) return m.select();
        return 0;
    }
}

