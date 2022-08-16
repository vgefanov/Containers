#include <iostream>
#include <limits>

#include "s21_map.hpp"

namespace s21 {

template <typename Key, typename T>
typename Map<Key, T>::Iterator& Map<Key, T>::Iterator::operator++() {
    if (m_node) {
        if (m_node->right == nullptr && m_node->parent) {
            while (m_node->parent && m_node->data.first > m_node->parent->data.first) m_node = m_node->parent;
            m_node = m_node->parent;
        } else {
            if (m_node->right) {
                m_node = m_node->right;
                while (m_node->left) m_node = m_node->left;
            } else {
                m_node = nullptr;
            }
        }
    }
    return *this;
}

template <typename Key, typename T>
typename Map<Key, T>::Iterator& Map<Key, T>::Iterator::operator--() {
    if (m_node) {
        if (m_node->left_ == nullptr && m_node->parent_) {
            while (m_node->data.first < m_node->parent->data.first) m_node = m_node->parent;
            m_node = m_node->parent;
        } else if (m_node->left) {
            m_node = m_node->left;
            while (m_node->right) m_node = m_node->right;
        }
    } else {
        m_node = begin();
    }
    return *this;
}

template <typename Key, typename T>
Map<Key, T>::Map() : root(nullptr) {}

template <typename Key, typename T>
Map<Key, T>::Map(std::initializer_list<value_type> const& items) : Map() {
    for (auto element : items) insert(element);
}

template <typename Key, typename T>
Map<Key, T>::Map(const Map& m) : Map() {
    if (this == &m) throw std::out_of_range("Invalid argument");
    clear();
    Node<Key, T>* tmp_node = m.root;
    while (tmp_node->left) tmp_node = tmp_node->left;
    iterator end(nullptr);
    for (iterator it_m(tmp_node); it_m != end; ++it_m) {
        this->insert(*it_m);
    }
}

template <typename Key, typename T>
Map<Key, T>::Map(Map&& m) : Map() {
    *this = std::move(m);
}

template <typename Key, typename T>
Map<Key, T>::~Map() {
    destroy(root);
}

template <typename Key, typename T>
void Map<Key, T>::destroy(Node<Key, T>*& node) {
    if (node == NULL) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}

template <typename Key, typename T>
Map<Key, T>& Map<Key, T>::operator=(Map&& m) {
    swap(m);
    m.clear();
    return *this;
}

template <typename Key, typename T>
T& Map<Key, T>::at(const Key& key) {
    Node<Key, T>* x = search(key);
    return x->data.second;
}

template <typename Key, typename T>
T& Map<Key, T>::operator[](const Key& key) {
    if (contains(key) == false) {
        insert(key, mapped_type());
    }
    iterator it_result = find(key);
    Node<Key, T>* result = it_result.GetNode();
    return result->data.second;
}

template <typename Key, typename T>
bool Map<Key, T>::empty() {
    return root == nullptr;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::size() {
    size_type res = 0;
    if (root) {
        for (iterator it = begin(); it != end(); ++it) {
            ++res;
        }
    }
    return res;
}

template <typename Key, typename T>
typename Map<Key, T>::size_type Map<Key, T>::max_size() {
    return std::numeric_limits<size_type>::max() / (sizeof(Node<Key, T>) / 2);
}

template <typename Key, typename T>
void Map<Key, T>::leftRotate(Node<Key, T>*& root, Node<Key, T>* x) {
    Node<Key, T>* y = x->right;
    x->right = y->left;
    if (y->left != NULL) y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    } else {
        if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

template <typename Key, typename T>
void Map<Key, T>::rightRotate(Node<Key, T>*& root, Node<Key, T>* y) {
    Node<Key, T>* x = y->left;
    y->left = x->right;
    if (x->right != NULL) x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL) {
        root = x;
    } else {
        if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;
    }
    x->right = y;
    y->parent = x;
}

template <typename Key, typename T>
template <typename... Args>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::emplace(Args&&... args) {
    const auto arg_list = {args...};
    std::pair<iterator, bool> result;
    result = std::make_pair(end(), false);
    for (auto value = arg_list.begin(); value != arg_list.end(); ++value) {
        result = insert(*value);
    }
    return result;
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(const Key& key, const T& obj) {
    std::pair<Key, T> data;
    data.first = key;
    data.second = obj;
    bool res = true;
    Node<Key, T>* node = new Node<Key, T>(data, Red, nullptr, nullptr, nullptr);
    Node<Key, T>* x = root;
    Node<Key, T>* y = NULL;
    while (x != NULL) {
        y = x;
        if (node->data.first > x->data.first)
            x = x->right;
        else
            x = x->left;
    }
    node->parent = y;
    if (y != NULL) {
        if (node->data.first > y->data.first)
            y->right = node;
        else if (node->data.first < y->data.first)
            y->left = node;
        else
            res = false;
    } else {
        root = node;
    }
    node->color = Red;
    InsertFixUp(root, node);
    iterator resultIterator(node);
    if (!res) delete node;
    return std::pair<iterator, bool>(resultIterator, res);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert_or_assign(const Key& key, const T& obj) {
    Node<Key, T>* node = search(key);
    if (node == nullptr) return insert(key, obj);
    node->data.second = obj;
    return std::pair<iterator, bool>(node, false);
}

template <typename Key, typename T>
std::pair<typename Map<Key, T>::iterator, bool> Map<Key, T>::insert(const_reference value) {
    return insert(value.first, value.second);
}

template <typename Key, typename T>
void Map<Key, T>::InsertFixUp(Node<Key, T>*& root, Node<Key, T>* node) {
    Node<Key, T>* parent;
    parent = node->parent;
    while (node != Map::root && parent->color == Red) {
        Node<Key, T>* gparent = parent->parent;
        if (gparent->left == parent) {
            Node<Key, T>* uncle = gparent->right;
            if (uncle != NULL && uncle->color == Red) {
                parent->color = Black;
                uncle->color = Black;
                gparent->color = Red;
                node = gparent;
                parent = node->parent;
            } else {
                if (parent->right == node) {
                    leftRotate(root, parent);
                    std::swap(node, parent);
                }
                rightRotate(root, gparent);
                gparent->color = Red;
                parent->color = Black;
                break;
            }
        } else {
            Node<Key, T>* uncle = gparent->left;
            if (uncle != NULL && uncle->color == Red) {
                gparent->color = Red;
                parent->color = Black;
                uncle->color = Black;

                node = gparent;
                parent = node->parent;
            } else {
                if (parent->left == node) {
                    rightRotate(root, parent);
                    std::swap(parent, node);
                }
                leftRotate(root, gparent);
                parent->color = Black;
                gparent->color = Red;
                break;
            }
        }
    }
    root->color = Black;
}

template <typename Key, typename T>
Node<Key, T>* Map<Key, T>::search(Node<Key, T>* node, Key key) {
    if (node == NULL || node->data.first == key)
        return node;
    else if (key > node->data.first)
        return search(node->right, key);
    else
        return search(node->left, key);
}

template <typename Key, typename T>
Node<Key, T>* Map<Key, T>::search(Key key) {
    return search(root, key);
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::find(Key key) {
    Node<Key, T>* node = search(root, key);
    iterator res(node);
    return res;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::begin() {
    Node<Key, T>* node = root;
    while (node->left) node = node->left;
    iterator res(node);
    return res;
}

template <typename Key, typename T>
typename Map<Key, T>::iterator Map<Key, T>::end() {
    return iterator(nullptr);
}

template <typename Key, typename T>
void Map<Key, T>::erase(iterator pos) {
    if (pos.GetNode()) {
        if (contains(pos.GetNode()->data.first)) {
            Node<Key, T>* node = search(root, pos.GetNode()->data.first);
            if (node != NULL) remove(root, node);
        }
    }
}

template <typename Key, typename T>
void Map<Key, T>::swap(Map& other) {
    if (this != &other) {
        std::swap(this->root, other.root);
    }
}

template <typename Key, typename T>
void Map<Key, T>::merge(Map& other) {
    if (this != &other && other.empty() == false) {
        for (iterator it_other = other.begin(); it_other != other.end(); ++it_other) {
            if (contains((*it_other).first) == false) {
                insert(*it_other);
            }
        }
    }
    other.clear();
}

template <typename Key, typename T>
bool Map<Key, T>::contains(const Key& key) {
    return (search(key) != nullptr);
}

template <typename Key, typename T>
void Map<Key, T>::clear() {
    destroy(root);
}

template <typename Key, typename T>
void Map<Key, T>::remove(Node<Key, T>*& root, Node<Key, T>* node) {
    Node<Key, T>*child, *parent;
    if (node->left != NULL && node->right != NULL) {
        Node<Key, T>* replace;
        replace = node->right;
        while (replace->left != NULL) {
            replace = replace->left;
        }
        if (node->parent != NULL) {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        } else {
            root = replace;
        }
        child = replace->right;
        parent = replace->parent;
        if (parent != node) {
            if (child != NULL) child->parent = parent;
            parent->left = child;

            replace->right = node->right;
            node->right->parent = replace;
        }
        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;
        delete node;
        return;
    }
    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    if (child) {
        child->parent = parent;
    }
    if (parent) {
        if (node == parent->left)
            parent->left = child;
        else
            parent->right = child;
    } else {
        Map::root = child;
    }
    delete node;
}
}  // namespace s21
