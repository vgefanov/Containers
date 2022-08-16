#include "s21_set.hpp"

namespace s21 {

// SetIterator

template <class T>
set<T>::SetIterator::SetIterator(RBNode<T, int> * ptr, RBTree<T, int> const * set_ptr)
    : ptr_(ptr), set_ptr_(set_ptr) {}

template <class T>
T set<T>::SetIterator::operator*() const {
    return (ptr_) ? ptr_->key_ : 0;
}

template <class T>
void set<T>::SetIterator::operator++() {
    ptr_ = (ptr_) ? set_ptr_->successor(ptr_->key_) : nullptr;
}

template <class T>
void set<T>::SetIterator::operator--() {
    ptr_ = (ptr_) ? set_ptr_->predecessor(ptr_->key_) : nullptr;
}

template <class T>
bool set<T>::SetIterator::operator==(iterator iter2) const {
    return (ptr_ == iter2.ptr_);
}

template <class T>
bool set<T>::SetIterator::operator!=(iterator iter2) const {
    return (ptr_ != iter2.ptr_);
}

// set

template <class T>
set<T>::set() : size_(0) {}

template <class T>
set<T>::set(std::initializer_list<T> const &items) : set() {
    for (auto i = items.begin(); i != items.end(); ++i) {
        insert(*i);
    }
}

template <class T>
set<T>::set(set<T> const &s) : set() {
    RBNode<T, int> *elem = s.min();
    while (elem) {
        insert(elem->key_);
        elem = s.successor(elem->key_);
    }
}

template <class T>
set<T>::set(set<T> &&s) {
    *this = std::move(s);
}

template <class T>
set<T>::~set() {
    size_ = 0;
}

template <class T>
set<T> & set<T>::operator=(set<T> &&s) {
    if (this != &s) {
        this->size_ = s.size_;
        this->root_ = s.root_;
        s.root_ = nullptr;
    }
    return *this;
}

template <class T>
typename set<T>::iterator set<T>::begin() const {
    return iterator(this->min(), this);
}

template <class T>
typename set<T>::iterator set<T>::end() const {
    return iterator(nullptr, this);
}

template <class T>
bool set<T>::empty() const {
    return (size_ == 0);
}

template <class T>
typename set<T>::size_type set<T>::size() const {
    return size_;
}

template <class T>
typename set<T>::size_type set<T>::max_size() const {
    return std::numeric_limits<size_t>::max() / (sizeof(T) * 20);
}

template <class T>
void set<T>::clear() {
    this->delete_tree(this->root_);
    this->root_ = nullptr;
    size_ = 0;
}

template <class T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(const_reference value) {
    bool result = false;
    RBNode<T, int> *node = nullptr;
    if (!contains(value)) {
        node = new RBNode<T, int>(value);
        this->insert_node(node);
        result = true;
        ++this->size_;
    }
    return { iterator(node, this), result };
}

template <class T>
void set<T>::erase(iterator pos) {
    if (contains(*pos)) {
        this->remove(*pos);
        --size_;
    }
}

template <class T>
void set<T>::swap(set& other) {
    std::swap(this->root_, other.root_);
    std::swap(size_, other.size_);
}

template <class T>
void set<T>::merge(set& other) {
    auto it = other.begin();
    while (it != other.end()) {
        auto [ins_it, ins_res] = insert(*it);
        auto tmp_it = it;
        ++tmp_it;
        if (ins_res) {
            other.erase(it);
        }
        it = tmp_it;
    }
}

template <class T>
typename set<T>::iterator set<T>::find(const_reference key) {
    return iterator(this->lookup(key), this);
}

template <class T>
bool set<T>::contains(const_reference key) {
    return (find(key).ptr_ != nullptr);
}

template <class T>
template <typename... Args>
std::pair<typename set<T>::iterator, bool> set<T>::emplace(Args&&... args) {
    const auto arg_list = {args...};
    std::pair<iterator, bool> result = { iterator(nullptr, this), false };
    for (auto value = arg_list.begin(); value != arg_list.end(); ++value) {
        result = insert(*value);
    }
    return result;
}

}  // namespace s21
