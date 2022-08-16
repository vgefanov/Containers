#include <gtest/gtest.h>

#include <vector>

#include "../classes/s21_vector.hpp"

TEST(s21_vector_case, create_1) {
    s21::vector<float> s21_vector;
    std::vector<float> std_vector;
    ASSERT_EQ(s21_vector.empty(), std_vector.empty());
}

TEST(s21_vector_case, create_2) {
    s21::vector<int> s21_vector(0);
    std::vector<int> std_vector(0);
    ASSERT_EQ(s21_vector.size(), std_vector.size());
}

TEST(s21_vector_case, create_3) {
    s21::vector<int> s21_vector(5);
    for (long unsigned i = 0; i < s21_vector.size(); i++) s21_vector.set_vector_value(i, i + 1);
    std::vector<int> std_vector(5);
    ASSERT_EQ(s21_vector.size(), std_vector.size());
    ASSERT_EQ(s21_vector.capacity(), std_vector.capacity());
    for (long unsigned i = 0; i < s21_vector.size(); i++) ASSERT_EQ(s21_vector[i], i + 1);
}

TEST(s21_vector_case, create_4) {
    std::initializer_list<int> data{1, 2, 3, 4};
    s21::vector<int> s21_vector(data);
    std::vector<int> std_vector(data);
    ASSERT_EQ(s21_vector.size(), std_vector.size());
}

TEST(s21_vector_case, copy) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    s21::vector<int> vector2(vector);
    ASSERT_EQ(vector.size(), vector2.size());
    ASSERT_EQ(vector.capacity(), vector2.capacity());
    for (long unsigned i = 0; i < vector.size(); i++) ASSERT_EQ(vector[i], vector2[i]);
}

TEST(s21_vector_case, move) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    s21::vector<int> vector2(std::move(vector));
    ASSERT_EQ(vector.size(), 0);
    ASSERT_EQ(vector.capacity(), 0);
    ASSERT_EQ(vector2.size(), 5);
    ASSERT_EQ(vector2.capacity(), 5);
    for (long unsigned i = 0; i < vector2.size(); i++) ASSERT_EQ(vector2[i], i + 1);
}

TEST(s21_vector_case, reference_at) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    ASSERT_EQ(vector.at(0), 1);
    vector.clear();
}

TEST(s21_vector_case, reference_front) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    ASSERT_EQ(vector.front(), 1);
    vector.remove_vector();
}

TEST(s21_vector_case, reference_back) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    ASSERT_EQ(vector.back(), 5);
    vector.remove_vector();
}

TEST(s21_vector_case, data) {
    s21::vector<int> vector(5);
    int *v = vector.data();
    *v = 1;
    ++v;
    *v = 2;
    ASSERT_EQ(vector[0], 1);
    ASSERT_EQ(vector[1], 2);
}

TEST(s21_vector_case, begin_end) {
    s21::vector<int> vector(5);
    ASSERT_FALSE(vector.begin() == vector.end());
}

TEST(s21_vector_case, max_size) {
    s21::vector<int> vector(5);
    std::vector<int> vector2(5);
    ASSERT_EQ(vector.max_size(), vector2.max_size());
}

TEST(s21_vector_case, reserve) {
    s21::vector<int> vector{2, 4, 6};
    std::vector<int> vector2{2, 4, 6};
    vector.reserve(6);
    vector2.reserve(6);
    EXPECT_EQ(vector.capacity(), vector2.capacity());
}

TEST(s21_vector_case, shrink_to_fit) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    ASSERT_EQ(vector.size(), 5);
    ASSERT_EQ(vector.capacity(), 5);
    vector.push_back(6);
    ASSERT_EQ(vector.size(), 6);
    ASSERT_EQ(vector.capacity(), 10);
    vector.shrink_to_fit();
    ASSERT_EQ(vector.size(), 6);
    ASSERT_EQ(vector.capacity(), 6);
    for (long unsigned i = 0; i < vector.size(); i++) ASSERT_EQ(vector[i], i + 1);
}

TEST(s21_vector_case, insert) {
    s21::vector<int> vector;
    std::vector<int> vector2;
    vector.push_back(1);
    vector.push_back(3);
    vector.push_back(5);
    vector2.push_back(1);
    vector2.push_back(3);
    vector2.push_back(5);
    s21::vector<int>::iterator pos = vector.begin();
    std::vector<int>::iterator pos2 = vector2.begin();
    pos = vector.insert(pos, 1);
    pos2 = vector2.insert(pos2, 1);
    ASSERT_EQ(*pos, *pos2);
}

TEST(s21_vector_case, insert_2) {
    s21::vector<int> vector;
    std::vector<int> vector2;
    vector.push_back(1);
    vector.push_back(3);
    vector.push_back(5);
    vector.push_back(7);
    vector2.push_back(1);
    vector2.push_back(3);
    vector2.push_back(5);
    vector2.push_back(7);
    s21::vector<int>::iterator pos = vector.begin();
    std::vector<int>::iterator pos2 = vector2.begin();
    pos = vector.insert(pos + 3, 1);
    pos2 = vector2.insert(pos2 + 3, 1);
    ASSERT_EQ(*pos, *pos2);
}

TEST(s21_vector_case, erase) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    auto pos = vector.begin();
    vector.erase(pos);
    ASSERT_EQ(vector.size(), 5 - 1);
    ASSERT_EQ(vector.capacity(), 5);
    for (long unsigned i = 0; i < vector.size(); i++) ASSERT_EQ(vector[i], i + 2);
}

TEST(s21_vector_case, pop_back) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    vector.pop_back();
    ASSERT_EQ(vector.size(), 5 - 1);
    ASSERT_EQ(vector.capacity(), 5);
    for (long unsigned i = 0; i < vector.size(); i++) ASSERT_EQ(vector[i], i + 1);
}

TEST(s21_vector_case, swap) {
    s21::vector<int> vector(5);
    for (long unsigned i = 0; i < vector.size(); i++) vector.set_vector_value(i, i + 1);
    s21::vector<int> vector2(7);
    for (long unsigned i = 0; i < vector2.size(); i++) vector2.set_vector_value(i, i + 1);
    vector.swap(vector2);
    for (long unsigned i = 0; i < vector.size(); i++) ASSERT_EQ(vector[i], i + 1);
    for (long unsigned i = 0; i < vector2.size(); i++) ASSERT_EQ(vector2[i], i + 1);
}

TEST(s21_vector_case, emplace) {
    s21::vector<int> vector{1, 2, 3, 4, 5};
    std::vector<int> vector2{1, 8, 7, 6, 2, 3, 4, 5};
    auto pos = vector.begin();
    ++pos;
    auto result = vector.emplace(pos, 8, 7, 6);
    ASSERT_EQ(*result, 6);

    vector.emplace_back(11, 22, 33);
    std::vector<int> vector3{1, 1, 1, 8, 2, 3, 4, 5, 11, 22, 33};
    for (long unsigned i = 0; i < vector.size(); i++) ASSERT_EQ(vector[i], vector3[i]);
}
