#include <gtest/gtest.h>
#include <set>
#include <initializer_list>

#include "../classes/s21_set.hpp"

void compare_lists(s21::set <float> const &s21_set, std::set <float> const &std_set) {
    auto s21_i = s21_set.begin();
    auto std_i = std_set.begin();
    while (s21_i != s21_set.end() || std_i != std_set.end()) {
        ASSERT_EQ(*s21_i, *std_i);
        ++s21_i;
        ++std_i;
    }
}

TEST(s21_set_case, constructors_capacity) {
    // default
    s21::set <double> s21_set;
    std::set <double> std_set;
    ASSERT_EQ(s21_set.empty(), std_set.empty());

    // initializer_list
    s21::set <float> s21_set2{ 5, 4, 3, 2, 1 };
    std::set <float> std_set2{ 5, 4, 3, 2, 1 };
    ASSERT_EQ(s21_set2.size(), std_set2.size());
    compare_lists(s21_set2, std_set2);

    // copy
    s21::set <float> s21_set3(s21_set2);
    std::set <float> std_set3(std_set2);
    ASSERT_EQ(s21_set3.size(), std_set3.size());
    compare_lists(s21_set3, std_set3);

    // move constructor
    s21::set <float> s21_set4(std::move(s21_set3));
    std::set <float> std_set4(std::move(std_set3));
    ASSERT_EQ(s21_set4.size(), std_set4.size());
    compare_lists(s21_set4, std_set4);

    // move operator
    std::set <float> std_set5 = std::move(std_set4);
    s21::set <float> s21_set5 = std::move(s21_set4);
    ASSERT_EQ(s21_set5.size(), std_set5.size());
    compare_lists(s21_set5, std_set5);

    // max_size
    ASSERT_EQ(s21_set5.max_size(), std_set5.max_size());
}

TEST(s21_set_case, clear) {
    s21::set <float> s21_set{ 5, 4, 3, 2, 1 };
    s21_set.clear();
    ASSERT_EQ(s21_set.size(), 0);
}

TEST(s21_set_case, eq_dec) {
    s21::set <float> s21_set{ 5, 4, 3, 2, 1 };
    auto pos = s21_set.begin();
    auto pos2 = s21::set<float>::iterator(pos);
    ++pos2;
    --pos2;
    ASSERT_EQ(pos, pos2);
}

TEST(s21_set_case, insert_erase_find) {
    std::set<float> std_set{ 1, 2, 3, 4, 5, 5 };
    s21::set <float> s21_set;

    for (auto i : std_set) {
        auto res = s21_set.insert(i);
        ASSERT_EQ(*res.first, i);
        ASSERT_EQ(res.second, true);
    }
    ASSERT_EQ(s21_set.size(), std_set.size());
    compare_lists(s21_set, std_set);

    auto res = s21_set.insert(1);
    ASSERT_EQ(res.second, false);

    std_set.erase(std_set.find(2));
    s21_set.erase(s21_set.find(2));
    std_set.erase(std_set.find(4));
    s21_set.erase(s21_set.find(4));
    s21_set.erase(s21_set.find(777));
    ASSERT_EQ(s21_set.size(), std_set.size());
    compare_lists(s21_set, std_set);
}

TEST(s21_set_case, swap) {
    s21::set <float> s21_set1{ 5, 4, 3, 2, 1 };
    std::set <float> std_set1{ 5, 4, 3, 2, 1 };
    s21::set <float> s21_set2{ 6, 7, 8, 9, 10 };
    std::set <float> std_set2{ 6, 7, 8, 9, 10 };
    s21_set1.swap(s21_set2);
    std_set1.swap(std_set2);
    ASSERT_EQ(s21_set1.size(), std_set1.size());
    compare_lists(s21_set1, std_set1);
    ASSERT_EQ(s21_set2.size(), std_set2.size());
    compare_lists(s21_set2, std_set2);
}

TEST(s21_set_case, merge_contains) {
    s21::set <float> s21_set1{ 1, 2, 3, 4 };
    std::set <float> std_set1{ 1, 2, 3, 4 };
    s21::set <float> s21_set2{ 4, 5, 6 };
    std::set <float> std_set2{ 4, 5, 6 };
    s21_set1.merge(s21_set2);
    std_set1.merge(std_set2);
    ASSERT_EQ(s21_set1.size(), std_set1.size());
    compare_lists(s21_set1, std_set1);
    ASSERT_EQ(s21_set2.size(), std_set2.size());
    compare_lists(s21_set2, std_set2);

    ASSERT_EQ(s21_set1.contains(1), true);
    ASSERT_EQ(s21_set1.contains(10), false);
}

TEST(s21_set_case, emplace) {
    s21::set <float> s21_set{ 1, 2, 3, 4, 5 };
    std::set <float> std_set{ 1, 2, 3, 4, 5, 6, 7, 8 };
    auto [emp_pos, emp_res] = s21_set.emplace(6, 7, 8);
    ASSERT_EQ(*emp_pos, 8);
    ASSERT_EQ(emp_res, true);
    compare_lists(s21_set, std_set);
}
