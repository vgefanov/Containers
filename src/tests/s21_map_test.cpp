#include "../classes/s21_map.hpp"

#include <gtest/gtest.h>

#include <initializer_list>
#include <map>

template <typename Key, typename T>
void compare_map(s21::Map<Key, T> &s21_map, std::map<Key, T> &std_map) {
    auto s21_i = s21_map.begin();
    auto std_i = std_map.begin();
    while (s21_i != s21_map.end() || std_i != std_map.end()) {
        ASSERT_EQ(*s21_i, *std_i);
        ++s21_i;
        ++std_i;
    }
}

TEST(s21_map_case, map1) {
    // default
    s21::Map<int, int> s21_map1;
    std::map<int, int> std_map1;
    ASSERT_EQ(s21_map1.empty(), std_map1.empty());

    s21::Map<int, int> s21_map2{std::make_pair(10, 10), std::make_pair(11, 9), std::make_pair(12, 8),
                                std::make_pair(13, 7),  std::make_pair(14, 6), std::make_pair(15, 5)};
    std::map<int, int> std_map2{std::make_pair(10, 10), std::make_pair(11, 9), std::make_pair(12, 8),
                                std::make_pair(13, 7),  std::make_pair(14, 6), std::make_pair(15, 5)};

    ASSERT_EQ(s21_map2.size(), std_map2.size());
    compare_map(s21_map2, std_map2);

    s21::Map<int, std::string> s21_map3{std::make_pair(15, "a"), std::make_pair(3, "b"),
                                        std::make_pair(7, "c"),  std::make_pair(41, "d"),
                                        std::make_pair(52, "e"), std::make_pair(6, "f")};
    std::map<int, std::string> std_map3{std::make_pair(15, "a"), std::make_pair(3, "b"),
                                        std::make_pair(7, "c"),  std::make_pair(41, "d"),
                                        std::make_pair(52, "e"), std::make_pair(6, "f")};
    ASSERT_EQ(s21_map3.size(), std_map3.size());
    compare_map(s21_map3, std_map3);
    ASSERT_FALSE(s21_map3.empty());

    s21::Map<int, double> s21_map4({std::make_pair(1, 1.11), std::make_pair(3, 3.45),
                                    std::make_pair(7, 4.563), std::make_pair(41, 33.23),
                                    std::make_pair(52, 44.3), std::make_pair(67, 0.9)});
    s21::Map<int, double> s21_map4_copy(std::move(s21_map4));
    ASSERT_EQ(s21_map4_copy.size(), 6);
    ASSERT_EQ(s21_map4.size(), 0);
    double map_4_check[8] = {1.11, 3.45, 4.563, 33.23, 44.3, 0.9};
    int i = 0;
    for (auto it = s21_map4_copy.begin(); it != s21_map4_copy.end(); ++it) {
        int key = (*it).first;
        ASSERT_DOUBLE_EQ(s21_map4_copy.at(key), map_4_check[i]);
        i++;
    }
}

// copy move
TEST(s21_map_case, map11) {
    s21::Map<int, int> s21_map2{std::make_pair(10, 10), std::make_pair(11, 9), std::make_pair(12, 8),
                                std::make_pair(13, 7),  std::make_pair(14, 6), std::make_pair(15, 5)};
    std::map<int, int> std_map2{std::make_pair(10, 10), std::make_pair(11, 9), std::make_pair(12, 8),
                                std::make_pair(13, 7),  std::make_pair(14, 6), std::make_pair(15, 5)};

    s21::Map<int, int> s21_map3(s21_map2);
    ASSERT_EQ(s21_map3.size(), std_map2.size());
    compare_map(s21_map3, std_map2);

    s21::Map<int, int> s21_map4(std::move(s21_map2));
    ASSERT_EQ(s21_map4.size(), std_map2.size());
    compare_map(s21_map4, std_map2);

    s21::Map<int, int> s21_map5{std::make_pair(10, 10)};
    s21_map5.erase(s21_map5.find(10));
    ASSERT_TRUE(s21_map5.empty());
}

