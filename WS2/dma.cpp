
#include "dma.h"
#include "cstr.h"
#include <cstring>

namespace seneca {

    Samples* CreateSamples(const char* title) {

        Samples* samples = new Samples;
        samples->m_title = new char[std::strlen(title) + 1];
        std::strcpy(samples->m_title, title);
        samples->m_data = nullptr;
        samples->m_size = 0;

        return samples;
    }
    void add(Samples& S, const int data[], int size) {

        if (size <= 0) return;

        if (S.m_data == nullptr) {

            S.m_data = new int[size];

            for (int i = 0; i < size; i++) {
                S.m_data[i] = data[i];
            }
            S.m_size = size;
        }
        else {
            int new_size = S.m_size + size;
            int* temp = new int[new_size];

            for (int i = 0; i < S.m_size; i++) {
                temp[i] = S.m_data[i];
            }
            for (int i = 0; i < size; i++) {
                temp[S.m_size + i] = data[i];
            }
            delete[] S.m_data;
            S.m_data = temp;
            S.m_size = new_size;
        }
    }
    void append(int*& data, int size, const int appendedData[], int dataSize) {

        int *new_array = new int[size + dataSize];

        for (int i = 0; i < size; i++) new_array[i] = data[i];
        for (int i = size; i < dataSize; i++) new_array[size + i] = appendedData[i];
        delete[] data;
        data = new_array;
    }
    void freemem(Samples*& s) {

        delete[] s->m_title;
        delete[] s->m_data;
        delete s;
        s = nullptr;
    }
}

