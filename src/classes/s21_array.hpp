#ifndef S21_CONTAINERS_S21_ARRAY_HPP
#define S21_CONTAINERS_S21_ARRAY_HPP

#include <iomanip>
#include <iostream>

namespace s21 {
template <typename T, std::size_t N>
class Array {
 public:
    // member types

    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

    // public methods

    Array();
    explicit Array(std::initializer_list<value_type> const &iterms);
    Array(const Array &a);
    Array(Array &&a);
    ~Array();
    Array &operator=(Array &&a);

    reference at(size_type pos);
    reference operator[](size_type pos);
    const_reference front();
    const_reference back();
    iterator data();

    iterator begin();
    iterator end();

    bool empty();
    size_type size();
    size_type max_size();

    void swap(Array &other);
    void fill(const_reference value);

 private:
    // private attributes and methods

    size_type sizeArray = N;
    value_type dataArray[N];
};

}  // namespace s21

#include "s21_array.inl"

#endif  // S21_CONTAINERS_S21_ARRAY_HPP
