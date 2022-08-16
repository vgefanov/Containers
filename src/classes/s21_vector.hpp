#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T>
class vector {
 public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using iterator = T *;
    using const_iterator = const T *;
    using size_type = size_t;

    vector();             // Конструктор по умолчанию
    explicit vector(size_type n);  // Конструктор размера n
    explicit vector(std::initializer_list<value_type> const
               &items);  // Конструктор инициализированный с помощью std::list
    vector(const vector &v);             // Конструктор копирования
    vector(vector &&v);                  // Конструктор перемещения
    ~vector();                           // Деструктор
    vector &operator=(vector &&v);       // Перегрузка опреатора присваивания
    vector &operator=(const vector &v);  // Перегрузка опреатора присваивания

    reference at(size_type pos);  // Доступ к указанному элементу с проверкой границ
    reference operator[](size_type pos);  // Доступ к указанному элементу
    const_reference front();              // Доступ к первому элементу
    const_reference back();               // Доступ к последнему элементу
    iterator data();                      // Доступ к базовому массиву

    iterator begin();  // Возвращает итератор в начало
    iterator end();    // Возвращает итератор в конец

    bool empty();      // проверка контейнера на пустоту
    size_type size();  // возвращает количество элементов
    size_type max_size();  // возвращает максимально возможное количество элементов
    void reserve(size_t size);  // выделяет хранилище элементов размера и копирует текущие элементы массива
                                // в новый выделенный массив
    size_type capacity();  // возвращает количество элементов, которые могут храниться в выделенной в данный
                           // момент памяти
    void shrink_to_fit();  // уменьшает использование памяти, освобождая неиспользуемую память

    void clear();  // Очищает содержимое
    iterator insert(iterator pos,
                    const_reference value);  // вставляет элементы в конкретную позицию и возвращает итератор,
                                             // указывающий на новый элемент
    void erase(iterator pos);                // стирает элемент в позиции
    void push_back(const_reference value);   // добавляет элемент в конец
    void pop_back();                         // удаляет последний элемент
    void swap(vector &other);                // меняет содержимое

    void set_vector_value(size_type i, const_reference value);
    void remove_vector();

    template <class... Args>
    iterator emplace(const_iterator pos, Args &&...args);
    template <class... Args>
    void emplace_back(Args &&...args);

 private:
    size_type size_;
    size_type capacity_;
    value_type *arr_;
    size_type max_size_ = std::numeric_limits<size_t>::max() / sizeof(value_type) / 2;
    bool flag_increase_vector = 1;

    void create_vector(size_type n);
    void increasing_vector_capacity();
    void resize_vector();
    void copy_vector_elements(const vector &v1, vector &v2);
};

template <typename value_type>
vector<value_type>::vector() : size_(0), capacity_(0), arr_(nullptr) {}

template <typename value_type>
void vector<value_type>::create_vector(size_type n) {
    if (n == 0)
        arr_ = nullptr;
    else
        arr_ = new value_type[n];
}

template <typename value_type>
vector<value_type>::vector(size_type n) : size_(n), capacity_(n) {
    if (n > max_size_) throw std::length_error("Vector has exceeded the maximum size values");
    create_vector(size_);
}

template <typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items)
    : size_(items.size()), capacity_(items.size()) {
    create_vector(size_);
    size_type i = 0;
    for (auto pos = items.begin(); pos != items.end(); ++pos) {
        arr_[i++] = *pos;
    }
}

template <typename value_type>
vector<value_type>::vector(const vector &v) : vector() {
    if (this == &v) throw std::out_of_range("Error. Incorrect data");
    *this = v;
}

template <typename value_type>
void vector<value_type>::remove_vector() {
    if (arr_) {
        delete[] arr_;
        arr_ = nullptr;
    }
}

template <typename value_type>
vector<value_type>::vector(vector &&v) : vector() {
    *this = std::move(v);
    v.remove_vector();
    v.size_ = 0;
    v.capacity_ = 0;
}

