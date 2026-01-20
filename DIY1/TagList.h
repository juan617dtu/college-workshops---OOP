//
// Created by masti on 1/19/2026.
//

#ifndef TAGLIST_H
#define TAGLIST_H
#include "NameTag.h"

namespace seneca {

    class TagList {

        NameTag* m_tag_list{};
        unsigned int m_max_capacity{};
        size_t m_added_tags{};

    public:

        TagList(int num);
        void add(const NameTag& nt);
        void print();
        ~TagList();
    };
}
#endif //TAGLIST_H
