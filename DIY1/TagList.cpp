#include "TagList.h"

namespace seneca {

    TagList::TagList(int num) {

        if (num > 0) {
            m_tag_list = new NameTag[num];
            m_max_capacity = num;
        }
    }
    void TagList::add(const NameTag &nt) {

        if (m_added_tags < m_max_capacity) {
            m_tag_list[m_added_tags] = nt;
            ++m_added_tags;
        }
    }
    void TagList::print() {

        if (m_added_tags == 0) return;
        size_t longest_name = 0;
        for (std::size_t i = 0; i < m_added_tags; ++i) {
            if (m_tag_list[i].name_length() > longest_name ) longest_name = m_tag_list[i].name_length();
        }
        unsigned int frame = longest_name + 4;
        for (std::size_t i = 0; i < m_added_tags; ++i) m_tag_list[i].set_frame_width(frame);
        for (std::size_t i = 0; i < m_added_tags; ++i) m_tag_list[i].print();
    }
    TagList::~TagList() {

        delete[] m_tag_list;
        m_tag_list = nullptr;
    }
}

