#ifndef S21_CONTAINERS_S21_STACK_HPP
#define S21_CONTAINERS_S21_STACK_HPP

#include <cstring>
#include <initializer_list>
#include <limits>
#include <utility>

#include "s21_list.hpp"

namespace s21 {

template <class T>
class stack : public list<T> {
 public:
    // member types

    using const_reference = const T &;
    using value_type = T;

    // public methods

    stack() {}
    explicit stack(std::initializer_list<value_type> const &items) : list<T>(items) {}
    const_reference top() { return this->back(); }

    void push(const_reference value) { this->push_back(value); }
    void pop() { this->pop_back(); }
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_STACK_HPP
