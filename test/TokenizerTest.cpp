#include <gtest/gtest.h>

#include "../include/Tokenizer.h"

#include <csignal>
#include <cstring>
#include <string>
#include <stdexcept>
#include <vector>
#include <unistd.h>


TEST(TokenizerTest, EmptyInput) {
    auto tokens = Tokenizer::GetInstance().Tokenize("");

    EXPECT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type_, TokenType::EOF_);
}

TEST(TokenizerTest, MathOperations) {
    auto tokens = Tokenizer::GetInstance().Tokenize("+ - / * -/ +*");

    EXPECT_EQ(tokens.size(), 9);
    EXPECT_EQ(tokens[0].type_, TokenType::PLUS);
    EXPECT_EQ(tokens[1].type_, TokenType::MINUS);
    EXPECT_EQ(tokens[2].type_, TokenType::DIVISION);
    EXPECT_EQ(tokens[3].type_, TokenType::MULTIPLICATION);
    EXPECT_EQ(tokens[4].type_, TokenType::MINUS);
    EXPECT_EQ(tokens[5].type_, TokenType::DIVISION);
    EXPECT_EQ(tokens[6].type_, TokenType::PLUS);
    EXPECT_EQ(tokens[7].type_, TokenType::MULTIPLICATION);
    EXPECT_EQ(tokens[8].type_, TokenType::EOF_);
}

TEST(TokenizerTest, Parenthesis) {
    auto tokens = Tokenizer::GetInstance().Tokenize("  ( 2*3 - 4 / ( 6 + 2))");

    EXPECT_EQ(tokens.size(), 14);
    EXPECT_EQ(tokens[0].type_, TokenType::LEFT_PAREN);
    EXPECT_EQ(tokens[1].type_, TokenType::INTEGER);
    EXPECT_EQ(tokens[1].int_num_, 2);

    EXPECT_EQ(tokens[2].type_, TokenType::MULTIPLICATION);

    EXPECT_EQ(tokens[3].type_, TokenType::INTEGER);
    EXPECT_EQ(tokens[3].int_num_, 3);

    EXPECT_EQ(tokens[4].type_, TokenType::MINUS);

    EXPECT_EQ(tokens[5].type_, TokenType::INTEGER);
    EXPECT_EQ(tokens[5].int_num_, 4);

    EXPECT_EQ(tokens[6].type_, TokenType::DIVISION);

    EXPECT_EQ(tokens[7].type_, TokenType::LEFT_PAREN);

    EXPECT_EQ(tokens[8].type_, TokenType::INTEGER);
    EXPECT_EQ(tokens[8].int_num_, 6);

    EXPECT_EQ(tokens[9].type_, TokenType::PLUS);

    EXPECT_EQ(tokens[10].type_, TokenType::INTEGER);
    EXPECT_EQ(tokens[10].int_num_, 2);

    EXPECT_EQ(tokens[11].type_, TokenType::RIGHT_PAREN);
    EXPECT_EQ(tokens[12].type_, TokenType::RIGHT_PAREN);
    EXPECT_EQ(tokens[13].type_, TokenType::EOF_);
}



TEST(TokenizerTest, MixedIntDouble) {
    auto tokens = Tokenizer::GetInstance().Tokenize("  ( 2.1 + 3.0 / 4.76)");

    EXPECT_EQ(tokens.size(), 8);
    EXPECT_EQ(tokens[0].type_, TokenType::LEFT_PAREN);

    EXPECT_EQ(tokens[1].type_, TokenType::DOUBLE);
    EXPECT_EQ(tokens[1].double_num_, 2.1);

    EXPECT_EQ(tokens[2].type_, TokenType::PLUS);

    EXPECT_EQ(tokens[3].type_, TokenType::DOUBLE);
    EXPECT_EQ(tokens[3].double_num_, 3.0);

    EXPECT_EQ(tokens[4].type_, TokenType::DIVISION);

    EXPECT_EQ(tokens[5].type_, TokenType::DOUBLE);
    EXPECT_EQ(tokens[5].double_num_, 4.76);

    EXPECT_EQ(tokens[6].type_, TokenType::RIGHT_PAREN);

    EXPECT_EQ(tokens[7].type_, TokenType::EOF_);
}

