namespace s21 {

template <class T, class U>
std::ostream& operator<<(std::ostream& out, RBNode<T, U> & node) {
    char color = (node.color_ == RED) ? 'r' : 'b';
    out << node.key_ << '[' << color << ']';
    if (node.value_) {
        for (auto i = node.value_->begin(); i != node.value_->end(); ++i) {
            out << "->" << *i;
        }
    }
    return out;
}

template <class T, class U>
RBTree<T, U>::RBTree() : root_(nullptr) {}

template <class T, class U>
RBTree<T, U>::RBTree(RBNode<T, U> *root) : root_(root) {}

template <class T, class U>
RBTree<T, U>::~RBTree() {
    delete_tree(root_);
    root_ = nullptr;
}

template <class T, class U>
bool RBTree<T, U>::insert_key(T key) {
    RBNode<T, U> *node = new RBNode<T, U>(key);
    bool result = insert_node(node);
    if (!result) {
        delete node;
    }
    return result;
}

template <class T, class U>
bool RBTree<T, U>::insert_node(RBNode<T, U> *node) {
    bool result = true;
    RBNode<T, U> *tree = root_;
    RBNode<T, U> *parent = nullptr;
    while (tree && result) {
        parent = tree;
        if (node->key_ > tree->key_) {
            tree = tree->right_;
        } else if (node->key_ < tree->key_) {
            tree = tree->left_;
        } else {
            result = false;
        }
    }
    if (result) {
        node->parent_ = parent;
        if (!parent) {
            root_ = node;
        } else {
            if (node->key_ > parent->key_)
                parent->right_ = node;
            else
                parent->left_ = node;
        }
        insert_fixup(root_, node);
    }
    return result;
}

template <class T, class U>
void RBTree<T, U>::delete_tree(RBNode<T, U> *root) {
    if (root) {
        delete_tree(root->left_);
        delete_tree(root->right_);
        delete root;
    }
}

template <class T, class U>
void RBTree<T, U>::insert_fixup(RBNode<T, U> *&root, RBNode<T, U> *node) {
    RBNode<T, U> *parent = node->parent_;
    while (node != RBTree::root_ && parent->color_ == RED) {
        RBNode<T, U> *gparent = parent->parent_;
        RBNode<T, U> *uncle = (gparent->left_ == parent) ? gparent->right_ : gparent->left_;
        bool left  = (gparent->left_ == parent);
        bool step1 = (uncle && (uncle->color_ == RED));
        if (step1) {
            parent->color_  = BLACK;
            uncle->color_   = BLACK;
            gparent->color_ = RED;
            node = gparent;
            parent = node->parent_;
        }
        if (left && !step1) {
            if (parent->right_ == node) {
                left_rotate(parent);
                std::swap(node, parent);
            }
            right_rotate(gparent);
        }
        if (!left && !step1) {
            if (parent->left_ == node) {
                right_rotate(parent);
                std::swap(parent, node);
            }
            left_rotate(gparent);
        }
        if (!step1) {
            parent->color_  = BLACK;
            gparent->color_ = RED;
            break;
        }
    }
    root->color_ = BLACK;
}

template <class T, class U>
void RBTree<T, U>::left_rotate(RBNode<T, U> *x) {
    RBNode<T, U> *y = x->right_;
    x->right_ = y->left_;
    if (y->left_) {
        y->left_->parent_ = x;
    }
    y->parent_ = x->parent_;
    transplant(x->parent_, y, x);
    y->left_ = x;
    x->parent_ = y;
}

template <class T, class U>
void RBTree<T, U>::right_rotate(RBNode<T, U> *x) {
    RBNode<T, U> *y = x->left_;
    x->left_ = y->right_;
    if (y->right_) {
        y->right_->parent_ = x;
    }
    y->parent_ = x->parent_;
    transplant(x->parent_, y, x);
    y->right_ = x;
    x->parent_ = y;
}

template <class T, class U>
void RBTree<T, U>::transplant(RBNode<T, U> *u, RBNode<T, U> *v, RBNode<T, U> const *node) {
    if (!u) {
        root_ = v;
    } else {
        if (u->left_ == node) {
            u->left_  = v;
        } else {
            u->right_ = v;
        }
    }
}

template <class T, class U>
void RBTree<T, U>::remove(T key) {
    RBNode<T, U> *node = lookup(key);
    if (node) {
        RBNode<T, U> *ins_child  = nullptr;
        RBNode<T, U> *ins_parent = nullptr;
        RBColor color;

        if (node->left_ && node->right_) {
            RBNode<T, U> *ins_node = max(node->left_);
            transplant(node->parent_, ins_node, node);
            ins_child  = ins_node->left_;
            ins_parent = ins_node->parent_;
            color      = ins_node->color_;

            if (ins_parent == node) {
                ins_parent = ins_node;
            } else {
                if (ins_child) {
                    ins_child->parent_ = ins_parent;
                }
                ins_parent->right_   = ins_child;
                ins_node->left_      = node->left_;
                node->left_->parent_ = ins_node;
            }

            ins_node->right_      = node->right_;
            ins_node->parent_     = node->parent_;
            ins_node->color_      = node->color_;
            node->right_->parent_ = ins_node;

        } else {
            ins_child = (node->left_) ? node->left_ : node->right_;
            ins_parent = node->parent_;
            color = node->color_;
            if (ins_child) {
                ins_child->parent_ = ins_parent;
            }
            transplant(ins_parent, ins_child, node);
        }

        if (color == BLACK) {
            remove_fixup(root_, ins_child, ins_parent);
        }
        delete node;
    }
}

template <class T, class U>
inline bool is_black(RBNode<T, U> *node) {
    return (!node || node->color_ == BLACK);
}

template <class T, class U>
void RBTree<T, U>::remove_fixup(RBNode<T, U> *&root, RBNode<T, U> *node, RBNode<T, U> *parent) {
    while (is_black(node) && (node != root_)) {
        RBNode<T, U> *w_node = (parent->left_ == node) ? parent->right_ : parent->left_;
        if (parent->left_ == node) {
            if (w_node->color_ == RED) {
                w_node->color_ = BLACK;
                parent->color_ = RED;
                left_rotate(parent);
                w_node = parent->right_;
            } else {
                if (is_black(w_node->right_)) {
                    w_node->left_->color_ = BLACK;
                    w_node->color_ = RED;
                    right_rotate(w_node);
                    w_node = parent->right_;
                }
                w_node->color_ = parent->color_;
                parent->color_ = BLACK;
                w_node->right_->color_ = BLACK;
                left_rotate(parent);
                node = root;
                break;
            }
        } else {
            if (w_node->color_ == RED) {
                w_node->color_ = BLACK;
                parent->color_ = RED;
                right_rotate(parent);
                w_node = parent->left_;
            }
            if (is_black(w_node->left_) && is_black(w_node->right_)) {
                w_node->color_ = RED;
                node = parent;
                parent = node->parent_;
            } else {
                if (is_black(w_node->left_)) {
                    w_node->right_->color_ = BLACK;
                    w_node->color_ = RED;
                    left_rotate(w_node);
                    w_node = parent->left_;
                }
                w_node->color_ = parent->color_;
                parent->color_ = BLACK;
                w_node->left_->color_ = BLACK;
                right_rotate(parent);
                node = root;
                break;
            }
        }
    }
    if (node) {
        node->color_ = BLACK;
    }
}

template <class T, class U>
RBNode<T, U> * RBTree<T, U>::lookup(T key) {
    RBNode<T, U> *result = nullptr;
    RBNode<T, U> *tree = root_;
    while (tree && !result) {
        if (key < tree->key_) {
            tree = tree->left_;
        } else if (key > tree->key_) {
            tree = tree->right_;
        } else {
            result = tree;
        }
    }
    return result;
}

template <class T, class U>
RBNode<T, U> * RBTree<T, U>::min(RBNode<T, U> *tree) const {
    if (!tree) {
        tree = root_;
    }
    while (tree && tree->left_) {
        tree = tree->left_;
    }
    return tree;
}

template <class T, class U>
RBNode<T, U> * RBTree<T, U>::max(RBNode<T, U> *tree) const {
    if (!tree) {
        tree = root_;
    }
    while (tree && tree->right_) {
        tree = tree->right_;
    }
    return tree;
}

template <class T, class U>
RBNode<T, U> * RBTree<T, U>::successor(T key) const {
    RBNode<T, U> *result = nullptr;
    RBNode<T, U> *successor = nullptr;
    RBNode<T, U> *tree = root_;
    while (tree && !result) {
        if (key < tree->key_) {
            successor = tree;
            tree = tree->left_;
        } else if (key > tree->key_) {
            tree = tree->right_;
        } else {
            if (tree->right_) {
                result = min(tree->right_);
            } else {
                tree = nullptr;
            }
            if (!result) {
                result = successor;
            }
        }
    }
    return result;
}

template <class T, class U>
RBNode<T, U> * RBTree<T, U>::predecessor(T key) const {
    RBNode<T, U> *result = nullptr;
    RBNode<T, U> *predecessor = nullptr;
    RBNode<T, U> *tree = root_;
    while (tree && !result) {
        if (key < tree->key_) {
            tree = tree->left_;
        } else if (key > tree->key_) {
            predecessor = tree;
            tree = tree->right_;
        } else {
            if (tree->left_) {
                result = max(tree->left_);
            } else {
                tree = nullptr;
            }
            if (!result) {
                result = predecessor;
            }
        }
    }
    return result;
}

template <class T, class U>
std::ostream& operator<<(std::ostream& out, RBTree<T, U> & tree) {
    tree.print_subtree(out, tree.root_, '*', 0);
    return out;
}

template <class T, class U>
void RBTree<T, U>::print_subtree(std::ostream& out, RBNode<T, U> *root, char lr, int lvl) {
    ++lvl;
    if (root) {
        print_subtree(out, root->left_, 'L', lvl);
        out << lr << lvl << ':' << *root << ' ';
        print_subtree(out, root->right_, 'R', lvl);
    }
}

}  // namespace s21
