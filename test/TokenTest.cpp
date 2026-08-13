#include <gtest/gtest.h>

#include "../include/Token.h"

#include <cstring>

TEST(TokenTest, ConstructTest) {
    Token t1{2.0};

    EXPECT_EQ(t1.type_, TokenType::DOUBLE);
    EXPECT_EQ(t1.double_num_, 2.0);


    Token t2 {1};

    EXPECT_EQ(t2.type_, TokenType::INTEGER);
    EXPECT_EQ(t2.int_num_, 1.0);

    Token t3 {TokenType::STRING, "Token"};
    EXPECT_EQ(t3.type_, TokenType::STRING);
    EXPECT_STREQ(t3.string_, "Token");

    Token t4 {TokenType::FALSE};
    EXPECT_EQ(t4.type_, TokenType::FALSE);
}
