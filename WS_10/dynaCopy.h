#ifndef DYNACOPY_H
#define DYNACOPY_H

template <typename T>
T* dynaCopy(const T* array, int size) {
    if (array == nullptr || size <= 0) return nullptr; //nothing to copy
    T* result = new T[size];
    for (size_t i = 0; i < size; ++i) result[i] = array[i];
    return result;
}
template <typename T>
T* dynaCopy(T*& dest_array, const T* src_array, int size) {
    if (src_array == nullptr || size <= 0) {
        delete[] dest_array;
        dest_array = nullptr;
        return nullptr;
    }
    delete[] dest_array;
    dest_array = new T[size];
    for (size_t i = 0; i < size; ++i) dest_array[i] = src_array[i];
    return dest_array;
}
template <typename T>
void prnArray(const T* array, int size) {
    for (size_t i = 1; i <= size; ++i) {
        if (i == size) std::cout << array[i - 1];
        else { std::cout << array[i - 1] << ", "; }
    }
    std::cout << std::endl;
}
#endif //DYNACOPY_H

