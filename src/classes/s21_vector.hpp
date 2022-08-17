#ifndef S21_CONTAINERS_S21_VECTOR_HPP
#define S21_CONTAINERS_S21_VECTOR_HPP

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

    vector();                      // Конструктор по умолчанию
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

    void set_vector_value(size_type i, const_reference value);  // Заполняет вектор элементами
    void remove_vector();                                       // Очищает память

    template <class... Args>
    iterator emplace(const_iterator pos,
                     Args &&...args);  // вставляет новые элементы в контейнер непосредственно перед pos
    template <class... Args>
    void emplace_back(Args &&...args);  // добавляет новые элементы в конец контейнера

 private:
    size_type size_;
    size_type capacity_;
    value_type *arr_;
    size_type max_size_ = std::numeric_limits<size_t>::max() / sizeof(value_type) / 2;
    bool flag_increase_vector = 1;

    void create_vector(size_type n);  // Выделяет память
    void increasing_vector_capacity();
    void resize_vector();  // Увеличивает емкость вектора
    void copy_vector_elements(const vector &v1, vector &v2);  // Копирует элементы вектора
};

}  // namespace s21

#include "s21_vector.inl"

#endif  // S21_CONTAINERS_S21_VECTOR_HPP
