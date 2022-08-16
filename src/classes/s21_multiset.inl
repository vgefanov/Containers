#include "s21_multiset.hpp"

namespace s21 {

// MultisetIterator

template <class T>
multiset<T>::MultisetIterator::MultisetIterator(RBNode<T, std::vector<T> *> *ptr,
                                                RBTree<T, std::vector<T> *> const * ms_ptr,
                                                int node_pos)
    : ptr_(ptr), ms_ptr_(ms_ptr), node_pos_(node_pos) {
}

template <class T>
T multiset<T>::MultisetIterator::operator*() const {
    T result = 0;
    if (ptr_) {
        if (node_pos_) {
            result = ptr_->value_->at(node_pos_ - 1);
        } else {
            result =  ptr_->key_;
        }
    }
    return result;
}

template <class T>
void multiset<T>::MultisetIterator::operator++() {
    if (ptr_) {
        if (ptr_->value_ && (node_pos_ < ptr_->value_->size())) {
            ++node_pos_;
        } else {
            node_pos_ = 0;
            ptr_ = ms_ptr_->successor(ptr_->key_);
        }
    }
}

template <class T>
void multiset<T>::MultisetIterator::operator--() {
    if (ptr_) {
        if (node_pos_ > 0) {
            --node_pos_;
        } else {
            ptr_ = ms_ptr_->predecessor(ptr_->key_);
            if (ptr_->value_) {
                node_pos_ = ptr_->value_->size();
            }
        }
    }
}

template <class T>
bool multiset<T>::MultisetIterator::operator==(iterator iter2) const {
    return ((ptr_ == iter2.ptr_) && (node_pos_ == iter2.node_pos_));
}

template <class T>
bool multiset<T>::MultisetIterator::operator!=(iterator iter2) const {
    return ((ptr_ != iter2.ptr_) || (node_pos_ != iter2.node_pos_));
}

// set

template <class T>
multiset<T>::multiset() : size_(0) {}

template <class T>
multiset<T>::multiset(std::initializer_list<T> const &items) : multiset() {
    for (auto i = items.begin(); i != items.end(); ++i) {
        insert(*i);
    }
}

template <class T>
multiset<T>::multiset(multiset<T> const &ms) : multiset() {
    RBNode<T,  std::vector<T> *> *elem = ms.min();
    while (elem) {
        insert(elem->key_);
        for (auto i = elem->value_->begin(); i != elem->value_->end(); ++i) {
            insert(*i);
        }
        elem = ms.successor(elem->key_);
    }
}

template <class T>
multiset<T>::multiset(multiset<T> &&ms) {
    *this = std::move(ms);
}

template <class T>
multiset<T>::~multiset() {
    clear_subnodes();
    size_ = 0;
}

template <class T>
multiset<T> & multiset<T>::operator=(multiset<T> &&ms) {
    if (this != &ms) {
        this->size_ = ms.size_;
        this->root_ = ms.root_;
        ms.root_ = nullptr;
    }
    return *this;
}

template <class T>
typename multiset<T>::iterator multiset<T>::begin() const {
    return iterator(this->min(), this);
}

template <class T>
typename multiset<T>::iterator multiset<T>::end() const {
    return iterator(nullptr, this);
}

template <class T>
bool multiset<T>::empty() const {
    return (size_ == 0);
}

template <class T>
typename multiset<T>::size_type multiset<T>::size() const {
    return size_;
}

template <class T>
typename multiset<T>::size_type multiset<T>::max_size() const {
    return std::numeric_limits<size_t>::max() / (sizeof(T) * 20);
}

template <class T>
void multiset<T>::clear_subnodes() {
    RBNode<T, std::vector<T> *> *elem = this->min();
    while (elem) {
        delete elem->value_;
        elem = this->successor(elem->key_);
    }
}

template <class T>
void multiset<T>::clear() {
    clear_subnodes();
    this->delete_tree(this->root_);
    this->root_ = nullptr;
    size_ = 0;
}

template <class T>
typename multiset<T>::iterator multiset<T>::insert(const_reference value) {
    iterator pos = find(value);
    if (!pos.ptr_) {
        std::vector<T> *items = new std::vector<T>;
        RBNode<T, std::vector<T> *> *node = new RBNode<T, std::vector<T> *>(value, items);
        this->insert_node(node);
        pos = iterator(node, this);
    } else {
        pos.ptr_->value_->push_back(value);
        pos = iterator(pos.ptr_, this, pos.ptr_->value_->size());
    }
    ++this->size_;
    return pos;
}

template <class T>
void multiset<T>::erase(iterator pos) {
    if (contains(*pos)) {
        if (pos.ptr_->value_->size() > 0) {
            pos.ptr_->value_->pop_back();
        } else {
            delete pos.ptr_->value_;
            this->remove(*pos);
        }
        --size_;
    }
}

template <class T>
void multiset<T>::swap(multiset& other) {
    std::swap(this->root_, other.root_);
    std::swap(size_, other.size_);
}

template <class T>
void multiset<T>::merge(multiset& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        insert(*it);
    }
    other.clear();
}

template <class T>
typename multiset<T>::size_type multiset<T>::count(const_reference key) {
    iterator pos = find(key);
    return (pos.ptr_) ? 1 + pos.ptr_->value_->size() : 0;
}

template <class T>
typename multiset<T>::iterator multiset<T>::find(const_reference key) {
    return iterator(this->lookup(key), this);
}

template <class T>
bool multiset<T>::contains(const_reference key) {
    return (find(key).ptr_ != nullptr);
}

template <class T>
std::pair<typename multiset<T>::iterator, typename multiset<T>::iterator>
    multiset<T>::equal_range(const_reference key) {
        iterator finded = find(key);
        std::pair<iterator, iterator> result = { finded, finded };
        if (finded.ptr_) {
            result.second = iterator(finded.ptr_, this, finded.ptr_->value_->size());
        }
        ++result.second;
        return result;
}

template <class T>
typename multiset<T>::iterator multiset<T>::lower_bound(const_reference key) {
    return find(key);
}

template <class T>
typename multiset<T>::iterator multiset<T>::upper_bound(const_reference key) {
    return iterator(this->successor(key), this);
}

template <class T>
template <typename... Args>
std::pair<typename multiset<T>::iterator, bool> multiset<T>::emplace(Args&&... args) {
    const auto arg_list = {args...};
    iterator result(nullptr, this);
    for (auto value = arg_list.begin(); value != arg_list.end(); ++value) {
        result = insert(*value);
    }
    return { result, true };
}

}  // namespace s21
