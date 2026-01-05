//
// Created by masti on 1/2/2026.
//

#include "Menu.h"
#include "Utils.h"
#include "constants.h"
#include <iomanip>

namespace seneca {

    MenuItem::MenuItem(char *content, unsigned int indentation, unsigned int indentation_size, int objects_num) {

        if (content and ut.strlen(content) > 0 and !ut.isspace(content) and indentation <= 4 and indentation_size <= 4
            and objects_num <= (int)MaximumNumberOfMenuItems) {
            m_content = new char[ut.strlen(content)+1];
            ut.strcpy(m_content,content);
            m_indentation = indentation;
            m_indentation_size = indentation_size;
            m_objects_num = objects_num;
            return;
        }
        m_content = nullptr;
        m_indentation = 0;
        m_indentation_size = 0;
        m_objects_num = 0;
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
        if (m_objects_num >= 0) {
            unsigned int spaces = m_indentation * m_indentation_size;
            for (auto i = 0u; i < spaces; ++i) ostr << ' ';
            ostr.width(2);
            ostr << std::right << m_objects_num << "- ";
        }
        const char* temp = m_content;
        while (*temp && ut.isspace(*temp)) temp++;
        ostr << temp;
        return ostr;
    }
}
