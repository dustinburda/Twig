#include <gtest/gtest.h>

#include "../include/Token.h"

TEST(TokenTest, ConstructTest) {
    Token t{2.0};

    EXPECT_EQ(t.type_, TokenType::DOUBLE);
    EXPECT_EQ(t.double_num_, 2.0);
}