TEST(s21_map_case, map2) {
    s21::Map<int, std::string> s21_map1;
    s21_map1.insert(std::pair<int, std::string>(30, "q"));
    s21_map1.insert(std::pair<int, std::string>(10, "s"));
    s21_map1.insert(std::pair<int, std::string>(50, "f"));
    s21_map1.insert(std::pair<int, std::string>(20, "h"));
    s21_map1.insert(std::pair<int, std::string>(70, "r"));

    auto result_insert = s21_map1.insert(std::pair<int, std::string>(60, "y"));
    ASSERT_TRUE(result_insert.second);
    ASSERT_EQ((*(result_insert.first)).first, 60);
    ASSERT_EQ((*(result_insert.first)).second, "y");
    ASSERT_EQ(s21_map1.size(), 6);
    // s21_map1.search(10);
    s21_map1.erase(s21_map1.find(60));
    std::pair<int, std::string> std_map1[5] = {{10, "s"}, {20, "h"}, {30, "q"}, {50, "f"}, {70, "r"}};
    int i = 0;
    for (auto it = s21_map1.begin(); it != s21_map1.end(); ++it) {
        int key = (*it).first;
        std::string mapped = (*it).second;
        ASSERT_EQ(key, std_map1[i].first);
        ASSERT_EQ(mapped, std_map1[i].second);
        ++i;
    }
    s21_map1[40] = "d";
    s21_map1[90] = "p";
    s21_map1.insert(100, "w");
    s21_map1.insert(1, "u");
    std::pair<int, std::string> std_map12[9] = {{1, "u"},  {10, "s"}, {20, "h"}, {30, "q"}, {40, "d"},
                                                {50, "f"}, {70, "r"}, {90, "p"}, {100, "w"}};
    i = 0;
    for (auto it = s21_map1.begin(); it != s21_map1.end(); ++it) {
        int key = (*it).first;
        std::string mapped = (*it).second;
        ASSERT_EQ(key, std_map12[i].first);
        ASSERT_EQ(mapped, std_map12[i].second);
        ++i;
    }

    s21::Map<int, std::string> s21_map4;
    s21_map4.insert(std::pair<int, std::string>(30, "q"));
    s21_map4.insert(std::pair<int, std::string>(10, "s"));
    s21_map4.insert(std::pair<int, std::string>(50, "f"));
    s21_map4.insert(std::pair<int, std::string>(60, "e"));

    s21::Map<int, std::string> s21_map5;
    s21_map5.insert(std::pair<int, std::string>(31, "qa"));
    s21_map5.insert(std::pair<int, std::string>(11, "sa"));
    s21_map5.insert(std::pair<int, std::string>(50, "f"));
    s21_map4.merge(s21_map5);
    std::pair<int, std::string> std_map13[14] = {{10, "s"},  {11, "sa"}, {30, "q"},
                                                 {31, "qa"}, {50, "f"},  {60, "e"}};
    i = 0;
    for (auto it = s21_map4.begin(); it != s21_map4.end(); ++it) {
        int key = (*it).first;
        std::string mapped = (*it).second;
        ASSERT_EQ(key, std_map13[i].first);
        ASSERT_EQ(mapped, std_map13[i].second);
        ++i;
    }
    ASSERT_TRUE(s21_map5.empty());
    s21_map1.clear();
    s21_map4.clear();
    s21_map5.clear();
}

TEST(s21_map_case, map3) {
    // default
    s21::Map<int, int> s21_map1;
    std::map<int, int> std_map1;
    ASSERT_EQ(s21_map1.empty(), std_map1.empty());

    s21::Map<int, int> s21_map2{std::make_pair(10, 10), std::make_pair(11, 9), std::make_pair(12, 8),
                                std::make_pair(13, 7),  std::make_pair(14, 6), std::make_pair(15, 5)};
    std::map<int, int> std_map2{std::make_pair(10, 10), std::make_pair(11, 9), std::make_pair(12, 8),
                                std::make_pair(13, 7),  std::make_pair(14, 6), std::make_pair(15, 5)};

    ASSERT_EQ(s21_map2.size(), std_map2.size());
    compare_map(s21_map2, std_map2);

    s21::Map<int, std::string> s21_map3{std::make_pair(15, "a"), std::make_pair(3, "b"),
                                        std::make_pair(7, "c"),  std::make_pair(41, "d"),
                                        std::make_pair(52, "e"), std::make_pair(6, "f")};
    std::map<int, std::string> std_map3{std::make_pair(15, "a"), std::make_pair(3, "b"),
                                        std::make_pair(7, "c"),  std::make_pair(41, "d"),
                                        std::make_pair(52, "e"), std::make_pair(6, "f")};
    ASSERT_EQ(s21_map3.size(), std_map3.size());
    compare_map(s21_map3, std_map3);
    ASSERT_FALSE(s21_map3.empty());

    s21::Map<int, double> s21_map4({std::make_pair(1, 1.11), std::make_pair(3, 3.45),
                                    std::make_pair(7, 4.563), std::make_pair(41, 33.23),
                                    std::make_pair(52, 44.3), std::make_pair(67, 0.9)});
    s21::Map<int, double> s21_map4_copy(std::move(s21_map4));
    ASSERT_EQ(s21_map4_copy.size(), 6);
    ASSERT_EQ(s21_map4.size(), 0);
    double map_4_check[8] = {1.11, 3.45, 4.563, 33.23, 44.3, 0.9};
    int i = 0;
    for (auto it = s21_map4_copy.begin(); it != s21_map4_copy.end(); ++it) {
        int key = (*it).first;
        ASSERT_DOUBLE_EQ(s21_map4_copy.at(key), map_4_check[i]);
        i++;
    }
}

