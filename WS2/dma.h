//
// Created by masti on 10/14/2025.
//

#ifndef DMA_H
#define DMA_H

namespace seneca {
    struct Samples {
        char* m_title;   // Dynamically allocated title
        int* m_data;     // Dynamically allocated array of integers
        int m_size;   // Number of elements in m_data
    };
    Samples* CreateSamples(const char* title);
    void add(Samples& S, const int data[], int size);
    void append(int*& data, int size, const int appendedData[], int dataSize);
    void freemem(Samples*& s);
}
#endif //DMA_H