TEST(TokenizerTest, SpaceInToken) {
    auto tokens = Tokenizer::GetInstance().Tokenize("! = = == !=");

    EXPECT_EQ(tokens.size(), 6);

    EXPECT_EQ(tokens[0].type_, TokenType::BANG);
    EXPECT_EQ(tokens[1].type_, TokenType::EQUAL);
    EXPECT_EQ(tokens[2].type_, TokenType::EQUAL);
    EXPECT_EQ(tokens[3].type_, TokenType::EQUAL_EQUAL);
    EXPECT_EQ(tokens[4].type_, TokenType::BANG_EQUAL);
    EXPECT_EQ(tokens[5].type_, TokenType::EOF_);
}

TEST(TokenizerTest, Identifiers) {
    auto tokens = Tokenizer::GetInstance().Tokenize("hello world x != 2 + (3.1 - 7.4)");

    EXPECT_EQ(tokens.size(), 12);

    EXPECT_EQ(tokens[0].type_, TokenType::IDENTIFIER);
    EXPECT_STREQ(tokens[0].string_, "hello");

    EXPECT_EQ(tokens[1].type_, TokenType::IDENTIFIER);
    EXPECT_STREQ(tokens[1].string_, "world");

    EXPECT_EQ(tokens[2].type_, TokenType::IDENTIFIER);
    EXPECT_STREQ(tokens[2].string_, "x");

    EXPECT_EQ(tokens[3].type_, TokenType::BANG_EQUAL);

    EXPECT_EQ(tokens[4].type_, TokenType::INTEGER);
    EXPECT_EQ(tokens[4].int_num_, 2);

    EXPECT_EQ(tokens[5].type_, TokenType::PLUS);

    EXPECT_EQ(tokens[6].type_, TokenType::LEFT_PAREN);

    EXPECT_EQ(tokens[7].type_, TokenType::DOUBLE);
    EXPECT_EQ(tokens[7].double_num_, 3.1);

    EXPECT_EQ(tokens[8].type_, TokenType::MINUS);

    EXPECT_EQ(tokens[9].type_, TokenType::DOUBLE);
    EXPECT_EQ(tokens[9].double_num_, 7.4);


    EXPECT_EQ(tokens[10].type_, TokenType::RIGHT_PAREN);

    EXPECT_EQ(tokens[11].type_, TokenType::EOF_);
}

TEST(TokenizerTest, IdentifiersAndReservedWords) {
    auto tokens = Tokenizer::GetInstance().Tokenize("hello true x != 2 + (false - 7.4)");

    EXPECT_EQ(tokens.size(), 12);

    EXPECT_EQ(tokens[0].type_, TokenType::IDENTIFIER);
    EXPECT_STREQ(tokens[0].string_, "hello");

    EXPECT_EQ(tokens[1].type_, TokenType::TRUE);

    EXPECT_EQ(tokens[2].type_, TokenType::IDENTIFIER);
    EXPECT_STREQ(tokens[2].string_, "x");

    EXPECT_EQ(tokens[3].type_, TokenType::BANG_EQUAL);

    EXPECT_EQ(tokens[4].type_, TokenType::INTEGER);
    EXPECT_EQ(tokens[4].int_num_, 2);

    EXPECT_EQ(tokens[5].type_, TokenType::PLUS);

    EXPECT_EQ(tokens[6].type_, TokenType::LEFT_PAREN);

    EXPECT_EQ(tokens[7].type_, TokenType::FALSE);

    EXPECT_EQ(tokens[8].type_, TokenType::MINUS);

    EXPECT_EQ(tokens[9].type_, TokenType::DOUBLE);
    EXPECT_EQ(tokens[9].double_num_, 7.4);


    EXPECT_EQ(tokens[10].type_, TokenType::RIGHT_PAREN);

    EXPECT_EQ(tokens[11].type_, TokenType::EOF_);
}

TEST(TokenizerTest, Strings) {
    auto tokens = Tokenizer::GetInstance().Tokenize(" hello_world = \"hello world\" ");

    EXPECT_EQ(tokens.size(), 4);

    EXPECT_EQ(tokens[0].type_, TokenType::IDENTIFIER);
    EXPECT_STREQ(tokens[0].string_, "hello_world");

    EXPECT_EQ(tokens[1].type_, TokenType::EQUAL);

    EXPECT_EQ(tokens[2].type_, TokenType::STRING);
    EXPECT_STREQ(tokens[2].string_, "hello world");

    EXPECT_EQ(tokens[3].type_, TokenType::EOF_);
}