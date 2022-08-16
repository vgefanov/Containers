#ifndef S21_CONTAINERS_S21_SET_HPP
#define S21_CONTAINERS_S21_SET_HPP

#include <cstring>
#include <initializer_list>
#include <utility>
#include <limits>

#include "s21_rbtree.hpp"

namespace s21 {

template <class T>
class set : public RBTree<T, int> {
 public:
    class SetIterator;

    // member types

    using key_type = T;
    using value_type = key_type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = SetIterator;
    using const_iterator = const SetIterator;
    using size_type = size_t;

    // iterator

    class SetIterator {
     public:
        explicit SetIterator(RBNode<T, int> * ptr, RBTree<T, int> const * set_ptr);
        T operator*() const;
        void operator++();
        void operator--();
        bool operator==(iterator iter2) const;
        bool operator!=(iterator iter2) const;

     public:
        RBNode<T, int> *ptr_;
        const RBTree<T, int> *set_ptr_;
    };

    // public methods

    set();
    explicit set(std::initializer_list<value_type> const &items);
    set(const set &s);
    set(set &&s);
    ~set();
    set<T> & operator=(set &&s);

    iterator begin() const;
    iterator end() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    void clear();
    std::pair<iterator, bool> insert(const_reference value);
    void erase(iterator pos);
    void swap(set& other);
    void merge(set& other);

    iterator find(const_reference key);
    bool contains(const_reference key);

    template <typename... Args> std::pair<iterator, bool> emplace(Args&&... args);

 private:
    // private attributes and methods

    size_type size_;
};

}  // namespace s21

#include "s21_set.inl"

#endif  // S21_CONTAINERS_S21_SET_HPP
