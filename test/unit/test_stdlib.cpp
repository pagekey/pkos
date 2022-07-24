#include <gtest/gtest.h>
#include "../../src/common/stdlib.h"

TEST( stdlib, streq_equal ) {
    char* mystring = "hello";
    char* myotherstring = "hello";
    ASSERT_TRUE(streq(mystring, 5, myotherstring, 5));
}
TEST( stdlib, streq_not_equal ) {
    char* mystring = "hello";
    char* myotherstring = "hello2";
    ASSERT_FALSE(streq(mystring, 5, myotherstring, 6));
}