#include "s21_list.hpp"

namespace s21 {

// ListIterator

template <class T>
list<T>::ListIterator::ListIterator(list_item<T> *ptr)
    : ptr_(ptr) {}

template <class T>
T list<T>::ListIterator::operator*() const {
    return (ptr_) ? ptr_->data_ : 0;
}

template <class T>
void list<T>::ListIterator::operator++() {
    ptr_ = (ptr_) ? ptr_->next_ : nullptr;
}

template <class T>
void list<T>::ListIterator::operator--() {
    ptr_ = (ptr_) ? ptr_->previous_ : nullptr;
}

template <class T>
bool list<T>::ListIterator::operator==(iterator iter2) const {
    return (ptr_ == iter2.ptr_);
}

template <class T>
bool list<T>::ListIterator::operator!=(iterator iter2) const {
    return (ptr_ != iter2.ptr_);
}

// list

template <class T>
list<T>::list()
    : head_(nullptr)
    , tail_(nullptr)
    , size_(0) {}

template <class T>
list<T>::list(size_type n)  : list() {
    for (size_type i = 0; i != n; ++i) {
        push_back(0);
    }
}

template <class T>
list<T>::list(std::initializer_list<T> const &items) : list() {
    for (auto i = items.begin(); i != items.end(); ++i) {
        push_back(*i);
    }
}

template <class T>
list<T>::list(const list<T> &l) : list() {
    list_item<T> *item = l.head_;
    while (item) {
        push_back(item->data_);
        item = item->next_;
    }
}

template <class T>
list<T>::list(list<T> &&l) {
    *this = std::move(l);
}

template <class T>
list<T>::~list() {
    clear();
}

template <class T>
list<T> & list<T>::operator=(list<T> &&l) {
    if (this != &l) {
        swap(l);
        l.head_ = nullptr;
        l.tail_ = nullptr;
        l.size_ = 0;
    }
    return *this;
}

template <class T>
typename list<T>::const_reference list<T>::front() const {
    return head_->data_;
}

template <class T>
typename list<T>::const_reference list<T>::back() const {
    return tail_->data_;
}

template <class T>
typename list<T>::iterator list<T>::begin() const {
    return iterator(head_);
}

template <class T>
typename list<T>::iterator list<T>::end() const {
    return iterator(nullptr);
}

template <class T>
bool list<T>::empty() const {
    return (size_ == 0);
}

template <class T>
typename list<T>::size_type list<T>::size() const {
    return size_;
}

template <class T>
typename list<T>::size_type list<T>::max_size() const {
    return std::numeric_limits<size_type>::max() / (sizeof(list_item<T>) * 2);
}

template <class T>
void list<T>::clear() {
    while (head_) {
        list_item<T> * cls = head_;
        head_ = head_->next_;
        delete cls;
    }
    tail_ = nullptr;
    size_ = 0;
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos, const_reference value) {
    iterator result;
    if (!pos.ptr_) {
        push_back(value);
        result = end();
    } else {
        list_item<T> *ins = new list_item<T>(value, pos.ptr_, pos.ptr_->previous_);
        if (pos != begin()) {
            pos.ptr_->previous_->next_ = ins;
        } else {
            head_ = ins;
        }
        pos.ptr_->previous_ = ins;
        ++size_;
        result = iterator(ins);
    }
    return result;
}

template <class T>
void list<T>::erase(iterator pos) {
    if (size_ == 1) {
        clear();
    }
    if (size_ > 1) {
        list_item<T> * cls = pos.ptr_;
        if (pos.ptr_ == head_) {
            head_ = pos.ptr_->next_;
            pos.ptr_->next_->previous_ = nullptr;
        } else if (pos.ptr_ == tail_) {
            tail_ = pos.ptr_->previous_;
            pos.ptr_->previous_->next_ = nullptr;
        } else {
            pos.ptr_->previous_->next_ = pos.ptr_->next_;
            pos.ptr_->next_->previous_ = pos.ptr_->previous_;
        }
        delete cls;
        --size_;
    }
}

template <class T>
void list<T>::push_back(const_reference value) {
    list_item<T> *item = new list_item<T>(value, nullptr, nullptr);
    if (!head_) {
        head_ = item;
    }
    if (tail_) {
        item->previous_ = tail_;
        tail_->next_ = item;
    }
    tail_ = item;
    ++size_;
}

template <class T>
void list<T>::pop_back() {
    if (size_ > 0) {
        erase(iterator(tail_));
    }
}

template <class T>
void list<T>::push_front(const_reference value) {
    insert(begin(), value);
}

template <class T>
void list<T>::pop_front() {
    if (size_ > 0) {
        erase(begin());
    }
}

template <class T>
void list<T>::swap(list& other) {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(size_, other.size_);
}

template <class T>
void list<T>::merge(list& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }
    other.clear();
}

template <class T>
void list<T>::splice(const_iterator pos, list& other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        insert(pos, *it);
    }
    other.clear();
}

template <class T>
void list<T>::reverse() {
    auto pos1 = begin();
    auto pos2 = iterator(tail_);
    while (pos1 != pos2) {
        swap_elements(pos1, pos2);
        ++pos1;
        if (pos1 == pos2) break;
        --pos2;
    }
}

template <class T>
void list<T>::unique() {
    auto pos = begin();
    ++pos;
    for (; pos != end(); ++pos) {
        for (auto cmp = begin(); cmp != pos; ++cmp) {
            if (pos.ptr_->data_ == cmp.ptr_->data_) {
                erase(pos);
                break;
            }
        }
    }
}

template <class T>
void list<T>::sort() {
    for (auto pos1 = begin(); pos1 != end(); ++pos1) {
        auto pos2 = pos1;
        ++pos2;
        for (; pos2 != end(); ++pos2) {
            if (pos2.ptr_->data_ < pos1.ptr_->data_) {
                swap_elements(pos1, pos2);
            }
        }
    }
}

template <class T>
void list<T>::swap_elements(iterator pos1, iterator pos2) {
    if (pos1 != pos2) {
        std::swap(pos1.ptr_->data_, pos2.ptr_->data_);
    }
}

template <class T>
typename list<T>::iterator list<T>::emplace(const_iterator pos) {
    return insert(pos, 0);
}

template <class T>
template <typename... Args>
typename list<T>::iterator list<T>::emplace(const_iterator pos, Args&&... args) {
    const auto arg_list = {args...};
    iterator result;
    for (auto value = arg_list.begin(); value != arg_list.end(); ++value) {
        result = insert(pos, *value);
    }
    return result;
}

template <class T>
template <typename... Args>
void list<T>::emplace_back(Args&&... args) {
    const auto arg_list = {args...};
    for (auto value = arg_list.begin(); value != arg_list.end(); ++value) {
        push_back(*value);
    }
}

template <class T>
template <typename... Args>
void list<T>::emplace_front(Args&&... args) {
    const auto arg_list = {args...};
    auto pos = begin();
    for (auto value = arg_list.begin(); value != arg_list.end(); ++value) {
        insert(pos, *value);
    }
}

}  // namespace s21
