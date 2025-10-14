//
// Created by masti on 10/6/2025.
//

#ifndef SENECA_CSTR_H
#define SENECA_CSTR_H
#include <cstring>
#include <iostream>

namespace seneca {

   char* strcat(char* des, const char* src);
   char tolower(char ch);
   char* tolower(char* des, const char* src);
   char* tolower(char* str);
   int strcmp(const char* s1, const char* s2);
   int strcmp(const char* s1, const char* s2, size_t len);
   char* strcpy(char* des, const char* src);
   char* strcpy(char* des, const char* src, size_t len);
   char* strncpy(char* des, const char* src, size_t len);
   size_t strlen(const char* str);
   const char* strstr(const char* str, const char* toFind);
   bool isalpha(char ch);
   bool isspace(char ch);
}
#endif //SENECA_CSTR_H
