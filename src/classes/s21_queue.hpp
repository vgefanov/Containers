#ifndef S21_CONTAINERS_S21_QUEUE_HPP
#define S21_CONTAINERS_S21_QUEUE_HPP

#include "s21_list.hpp"

namespace s21 {

template <class T>
class queue : public list<T> {
 public:
    // member types

    using value_type = T;
    using const_reference = const T &;

    // public methods

    queue() {}
    explicit queue(std::initializer_list<value_type> const &items) : list<T>(items) {}
    void push(const_reference value) { this->push_back(value); }
    void pop() { this->pop_front(); }
};

}  // namespace s21

#endif  // S21_CONTAINERS_S21_LIST_HPP
