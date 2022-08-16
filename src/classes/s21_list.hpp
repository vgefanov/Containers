#ifndef S21_CONTAINERS_S21_LIST_HPP
#define S21_CONTAINERS_S21_LIST_HPP

#include <cstring>
#include <initializer_list>
#include <utility>
#include <limits>

namespace s21 {

template <class T>
struct list_item {
 public:
    T data_;
    list_item<T> *next_;
    list_item<T> *previous_;

    list_item<T>(T data, list_item<T> *next, list_item<T> *previous)
        : data_(data), next_(next), previous_(previous) {}
};

template <class T>
class list {
 public:
    class ListIterator;

    // member types

    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = ListIterator;
    using const_iterator = const ListIterator;
    using size_type = size_t;

    // iterator

    class ListIterator {
     public:
        explicit ListIterator(list_item<T> *ptr = nullptr);
        T operator*() const;
        void operator++();
        void operator--();
        bool operator==(iterator iter2) const;
        bool operator!=(iterator iter2) const;
        list_item<T> *ptr_;
    };

    // public methods

    list();
    explicit list(size_type n);
    explicit list(std::initializer_list<value_type> const &items);
    list(const list &l);
    list(list &&l);
    ~list();
    list<T> & operator=(list &&l);

    const_reference front() const;
    const_reference back() const;

    iterator begin() const;
    iterator end() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    void clear();
    iterator insert(iterator pos, const_reference value);
    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void push_front(const_reference value);
    void pop_front();
    void swap(list& other);
    void merge(list& other);
    void splice(const_iterator pos, list& other);
    void reverse();
    void unique();
    void sort();

    iterator emplace(const_iterator pos);
    template <typename... Args> iterator emplace(const_iterator pos, Args&&... args);
    template <typename... Args> void emplace_back(Args&&... args);
    template <typename... Args> void emplace_front(Args&&... args);

 private:
    // private attributes and methods

    list_item<T> *head_;
    list_item<T> *tail_;
    size_type size_;

    void swap_elements(iterator pos1, iterator pos2);
};

}  // namespace s21

#include "s21_list.inl"

#endif  // S21_CONTAINERS_S21_LIST_HPP