TEST(s21_map_case, map4) {
    s21::Map<int, std::string> s21_map1;
    s21_map1.insert(std::pair<int, std::string>(30, "q"));
    s21_map1.insert(std::pair<int, std::string>(10, "s"));
    s21_map1.insert(std::pair<int, std::string>(50, "f"));
    s21_map1.insert(std::pair<int, std::string>(20, "h"));
    s21_map1.insert(std::pair<int, std::string>(70, "r"));
    s21_map1.clear();
    ASSERT_TRUE(s21_map1.empty());
}

TEST(s21_map_case, map5) {
    s21::Map<int, std::string> s21_map1{
        std::make_pair(15, "a"), std::make_pair(3, "h"),  std::make_pair(7, "l"),  std::make_pair(11, " "),
        std::make_pair(42, "w"), std::make_pair(8, "l"),  std::make_pair(52, "o"), std::make_pair(6, "e"),
        std::make_pair(53, "r"), std::make_pair(10, "o"), std::make_pair(63, "l"), std::make_pair(70, "d")};
    std::map<int, std::string> std_map1{
        std::make_pair(15, "a"), std::make_pair(3, "h"),  std::make_pair(7, "l"),  std::make_pair(11, " "),
        std::make_pair(42, "w"), std::make_pair(8, "l"),  std::make_pair(52, "o"), std::make_pair(6, "e"),
        std::make_pair(53, "r"), std::make_pair(10, "o"), std::make_pair(63, "l"), std::make_pair(70, "d")};
    ASSERT_EQ(s21_map1.size(), std_map1.size());
    compare_map(s21_map1, std_map1);
    ASSERT_FALSE(s21_map1.contains(1000));

    s21_map1.erase(s21_map1.find(10));
    s21_map1.erase(s21_map1.find(1000));
}

TEST(s21_map_case, map6) {
    s21::Map<int, std::string> s21_map1{
        std::make_pair(15, "a"), std::make_pair(3, "h"),  std::make_pair(7, "l"),  std::make_pair(11, " "),
        std::make_pair(42, "w"), std::make_pair(8, "l"),  std::make_pair(52, "o"), std::make_pair(6, "e"),
        std::make_pair(53, "r"), std::make_pair(10, "o"), std::make_pair(63, "l"), std::make_pair(70, "d")};
    s21_map1.emplace(std::make_pair(100, "!"), std::make_pair(103, "!"), std::make_pair(101, "!"));
    std::map<int, std::string> std_map1{
        std::make_pair(100, "!"), std::make_pair(101, "!"), std::make_pair(103, "!"), std::make_pair(15, "a"),
        std::make_pair(3, "h"),   std::make_pair(7, "l"),   std::make_pair(11, " "),  std::make_pair(42, "w"),
        std::make_pair(8, "l"),   std::make_pair(52, "o"),  std::make_pair(6, "e"),   std::make_pair(53, "r"),
        std::make_pair(10, "o"),  std::make_pair(63, "l"),  std::make_pair(70, "d")};
    ASSERT_EQ(s21_map1.size(), std_map1.size());
    compare_map(s21_map1, std_map1);
    ASSERT_FALSE(s21_map1.contains(1000));

    s21_map1.erase(s21_map1.find(10));
    s21_map1.erase(s21_map1.find(1000));
}

