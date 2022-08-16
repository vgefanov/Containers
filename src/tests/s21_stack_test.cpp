#include "../classes/s21_stack.hpp"

#include <gtest/gtest.h>

#include <initializer_list>
#include <stack>

void compare_stacks(s21::stack<float> &s21_q, std::stack<float> &std_q) {
    while (s21_q.size() || std_q.size()) {
        ASSERT_EQ(s21_q.top(), std_q.top());
        s21_q.pop();
        std_q.pop();
    }
}

TEST(s21_stack_case, alltogather) {
    // default
    s21::stack<float> s21_stack;
    std::stack<float> std_stack;
    ASSERT_EQ(s21_stack.empty(), std_stack.empty());

    s21_stack.push(1);
    std_stack.push(1);
    s21_stack.push(2);
    std_stack.push(2);
    s21_stack.push(3);
    std_stack.push(3);
    s21_stack.push(2);
    std_stack.push(2);
    ASSERT_EQ(s21_stack.size(), std_stack.size());
    compare_stacks(s21_stack, std_stack);

    // initializer_list
    std::initializer_list<float> data{1, 2, 3, 4, 5};
    s21::stack<float> s21_stack2{1, 2, 3, 4, 5};
    std::stack<float> std_stack2(data);
    ASSERT_EQ(s21_stack2.size(), std_stack2.size());
    compare_stacks(s21_stack2, std_stack2);

    // copy
    std::initializer_list<float> data_tmp{6, 7, 8, 9, 10};
    s21::stack<float> s21_stack_tmp{6, 7, 8, 9, 10};
    std::stack<float> std_stack_tmp(data_tmp);

    s21::stack<float> s21_stack3(s21_stack_tmp);
    std::stack<float> std_stack3(std_stack_tmp);
    ASSERT_EQ(s21_stack3.size(), std_stack3.size());

    // move constructor
    s21::stack<float> s21_stack4(std::move(s21_stack3));
    std::stack<float> std_stack4(std::move(std_stack3));
    ASSERT_EQ(s21_stack4.size(), std_stack4.size());
    compare_stacks(s21_stack4, std_stack4);

    // move operator
    s21::stack<float> s21_stack5 = std::move(s21_stack_tmp);
    std::stack<float> std_stack5(data_tmp);
    ASSERT_EQ(s21_stack5.size(), std_stack5.size());
    compare_stacks(s21_stack5, std_stack5);
}

TEST(s21_stack_case, swap) {
    std::initializer_list<float> data1{5, 4, 3, 2, 1};
    s21::stack<float> s21_q1(data1);
    std::stack<float> std_q1(data1);
    std::initializer_list<float> data2{6, 7, 8, 9, 10};
    s21::stack<float> s21_q2(data2);
    std::stack<float> std_q2(data2);
    s21_q1.swap(s21_q2);
    std_q1.swap(std_q2);
    compare_stacks(s21_q1, std_q1);
    compare_stacks(s21_q2, std_q2);
}
