#include <gtest/gtest.h>
#include <queue>
#include <initializer_list>

#include "../classes/s21_queue.hpp"

void compare_queues(s21::queue <float> &s21_q, std::queue <float> &std_q) {
    while (s21_q.size() || std_q.size()) {
        ASSERT_EQ(s21_q.front(), std_q.front());
        ASSERT_EQ(s21_q.back(), std_q.back());
        s21_q.pop();
        std_q.pop();
    }
}

TEST(s21_queue_case, alltogather) {
    // default
    s21::queue <float> s21_queue;
    std::queue <float> std_queue;
    ASSERT_EQ(s21_queue.empty(), std_queue.empty());

    s21_queue.push(777);
    std_queue.push(777);
    s21_queue.push(888);
    std_queue.push(888);
    ASSERT_EQ(s21_queue.size(), std_queue.size());
    compare_queues(s21_queue, std_queue);

    // initializer_list
    std::initializer_list <float> data{ 1, 2, 3, 4, 5 };
    s21::queue <float> s21_queue2{ 1, 2, 3, 4, 5 };
    std::queue <float> std_queue2(data);
    ASSERT_EQ(s21_queue2.size(), std_queue2.size());
    compare_queues(s21_queue2, std_queue2);

    // copy
    std::initializer_list <float> data_tmp{ 6, 7, 8, 9, 10 };
    s21::queue <float> s21_queue_tmp{ 6, 7, 8, 9, 10 };
    std::queue <float> std_queue_tmp(data_tmp);

    s21::queue <float> s21_queue3(s21_queue_tmp);
    std::queue <float> std_queue3(std_queue_tmp);
    ASSERT_EQ(s21_queue3.size(), std_queue3.size());

    // move constructor
    s21::queue <float> s21_queue4(std::move(s21_queue3));
    std::queue <float> std_queue4(std::move(std_queue3));
    ASSERT_EQ(s21_queue4.size(), std_queue4.size());
    compare_queues(s21_queue4, std_queue4);

    // move operator
    s21::queue <float> s21_queue5 = std::move(s21_queue_tmp);
    std::queue <float> std_queue5(data_tmp);
    ASSERT_EQ(s21_queue5.size(), std_queue5.size());
    compare_queues(s21_queue5, std_queue5);
}

TEST(s21_queue_case, swap) {
    std::initializer_list <float> data1{ 5, 4, 3, 2, 1 };
    s21::queue <float> s21_q1(data1);
    std::queue <float> std_q1(data1);
    std::initializer_list <float> data2{ 6, 7, 8, 9, 10 };
    s21::queue <float> s21_q2(data2);
    std::queue <float> std_q2(data2);
    s21_q1.swap(s21_q2);
    std_q1.swap(std_q2);
    compare_queues(s21_q1, std_q1);
    compare_queues(s21_q2, std_q2);
}
