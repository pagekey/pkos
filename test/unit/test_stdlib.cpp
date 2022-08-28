#include <gtest/gtest.h>
#include "../../src/common/stdlib.h"


TEST ( stdlib, itoa ) {
    int a = 12345;
    char c[10];
    ASSERT_TRUE(streq(itoa(a, c), "12345"));
}

TEST( stdlib, streq_equal ) {
    char* mystring = "hello";
    char* myotherstring = "hello";
    ASSERT_TRUE(streq(mystring, myotherstring));
}
TEST( stdlib, streq_not_equal ) {
    char* mystring = "hello";
    char* myotherstring = "hello2";
    ASSERT_FALSE(streq(mystring, myotherstring));
}


TEST( stdlib, safe_streq_equal ) {
    char* mystring = "hello";
    char* myotherstring = "hello";
    ASSERT_TRUE(safe_streq(mystring, 5, myotherstring, 5));
}
TEST( stdlib, safe_streq_not_equal ) {
    char* mystring = "hello";
    char* myotherstring = "hello2";
    ASSERT_FALSE(safe_streq(mystring, 5, myotherstring, 6));
}
