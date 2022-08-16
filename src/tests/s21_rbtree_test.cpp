#include <gtest/gtest.h>

#include "../classes/s21_rbtree.hpp"
#include <vector>
#include <iostream>

TEST(s21_rbtree_case, base) {
    s21::RBTree<int, std::vector<int>*> tree;
    std::vector<int> data{ 14, 4, 18, 3, 8, 21, 6, 11, 5, 1 };
    for (auto i : data) {
        tree.insert_key(i);
    }
    tree.remove(8);
    tree.remove(5);
    std::vector<int> data2{ 9, 10, 8, 7, 13 };
    for (auto i : data2) {
        tree.insert_key(i);
    }
    std::vector<int> data3{ 6, 14, 13, 4 };
    for (auto i : data3) {
        tree.remove(i);
    }
    std::vector<int> data4{ 4, 2, 6, 20, 19, 17, 16 };
    for (auto i : data4) {
        tree.insert_key(i);
    }
    std::vector<int> data5{ 18, 20, 8, 10 };
    for (auto i : data5) {
        tree.remove(i);
    }

    std::vector<int> test{ 1, 2, 3, 4, 6, 7, 9, 11, 16, 17, 19, 21 };
    int val = tree.max()->key_;
    auto i = test.end();
    --i;
    for (; i != test.begin(); --i) {
        ASSERT_EQ(*i, val);
        val = tree.predecessor(val)->key_;
    }
    ASSERT_EQ(*i, val);
}