template <typename value_type>
vector<value_type>::~vector() {
    remove_vector();
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(vector &&v) {
    if (this == &v) throw std::out_of_range("Error. Incorrect data");
    *this = v;
    v.remove_vector();
    v.size_ = 0;
    v.capacity_ = 0;
    return *this;
}

template <typename value_type>
vector<value_type> &vector<value_type>::operator=(const vector &v) {
    if (this == &v) throw std::out_of_range("Error. Incorrect data");
    remove_vector();
    size_ = v.size_;
    capacity_ = v.capacity_;
    create_vector(size_);
    copy_vector_elements(v, *this);
    return *this;
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
    if (pos >= size_) throw std::out_of_range("The specified element is outside the bounds of the vector");
    return *(arr_ + pos);
}

template <typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](size_type pos) {
    return *(arr_ + pos);
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() {
    if (!arr_) throw std::out_of_range("The vector contains no elements");
    return *arr_;
}

template <typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() {
    if (!arr_) throw std::out_of_range("The vector contains no elements");
    return *(arr_ + size_ - 1);
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::data() {
    return arr_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::begin() {
    return arr_;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::end() {
    return arr_ + size_;
}

template <typename value_type>
bool vector<value_type>::empty() {
    return size_ == 0;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::size() {
    return size_;
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::max_size() {
    return max_size_;
}

template <typename value_type>
void vector<value_type>::reserve(size_t size) {
    if (size > capacity_) {
        capacity_ = size;
        value_type *buff = new value_type[size]();
        for (size_type i = 0; i < size_; ++i) {
            buff[i] = arr_[i];
        }
        std::swap(arr_, buff);
        delete[] buff;
    }
}

template <typename value_type>
typename vector<value_type>::size_type vector<value_type>::capacity() {
    return capacity_;
}

template <typename value_type>
void vector<value_type>::increasing_vector_capacity() {
    capacity_ = size_ * 2;
    if (capacity_ >= max_size_) throw std::invalid_argument("Capacity exceeds allowable dimensions");
}

template <typename value_type>
void vector<value_type>::copy_vector_elements(const vector &v1, vector &v2) {
    if (&v1 != &v2 || v1.size_ != v2.size_) {
        for (size_type i = 0; i < v1.size_; ++i) {
            v2.arr_[i] = v1.arr_[i];
        }
    }
}

template <typename value_type>
void vector<value_type>::resize_vector() {
    vector tmp(*this);
    remove_vector();
    size_ = tmp.size_;
    if (flag_increase_vector == 1 && size_ >= capacity_) {
        increasing_vector_capacity();
    }
    if (flag_increase_vector == 0) {
        capacity_ = size_;
    }
    create_vector(capacity_);
    copy_vector_elements(tmp, *this);
}

template <typename value_type>
void vector<value_type>::shrink_to_fit() {
    flag_increase_vector = 0;
    resize_vector();
    flag_increase_vector = 1;
}

template <typename value_type>
void vector<value_type>::clear() {
    remove_vector();
    size_ = 0;
}

template <typename value_type>
typename vector<value_type>::iterator vector<value_type>::insert(iterator pos, const_reference value) {
    size_type index = pos - arr_;
    if (size_ == capacity_) {
        reserve(capacity_ * 2);
    }
    for (size_type i = size_, j = size_ - 1; i > 0; --i, --j) {
        arr_[i] = arr_[j];
        if (i == index) {
            arr_[i] = value;
            ++j;
        }
    }
    ++size_;
    arr_[index] = value;
    pos = arr_ + index;
    return pos;
}

template <typename value_type>
void vector<value_type>::erase(iterator pos) {
    if (pos != end()) {
        size_type index = pos - begin();
        pos = begin() + index;
        for (auto i = pos; i != end() - 1; ++i) {
            *i = *(i + 1);
        }
    }
    --size_;
}

template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
    if (arr_) {
        resize_vector();
        auto pos = end();
        *pos = value;
        ++size_;
    } else {
        size_ = capacity_ = 1;
        create_vector(size_);
        auto pos = begin();
        *pos = value;
    }
}

template <typename value_type>
void vector<value_type>::pop_back() {
    if (!arr_) throw std::out_of_range("The vector contains no elements");
    --size_;
}

template <typename value_type>
void vector<value_type>::swap(vector &other) {
    if (this != &other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(arr_, other.arr_);
    }
}

template <typename value_type>
void vector<value_type>::set_vector_value(size_type i, const_reference value) {
    if (arr_) arr_[i] = value;
}

template <typename value_type>
template <class... Args>
typename vector<value_type>::iterator vector<value_type>::emplace(const_iterator pos, Args &&...args) {
    const auto arg_vector = {args...};
    auto value = arg_vector.begin();
    iterator result = nullptr;
    for (; value != arg_vector.end(); ++value) {
        result = insert(const_cast<int *>(pos), *value);
    }
    return result;
}

template <typename value_type>
template <class... Args>
void vector<value_type>::emplace_back(Args &&...args) {
    const auto arg_vector = {args...};
    for (auto value = arg_vector.begin(); value != arg_vector.end(); ++value) {
        push_back(*value);
    }
}

}  // namespace s21

#endif  // SRC_S21_VECTOR_H_
