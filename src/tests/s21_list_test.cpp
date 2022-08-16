#include <gtest/gtest.h>
#include <list>
#include <initializer_list>

#include "../classes/s21_list.hpp"

void compare_lists(s21::list <float> const &s21_list, std::list <float> const &std_list) {
    auto s21_i = s21_list.begin();
    auto std_i = std_list.begin();
    while (s21_i != s21_list.end() || std_i != std_list.end()) {
        ASSERT_EQ(*s21_i, *std_i);
        ++s21_i;
        ++std_i;
    }
}

TEST(s21_list_case, constructors_capacity) {
    // default
    s21::list <float> s21_list;
    std::list <float> std_list;
    ASSERT_EQ(s21_list.empty(), std_list.empty());

    // parameterized
    s21::list <float> s21_list2(3);
    std::list <float> std_list2(3);
    ASSERT_EQ(s21_list2.size(), std_list2.size());
    compare_lists(s21_list2, std_list2);

    // initializer_list
    std::initializer_list <float> data{ 5, 4, 3, 2, 1 };
    s21::list <float> s21_list3(data);
    std::list <float> std_list3(data);
    ASSERT_EQ(s21_list3.size(), std_list3.size());
    compare_lists(s21_list3, std_list3);

    // copy
    s21::list <float> s21_list4(s21_list3);
    std::list <float> std_list4(std_list3);
    ASSERT_EQ(s21_list4.size(), std_list4.size());
    compare_lists(s21_list4, std_list4);

    // move constructor
    s21::list <float> s21_list5(std::move(s21_list4));
    std::list <float> std_list5(std::move(std_list4));
    ASSERT_EQ(s21_list5.size(), std_list5.size());
    compare_lists(s21_list5, std_list5);

    // move operator
    s21::list <float> s21_list6 = std::move(s21_list5);
    std::list <float> std_list6{ 5, 4, 3, 2, 1 };
    ASSERT_EQ(s21_list6.size(), std_list6.size());
    compare_lists(s21_list6, std_list6);

    // max_size
    ASSERT_EQ(s21_list.max_size(), std_list.max_size());
}

TEST(s21_list_case, element_access) {
    // front/back
    std::initializer_list <float> data{ 5, 4, 3, 2, 1 };
    s21::list <float> s21_list(data);
    std::list <float> std_list(data);
    ASSERT_EQ(s21_list.front(), std_list.front());
    ASSERT_EQ(s21_list.back(), std_list.back());

    // clear
    s21_list.clear();
    ASSERT_EQ(s21_list.size(), 0);

    // insert - filled list
    std::list <float> std_list_x(data);
    auto pos = std_list_x.begin();
    std_list_x.insert(pos, 777);
    std_list_x.insert(pos, 888);
    auto ins_pos = std_list_x.insert(pos, 999);

    s21::list <float> s21_list_x(data);
    auto pos21 = s21_list_x.begin();
    s21_list_x.insert(pos21, 777);
    s21_list_x.insert(pos21, 888);
    auto ins_pos_21 = s21_list_x.insert(pos21, 999);

    compare_lists(s21_list_x, std_list_x);
    ASSERT_EQ(*ins_pos_21, *ins_pos);

    // insert - empty list
    std::list <float> std_list_y;
    auto pos_y = std_list_y.begin();
    std_list_y.insert(pos_y, 555);
    std_list_y.insert(pos_y, 666);

    s21::list <float> s21_list_y;
    auto pos21y = s21_list_y.begin();
    s21_list_y.insert(pos21y, 555);
    s21_list_y.insert(pos21y, 666);

    compare_lists(s21_list_y, std_list_y);
}

TEST(s21_list_case, erase) {
    // erase
    std::initializer_list <float> data{ 1, 2, 3 };
    s21::list <float> s21_list(data);
    std::list <float> std_list(data);
    auto p21 = s21_list.begin();
    ++p21;
    auto pstd = std_list.begin();
    pstd++;
    s21_list.erase(p21);
    std_list.erase(pstd);
    ASSERT_EQ(s21_list.size(), std_list.size());
    compare_lists(s21_list, std_list);

    p21 = s21_list.begin();
    pstd = std_list.begin();
    s21_list.erase(p21);
    std_list.erase(pstd);
    ASSERT_EQ(s21_list.size(), std_list.size());
    compare_lists(s21_list, std_list);

    p21 = s21_list.begin();
    pstd = std_list.begin();
    s21_list.erase(p21);
    std_list.erase(pstd);
    ASSERT_EQ(s21_list.size(), std_list.size());
    compare_lists(s21_list, std_list);
}

