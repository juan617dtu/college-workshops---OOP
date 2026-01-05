#include "io.h"

#include <cstring>
#include <iostream>
#include <string>

namespace seneca {

        void read(char* name) {

                std::cout << "Name\n> ";
                std::cin >> name; //cpp version <= 17
        }
        void print(long long int phone_num) {

                std::string formatted_phone_num = std::to_string(phone_num);

                formatted_phone_num.insert(0, "(");
                formatted_phone_num.insert(4, ")");
                formatted_phone_num.insert(5, " ");
                formatted_phone_num.insert(9, "-");

                std::cout << formatted_phone_num;
        }
        void print(const PhoneRec& phone_rec, size_t& row_num, const char* name_filter) {

                if (name_filter == nullptr ||
                        strstr(phone_rec.first_name.c_str(), name_filter) ||
                        strstr(phone_rec.last_name.c_str(), name_filter)) {

                        std::cout << row_num << ": " << phone_rec.first_name << " " << phone_rec.last_name << " ";
                        print(phone_rec.phone_num);
                        std::cout << "\n";
                        row_num++;
                }
        }
        bool read(PhoneRec& data, FILE* file) {

                char first[26]{}, last[26]{};
                long long number{};
                int fields_read = fscanf(file, "%s %s %lld", first, last, &number);

                if (fields_read == 3) {
                        data.first_name = first;
                        data.last_name = last;
                        data.phone_num = number;
                        return true;
                }
                return false;
        }
        void print(PhoneRec *array[], size_t size, const char *filter) {

                size_t row_num = 1;

                for (int i = 0; i < size; i++) {
                        print(*array[i], row_num, filter);
                }
        }
        void setPointers(PhoneRec *array[], PhoneRec records[], size_t arrays_size) {

                for (int i = 0; i < arrays_size; i++) {
                        array[i] = &records[i];
                }
        }
        void sort(PhoneRec *array[], size_t array_size, bool sort_criteria) {

                for (size_t i = 0; i < array_size - 1; i++) {
                        for (size_t j = i + 1; j < array_size; j++) {

                                bool should_swap = false;

                                if (sort_criteria == true) {
                                        if (array[i]->last_name > array[j]->last_name) should_swap = true;
                                }
                                else {
                                        if (array[i]->first_name > array[j]->first_name) should_swap = true;
                                }
                                if (should_swap == true) {

                                        PhoneRec* temp = array[i];
                                        array[i] = array[j];
                                        array[j] = temp;
                                }
                        }
                }
        }
}


