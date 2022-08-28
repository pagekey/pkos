#include <gtest/gtest.h>
#include "../../src/common/stdlib.h"


TEST ( stdlib, itoa ) {
    int a = 12345;
    char c[10];
    ASSERT_TRUE(streq(itoa(a, c), "12345"));
}
TEST ( stdlib, itoah ) {
    int a = 12345;
    char c[10];
    ASSERT_TRUE(streq(itoah(a, c), "3039"));
}
TEST ( stdlib, itoab ) {
    int a = 12345;
    char c[15];
    ASSERT_TRUE(streq(itoab(a, c), "11000000111001"));
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
