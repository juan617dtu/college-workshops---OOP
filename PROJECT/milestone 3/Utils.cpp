#include <iostream>
#include "Utils.h"
#include <limits>

using namespace std;
namespace seneca {
    Utils ut;

    char* Utils::alocpy(const char* src) const{
        char* des{};
        return alocpy(des, src);
    }

    char* Utils::alocpy(char*& des, const char* src)const {
        delete[] des;
        des = nullptr;
        if (src) {
            des = new char[strlen(src) + 1];
            strcpy(des, src);
        }
        return des;
    }
    char* Utils::strcpy(char* des, const char* src)const {
        int i;
        for (i = 0; src[i]; i++) des[i] = src[i];
        des[i] = char(0);
        return des;
    }
    int Utils::strlen(const char* str)const {
        int len;
        for (len = 0; str[len]; len++);
        return len;
    }

    bool Utils::isspace(char ch)const {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v' || ch == '\f' || ch == '\r';
    }

    bool Utils::isspace(const char* cstring) const{
        while (cstring && isspace(*cstring)) {
            cstring++;
        }
        return cstring && *cstring == 0;
    }
    int Utils::getInt() {

        int num;
        bool valid = false;
        do {
            if (cin.peek() == '\n') cout << "You must enter a value: ";
            else {
                cin >> num;
                if (cin.fail()) {
                    cout << "Invalid integer: ";
                }
                else if (cin.peek() != '\n') cout << "Only an integer please: ";
                else valid = true;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (!valid);
        return num;
    }
    int Utils::getInt(int min, int max) {

        int num;
        bool valid = false;
        do {
            num = getInt();
            if (num < min || num > max) cout << "Invalid value: [min <= value <= max], try again: ";
            else valid = true;
        } while (!valid);
        return num;
    }
}