#include "tests/s21_rbtree_test.cpp"

#include "tests/s21_list_test.cpp"
#include "tests/s21_map_test.cpp"
#include "tests/s21_queue_test.cpp"
#include "tests/s21_set_test.cpp"
#include "tests/s21_stack_test.cpp"
#include "tests/s21_vector_test.cpp"
#include "tests/s21_array_test.cpp"
#include "tests/s21_multiset_test.cpp"

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
