//
// Created by masti on 10/6/2025.
//

#ifndef IO_H
#define IO_H
#include <cstring>
#include <string>
#include <iostream>

namespace seneca {

    struct PhoneRec {

        std::string first_name;
        std::string last_name;
        long long int phone_num;
    };
    void read(char* name);
    void print(long long int phone_num);
    void print(const PhoneRec& phone_rec, size_t& row_num, const char* name_filter = nullptr);
    bool read(PhoneRec& data, FILE* file);
    void print(PhoneRec* array[], size_t size, const char* filter = nullptr);
    void setPointers(PhoneRec* array[], PhoneRec records[], size_t arrays_size);
    void sort(PhoneRec* array[], size_t array_size, bool sort_criteria);
}
#endif //IO_H