TEST(s21_map_case, map7) {
    s21::Map<int, std::string> s21_map1{
        std::make_pair(15, "a"), std::make_pair(3, "h"),  std::make_pair(7, "l"),  std::make_pair(11, " "),
        std::make_pair(42, "w"), std::make_pair(8, "l"),  std::make_pair(52, "o"), std::make_pair(6, "e"),
        std::make_pair(53, "r"), std::make_pair(10, "o"), std::make_pair(63, "l"), std::make_pair(70, "d"),
        std::make_pair(70, "d")};
    s21_map1.insert(70, "d");
    s21_map1.emplace(std::make_pair(100, "!"), std::make_pair(101, "!"), std::make_pair(103, "!"));
    s21_map1.insert_or_assign(189, ")");
    std::map<int, std::string> std_map1{
        std::make_pair(100, "!"), std::make_pair(189, ")"), std::make_pair(101, "!"),
        std::make_pair(103, "!"), std::make_pair(15, "a"),  std::make_pair(3, "h"),
        std::make_pair(7, "l"),   std::make_pair(11, " "),  std::make_pair(42, "w"),
        std::make_pair(8, "l"),   std::make_pair(52, "o"),  std::make_pair(6, "e"),
        std::make_pair(53, "r"),  std::make_pair(10, "o"),  std::make_pair(63, "l"),
        std::make_pair(70, "d")};
    ASSERT_EQ(s21_map1.size(), std_map1.size());
    compare_map(s21_map1, std_map1);
    ASSERT_FALSE(s21_map1.contains(1000));

    s21_map1.erase(s21_map1.find(10));
    s21_map1.erase(s21_map1.find(1000));
    s21_map1.erase(s21_map1.find(7));
    s21_map1.erase(s21_map1.find(11));
    s21_map1.erase(s21_map1.find(52));
    s21_map1.erase(s21_map1.find(53));
    s21_map1.erase(s21_map1.find(100));
    s21_map1.erase(s21_map1.find(103));
    s21_map1.erase(s21_map1.find(189));
    s21_map1.erase(s21_map1.find(101));
    s21_map1.erase(s21_map1.find(42));
    s21_map1.erase(s21_map1.find(15));
    s21_map1.erase(s21_map1.find(8));
    s21_map1.erase(s21_map1.find(70));
    s21_map1.erase(s21_map1.find(6));
    s21_map1.erase(s21_map1.find(3));
    std::map<int, std::string> std_map2{std::make_pair(63, "l")};
    ASSERT_EQ(s21_map1.size(), std_map2.size());
    compare_map(s21_map1, std_map2);
    s21_map1.clear();
    ASSERT_TRUE(s21_map1.empty());
}

TEST(s21_map_case, map71) {
    s21::Map<int, std::string> s21_map1{
        std::make_pair(14, "a"), std::make_pair(4, "a"),  std::make_pair(18, "a"), std::make_pair(3, "a"),
        std::make_pair(8, "a"),  std::make_pair(21, "a"), std::make_pair(6, "a"),  std::make_pair(11, "a")};
    s21_map1.insert(5, "a");
    s21_map1.insert(1, "a");
    s21_map1.erase(s21_map1.find(8));
    s21_map1.insert(9, "a");
    s21_map1.insert(10, "a");
    s21_map1.insert(8, "a");
    s21_map1.insert(7, "a");
    s21_map1.insert(13, "a");
    s21_map1.erase(s21_map1.find(6));
    s21_map1.erase(s21_map1.find(5));
    s21_map1.erase(s21_map1.find(14));
    s21_map1.erase(s21_map1.find(13));
    std::map<int, std::string> std_map1{
        std::make_pair(1, "a"),  std::make_pair(4, "a"), std::make_pair(3, "a"),  std::make_pair(7, "a"),
        std::make_pair(8, "a"),  std::make_pair(9, "a"), std::make_pair(10, "a"), std::make_pair(18, "a"),
        std::make_pair(11, "a"), std::make_pair(21, "a")};

    ASSERT_EQ(s21_map1.size(), std_map1.size());
    compare_map(s21_map1, std_map1);
}

TEST(s21_map_case, map711) {
    s21::Map<int, std::string> s21_map1{std::make_pair(0, "a"), std::make_pair(1, "a"),
                                        std::make_pair(2, "a"), std::make_pair(3, "a"),
                                        std::make_pair(4, "a")};

    s21_map1.erase(s21_map1.find(1));
    std::map<int, std::string> std_map1{std::make_pair(0, "a"), std::make_pair(2, "a"),
                                        std::make_pair(3, "a"), std::make_pair(4, "a")};

    ASSERT_EQ(s21_map1.size(), std_map1.size());
    compare_map(s21_map1, std_map1);
}
