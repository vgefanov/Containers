#include "../classes/s21_array.hpp"

#include <gtest/gtest.h>

#include <array>
#include <initializer_list>

TEST(s21_array_case, array1) {
    s21::Array<int, 3> arr1;
    s21::Array<char, 5> arr2;
    char test[] = {'a', 'b', 'c', 'd', 'e'};

    for (std::size_t i = 0; i < arr1.size(); i++) arr1[i] = i;
    for (std::size_t i = 0; i < arr2.size(); i++) arr2[i] = test[i];
    ASSERT_EQ(arr1.size(), 3);
    ASSERT_EQ(arr2.size(), 5);

    for (size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], i);
    for (size_t i = 0; i < arr2.size(); i++) ASSERT_EQ(arr2[i], test[i]);
}

TEST(s21_array_case, array2) {
    s21::Array<int, 10> arr1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ASSERT_EQ(arr1.size(), 10);

    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], i + 1);
}

TEST(s21_array_case, array3) {
    s21::Array<int, 10> arr1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    s21::Array<int, 10> arr2(arr1);
    ASSERT_EQ(arr1.size(), 10);
    ASSERT_EQ(arr2.size(), 10);
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr2[i], i + 1);
}

TEST(s21_array_case, array4) {
    s21::Array<int, 10> arr1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    s21::Array<int, 10> arr2(std::move(arr1));
    ASSERT_EQ(arr1.size(), 10);
    ASSERT_EQ(arr2.size(), 10);
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr2[i], i + 1);

    s21::Array<int, 10> arr3;
    ASSERT_FALSE(arr3.empty());

    s21::Array<int, 0> arr4;
    ASSERT_TRUE(arr4.empty());
}

TEST(s21_array_case, array5) {
    s21::Array<int, 10> arr1{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    ASSERT_EQ(arr1.size(), 10);
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], i + 1);
    ASSERT_EQ(arr1.front(), 1);
    ASSERT_EQ(arr1.back(), 10);
}

TEST(s21_array_case, array6) {
    s21::Array<int, 5> arr1{1, 2, 3, 4, 5};
    ASSERT_EQ(arr1.size(), 5);
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], i + 1);
    int *p = arr1.data();
    *p = 10;
    p++;
    *p = 20;
    p++;
    *p = 30;
    p++;
    *p = 40;
    p++;
    *p = 50;
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], (i + 1) * 10);
}

TEST(s21_array_case, array7) {
    s21::Array<int, 5> arr1{1, 2, 3, 4, 5};
    ASSERT_EQ(arr1.size(), 5);
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], i + 1);
    int *p = arr1.begin();
    ASSERT_EQ(*p, 1);
    p = arr1.end();
    p--;
    ASSERT_EQ(*p, 5);
}

TEST(s21_array_case, array8) {
    s21::Array<int, 5> arr1{1, 2, 3, 4, 5};
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], i + 1);
    s21::Array<int, 5> arr2{1, 2, 3, 4, 5};
    // for (std::size_t i = 0; i < arr2.size(); i++) ASSERT_EQ(arr2[i], i + 1);

    arr1.swap(arr2);

    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], i + 1);
    for (std::size_t i = 0; i < arr2.size(); i++) ASSERT_EQ(arr2[i], i + 1);
}

TEST(s21_array_case, array9) {
    s21::Array<int, 5> arr1;
    arr1.fill(100);
    for (std::size_t i = 0; i < arr1.size(); i++) ASSERT_EQ(arr1[i], 100);
}
