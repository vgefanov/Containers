#include "s21_array.hpp"

namespace s21 {
template <typename T, std::size_t N>
Array<T, N>::Array() {}

template <typename T, std::size_t N>
Array<T, N>::Array(std::initializer_list<T> const &iterms) {
    size_type i = 0;
    for (auto pos = iterms.begin(); pos != iterms.end(); ++pos) dataArray[i++] = *pos;
}

template <typename T, std::size_t N>
Array<T, N>::Array(const Array &a) {
    if (this != &a) {
        for (size_type i = 0; i < sizeArray; ++i) dataArray[i] = a.dataArray[i];
    }
}

template <typename T, std::size_t N>
Array<T, N>::Array(Array &&a) {
    *this = std::move(a);
}

template <typename T, std::size_t N>
Array<T, N>::~Array() {}

template <typename T, std::size_t N>
Array<T, N> &Array<T, N>::operator=(Array &&a) {
    if (this != &a) {
        for (size_type i = 0; i < sizeArray; ++i) dataArray[i] = a.dataArray[i];
    }
    return *this;
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
    if (pos >= size) throw std::invalid_argument("Invalid index");
    return *(dataArray + pos);
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
    return *(dataArray + pos);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
    if (sizeArray == 0) throw std::out_of_range("Invalid data");
    return *dataArray;
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
    if (sizeArray == 0) throw std::out_of_range("Invalid data");
    return *(dataArray + sizeArray - 1);
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
    return dataArray;
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
    return dataArray;
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
    return dataArray + sizeArray;
}

template <typename T, std::size_t N>
bool Array<T, N>::empty() {
    return sizeArray == 0;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::size() {
    return sizeArray;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() {
    return 0;
}

template <typename T, std::size_t N>
void Array<T, N>::swap(Array &other) {
    if (this != &other || sizeArray != other.sizeArray) {
        std::swap(sizeArray, other.sizeArray);
        std::swap(dataArray, other.dataArray);
    }
}

template <typename T, std::size_t N>
void Array<T, N>::fill(const_reference value) {
    if (sizeArray != 0) {
        for (size_type i = 0; i < sizeArray; ++i) dataArray[i] = value;
    }
}

}  // namespace s21
