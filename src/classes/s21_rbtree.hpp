#ifndef S21_CONTAINERS_S21_RBTREE_HPP
#define S21_CONTAINERS_S21_RBTREE_HPP

#include <iostream>

namespace s21 {

enum RBColor {
    RED,
    BLACK,
};

template <class T, class U>
struct RBNode {
    T key_;
    U value_;
    RBColor color_;
    RBNode * parent_;
    RBNode * left_;
    RBNode * right_;

    explicit RBNode(T key,
           U value = 0,
           RBColor color = RED,
           RBNode *parent = nullptr,
           RBNode *left = nullptr,
           RBNode *right = nullptr)
        : key_(key), value_(value), color_(color), parent_(parent), left_(left), right_(right) {}

    template <typename V, class W> friend std::ostream& operator<<(std::ostream& out, RBNode<V, W> & node);
};

template <class T, class U>
class RBTree {
 public:
    RBTree();
    explicit RBTree(RBNode<T, U> *root);
    ~RBTree();
    bool insert_key(T key);
    bool insert_node(RBNode<T, U> *node);
    void remove(T key);
    RBNode<T, U> * lookup(T key);
    RBNode<T, U> * min(RBNode<T, U> *tree = nullptr) const;
    RBNode<T, U> * max(RBNode<T, U> *tree = nullptr) const;
    RBNode<T, U> * successor(T key) const;
    RBNode<T, U> * predecessor(T key) const;
    template <typename V, class W> friend std::ostream& operator<<(std::ostream& out, RBTree<V, W> & tree);

 protected:
    // RBNode<T, U> * getRoot();
    void delete_tree(RBNode<T, U> *root);

 private:
    void insert_fixup(RBNode<T, U> *&root, RBNode<T, U> *node);
    void left_rotate(RBNode<T, U> *x);
    void right_rotate(RBNode<T, U> *y);
    void transplant(RBNode<T, U> *u, RBNode<T, U> *v, RBNode<T, U> const *node);
    void remove_fixup(RBNode<T, U> *&root, RBNode<T, U> *node, RBNode<T, U> *parent);
    void print_subtree(std::ostream& out, RBNode<T, U> *root, char lr, int lvl);

 protected:
    RBNode<T, U> *root_;
};

}  // namespace s21

#include "s21_rbtree.inl"

#endif  // S21_CONTAINERS_S21_RBTREE_HPP
