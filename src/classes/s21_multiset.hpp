#ifndef S21_CONTAINERS_S21_MULTISET_HPP
#define S21_CONTAINERS_S21_MULTISET_HPP

#include <cstring>
#include <initializer_list>
#include <utility>
#include <limits>
#include <vector>

#include "s21_rbtree.hpp"

namespace s21 {

template <class T>
class multiset : public RBTree<T, std::vector<T> *> {
 public:
    class MultisetIterator;

    // member types

    using key_type = T;
    using value_type = key_type;
    using reference = value_type &;
    using const_reference = const value_type &;
    using iterator = MultisetIterator;
    using const_iterator = const MultisetIterator;
    using size_type = size_t;

    // iterator

    class MultisetIterator {
     public:
        explicit MultisetIterator(RBNode<T, std::vector<T> *> *ptr,
                                  RBTree<T, std::vector<T> *> const * ms_ptr,
                                  int node_pos_ = 0);
        T operator*() const;
        void operator++();
        void operator--();
        bool operator==(iterator iter2) const;
        bool operator!=(iterator iter2) const;

     public:
        RBNode<T, std::vector<T> *> *ptr_;
        const RBTree<T, std::vector<T> *> *ms_ptr_;
        long unsigned int node_pos_;
    };

    // public methods

    multiset();
    explicit multiset(std::initializer_list<value_type> const &items);
    multiset(const multiset &ms);
    multiset(multiset &&ms);
    ~multiset();
    multiset<T> & operator=(multiset &&ms);

    iterator begin() const;
    iterator end() const;

    bool empty() const;
    size_type size() const;
    size_type max_size() const;

    void clear();
    iterator insert(const_reference value);
    void erase(iterator pos);
    void swap(multiset& other);
    void merge(multiset& other);

    size_type count(const_reference key);
    iterator find(const_reference key);
    bool contains(const_reference key);
    std::pair<iterator, iterator> equal_range(const_reference key);
    iterator lower_bound(const_reference key);
    iterator upper_bound(const_reference key);

    template <typename... Args> std::pair<iterator, bool> emplace(Args&&... args);

 private:
    // private attributes and methods

    void clear_subnodes();

    size_type size_;
};

}  // namespace s21

#include "s21_multiset.inl"

#endif  // S21_CONTAINERS_S21_MULTISET_HPP
