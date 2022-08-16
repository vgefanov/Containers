#include <gtest/gtest.h>
#include <set>
#include <initializer_list>
#include <fstream>

#include "../classes/s21_multiset.hpp"

void compare_multisets(s21::multiset <float> const &s21_ms, std::multiset <float> const &std_ms) {
    auto s21_i = s21_ms.begin();
    auto std_i = std_ms.begin();
    while (s21_i != s21_ms.end() || std_i != std_ms.end()) {
        ASSERT_EQ(*s21_i, *std_i);
        ++s21_i;
        ++std_i;
    }
}

TEST(s21_multiset_case, constructors_capacity) {
    // default
    s21::multiset<float> s21_ms;
    std::multiset<float> std_ms;
    ASSERT_EQ(s21_ms.empty(), std_ms.empty());

    // initializer_list
    s21::multiset <float> s21_ms2{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    std::multiset <float> std_ms2{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    ASSERT_EQ(s21_ms2.size(), std_ms2.size());
    compare_multisets(s21_ms2, std_ms2);

    // copy
    s21::multiset <float> s21_ms3(s21_ms2);
    std::multiset <float> std_ms3(std_ms2);
    ASSERT_EQ(s21_ms3.size(), std_ms3.size());
    compare_multisets(s21_ms3, std_ms3);

    // move constructor
    s21::multiset <float> s21_ms4(std::move(s21_ms3));
    std::multiset <float> std_ms4(std::move(std_ms3));
    ASSERT_EQ(s21_ms4.size(), std_ms4.size());
    compare_multisets(s21_ms4, std_ms4);

    // move operator
    std::multiset <float> std_ms5 = std::move(std_ms4);
    s21::multiset <float> s21_ms5 = std::move(s21_ms4);
    ASSERT_EQ(s21_ms5.size(), std_ms5.size());
    compare_multisets(s21_ms5, std_ms5);

    ASSERT_EQ(s21_ms5.max_size(), std_ms5.max_size());
}

TEST(s21_multiset_case, clear) {
    s21::multiset <float> s21_ms{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    s21_ms.clear();
    ASSERT_EQ(s21_ms.size(), 0);
}

TEST(s21_multiset_case, eq_dec) {
    s21::multiset <float> s21_ms{ 5, 4, 3, 2, 2, 2, 1 };
    auto pos = s21_ms.begin();
    auto pos2 = s21::multiset<float>::iterator(pos);
    ++pos2;
    ++pos2;
    --pos2;
    --pos2;
    ASSERT_EQ(pos, pos2);
}

TEST(s21_multiset_case, insert_erase_find) {
    std::multiset <float> std_ms{ 1, 2, 3, 4, 5 };
    s21::multiset <float> s21_ms;

    for (auto i : std_ms) {
        auto res = s21_ms.insert(i);
        ASSERT_EQ(*res, i);
    }
    ASSERT_EQ(s21_ms.size(), std_ms.size());
    compare_multisets(s21_ms, std_ms);

    for (auto i : std::initializer_list{1, 2, 3, 1, 2, 1}) {
        s21_ms.insert(i);
        std_ms.insert(i);
    }
    ASSERT_EQ(s21_ms.size(), std_ms.size());
    compare_multisets(s21_ms, std_ms);

    s21_ms.erase(s21_ms.find(1));
    std_ms.erase(std_ms.find(1));
    s21_ms.erase(s21_ms.find(4));
    std_ms.erase(std_ms.find(4));
    s21_ms.erase(s21_ms.find(777));
    ASSERT_EQ(s21_ms.size(), std_ms.size());
    compare_multisets(s21_ms, std_ms);
}

TEST(s21_multiset_case, swap) {
    s21::multiset <float> s21_ms1{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    std::multiset <float> std_ms1{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    s21::multiset <float> s21_ms2{ 6, 7, 8, 9, 10, 9, 8, 7, 6 };
    std::multiset <float> std_ms2{ 6, 7, 8, 9, 10, 9, 8, 7, 6 };
    s21_ms1.swap(s21_ms2);
    std_ms1.swap(std_ms2);
    ASSERT_EQ(s21_ms1.size(), std_ms1.size());
    compare_multisets(s21_ms1, std_ms1);
    ASSERT_EQ(s21_ms2.size(), std_ms2.size());
    compare_multisets(s21_ms2, std_ms2);
}

TEST(s21_multiset_case, merge_contains) {
    s21::multiset <float> s21_ms1{ 1, 2, 3, 4 };
    std::multiset <float> std_ms1{ 1, 2, 3, 4 };
    s21::multiset <float> s21_ms2{ 4, 4, 5, 6 };
    std::multiset <float> std_ms2{ 4, 4, 5, 6 };
    s21_ms1.merge(s21_ms2);
    std_ms1.merge(std_ms2);
    ASSERT_EQ(s21_ms1.size(), std_ms1.size());
    compare_multisets(s21_ms1, std_ms1);
    ASSERT_EQ(s21_ms2.size(), std_ms2.size());
    compare_multisets(s21_ms2, std_ms2);

    ASSERT_EQ(s21_ms1.contains(1), true);
    ASSERT_EQ(s21_ms1.contains(10), false);
}

TEST(s21_multiset_case, count) {
    s21::multiset <float> s21_ms{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    std::multiset <float> std_ms{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    ASSERT_EQ(s21_ms.count(5), std_ms.count(5));
}

TEST(s21_multiset_case, equal_range) {
    s21::multiset <float> s21_ms{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    std::multiset <float> std_ms{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    auto [s21_l, s21_u] = s21_ms.equal_range(2);
    auto [std_l, std_u] = std_ms.equal_range(2);
    while (s21_l != s21_u || (std_l != std_u)) {
        ASSERT_EQ(*s21_l, *std_l);
        ++s21_l;
        ++std_l;
    }
}

TEST(s21_multiset_case, lower_upper_bound) {
    s21::multiset <float> s21_ms{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    std::multiset <float> std_ms{ 5, 4, 3, 2, 1, 2, 3, 4, 5 };
    auto s21_pos = s21_ms.lower_bound(2);
    auto std_pos = std_ms.lower_bound(2);
    while (s21_pos != s21_ms.end() || (std_pos != std_ms.end())) {
        ASSERT_EQ(*s21_pos, *std_pos);
        ++s21_pos;
        ++std_pos;
    }

    s21_pos = s21_ms.upper_bound(2);
    std_pos = std_ms.upper_bound(2);
    while (s21_pos != s21_ms.end() || (std_pos != std_ms.end())) {
        ASSERT_EQ(*s21_pos, *std_pos);
        ++s21_pos;
        ++std_pos;
    }
}

TEST(s21_multiset_case, emplace) {
    s21::multiset <float> s21_ms{ 1, 2, 3, 4, 5 };
    std::multiset <float> std_ms{ 1, 2, 3, 4, 5, 6, 7, 8 };
    auto [emp_pos, emp_res] = s21_ms.emplace(6, 7, 8);
    ASSERT_EQ(*emp_pos, 8);
    ASSERT_EQ(emp_res, true);
    compare_multisets(s21_ms, std_ms);
}

TEST(s21_multiset_case, out_test_for_coverage) {
    s21::multiset <float> s21_ms{ 1, 2, 3, 4, 5, 5 };
    std::ofstream out("/dev/null");
    out << s21_ms << std::endl;
}
