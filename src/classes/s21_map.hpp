#ifndef S21_CONTAINERS_S21_MAP_HPP
#define S21_CONTAINERS_S21_MAP_HPP

#include <iomanip>
#include <iostream>

enum Color { Black, Red };
namespace s21 {
template <typename Key, typename T>
struct Node {
    std::pair<const Key, T> data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;
    Node(std::pair<const Key, T> data, Color color, Node* left, Node* right, Node* parent)
        : data(data), color(color), left(left), right(right), parent(parent) {}
    explicit Node(std::pair<const Key, T> data)
        : data(data), left(nullptr), right(nullptr), parent(nullptr), color(Red) {}
};

template <typename Key, typename T>
class Map {
 private:
    void destroy(Node<Key, T>*& node);
    void InsertFixUp(Node<Key, T>*& root, Node<Key, T>* node);
    void leftRotate(Node<Key, T>*& root, Node<Key, T>* x);
    void rightRotate(Node<Key, T>*& root, Node<Key, T>* y);
    void remove(Node<Key, T>*& root, Node<Key, T>* node);

 public:
    // member types

    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

    // iterator

    class Iterator {
     public:
        Iterator() : m_node(nullptr) {}
        explicit Iterator(Node<Key, T>* node) : m_node(node) {}

        Node<Key, T>* GetNode() { return m_node; }
        Iterator& operator++();
        Iterator& operator--();
        const_reference operator*() { return m_node->data; }

        bool operator==(const Iterator& other) { return this->m_node == other.m_node; }

        bool operator!=(const Iterator& other) { return this->m_node != other.m_node; }

     private:
        Node<Key, T>* m_node;
    };

    using iterator = Iterator;
    using const_iterator = const Iterator;

    // public methods

    Map();
    explicit Map(std::initializer_list<value_type> const& items);
    Map(const Map& m);
    Map(Map&& m);
    ~Map();

    Map& operator=(Map&& m);

    // Element access
    T& operator[](const Key& key);
    T& at(const Key& key);

    // Map Iterators
    iterator begin();
    iterator end();

    // Capacity
    bool empty();
    size_type size();
    size_type max_size();

    void clear();
    std::pair<iterator, bool> insert(const value_type& value);
    std::pair<iterator, bool> insert(const Key& key, const T& obj);
    template <class... Args>
    std::pair<iterator, bool> emplace(Args&&... args);
    std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
    void erase(iterator pos);
    void swap(Map& other);
    void merge(Map& other);

    bool contains(const Key& key);

    Node<Key, T>* search(Key key);
    iterator find(Key key);
    Node<Key, T>* search(Node<Key, T>* node, Key key);

 private:
    // private attributes and methods

    Node<Key, T>* root;
};
}  // namespace s21

#include "s21_map.inl"

#endif  // S21_CONTAINERS_S21_MAP_HPP