TEST(s21_list_case, push_pop) {
    std::initializer_list <float> data{ 5, 4, 3, 2, 1 };
    s21::list <float> s21_list(data);
    std::list <float> std_list(data);

    s21_list.push_back(777);
    std_list.push_back(777);
    ASSERT_EQ(s21_list.size(), std_list.size());
    compare_lists(s21_list, std_list);

    s21_list.pop_back();
    std_list.pop_back();
    ASSERT_EQ(s21_list.size(), std_list.size());
    compare_lists(s21_list, std_list);

    s21_list.push_front(888);
    std_list.push_front(888);
    ASSERT_EQ(s21_list.size(), std_list.size());
    compare_lists(s21_list, std_list);

    s21_list.pop_front();
    std_list.pop_front();
    ASSERT_EQ(s21_list.size(), std_list.size());
    compare_lists(s21_list, std_list);
}

TEST(s21_list_case, swap) {
    std::initializer_list <float> data1{ 5, 4, 3, 2, 1 };
    s21::list <float> s21_list1(data1);
    std::list <float> std_list1(data1);
    std::initializer_list <float> data2{ 6, 7, 8, 9, 10 };
    s21::list <float> s21_list2(data2);
    std::list <float> std_list2(data2);
    s21_list1.swap(s21_list2);
    std_list1.swap(std_list2);
    compare_lists(s21_list1, std_list1);
    compare_lists(s21_list2, std_list2);
}

TEST(s21_list_case, merge) {
    std::initializer_list <float> data1{ 1, 2, 3 };
    s21::list <float> s21_list1(data1);
    std::list <float> std_list1(data1);
    std::initializer_list <float> data2{ 4, 5, 6 };
    s21::list <float> s21_list2(data2);
    std::list <float> std_list2(data2);
    s21_list1.merge(s21_list2);
    std_list1.merge(std_list2);
    compare_lists(s21_list1, std_list1);
    compare_lists(s21_list2, std_list2);
}

TEST(s21_list_case, splice) {
    std::initializer_list <float> data1{ 1, 2, 3 };
    s21::list <float> s21_list1(data1);
    auto p21 = s21_list1.begin();
    ++p21;
    std::list <float> std_list1(data1);
    std::initializer_list <float> data2{ 4, 5, 6 };
    s21::list <float> s21_list2(data2);
    auto pstd = std_list1.begin();
    ++pstd;
    std::list <float> std_list2(data2);
    s21_list1.splice(p21, s21_list2);
    std_list1.splice(pstd, std_list2);
    compare_lists(s21_list1, std_list1);
    compare_lists(s21_list2, std_list2);
}

TEST(s21_list_case, reverse) {
    std::initializer_list <float> data1{ 1, 2, 3, 4, 5 };
    s21::list <float> s21_list(data1);
    std::initializer_list <float> data2{ 5, 4, 3, 2, 1 };
    std::list <float> std_list(data2);
    s21_list.reverse();
    compare_lists(s21_list, std_list);
}


TEST(s21_list_case, unique) {
    s21::list <float> s21_list{ 1, 2, 2, 3, 4, 5, 3 };
    std::list <float> std_list{ 1, 2, 3, 4, 5 };
    s21_list.unique();
    compare_lists(s21_list, std_list);
}

TEST(s21_list_case, sort) {
    s21::list <float> s21_list{ 5, 4, 3, 2, 1 };
    std::list <float> std_list{ 1, 2, 3, 4, 5 };
    s21_list.sort();
    compare_lists(s21_list, std_list);
}

TEST(s21_list_case, emplace) {
    s21::list <float> s21_list{ 5, 4, 3, 2, 1 };
    std::list <float> std_list{ 5, 6, 7, 8, 4, 3, 2, 1 };
    auto pos = s21_list.begin();
    ++pos;
    auto result = s21_list.emplace(pos, 6, 7, 8);
    ASSERT_EQ(*result, 8);
    compare_lists(s21_list, std_list);

    std_list.emplace(++std_list.begin());
    auto ins_pos = s21_list.begin();
    ++ins_pos;
    s21_list.emplace(ins_pos);

    s21_list.emplace_back(444, 555, 666);
    s21_list.emplace_front(111, 222, 333);
    std::list <float> std_list2{ 111, 222, 333, 5, 0, 6, 7, 8, 4, 3, 2, 1, 444, 555, 666 };
    compare_lists(s21_list, std_list2);
}
