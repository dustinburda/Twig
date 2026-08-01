#ifndef TWIG_TOKEN_H
#define TWIG_TOKEN_H

#include <string>

using operation = const char*;

enum class TokenType {
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    INTEGER,
    DOUBLE,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    TRUE,
    FALSE,
    BANG,
    BANG_EQUAL,
    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    AND,
    OR,
    STRING,
    EOF_
};


struct Token {
    Token(int num);
    Token(double num);
    Token(std::string c);
    Token(operation o, TokenType type);
    Token(bool b);
    Token(TokenType type);

    ~Token();

    TokenType type_;

    union {
        int int_num_;
        double double_num_;
        char operation_[2];
        char character_;
        bool bool_;
        char* string_;
    };

    std::string toString();

    static bool IsSumToken(Token t) {
        return t.type_ == TokenType::PLUS || t.type_ == TokenType::MINUS;
    }

    static bool IsMultToken(Token t) {
        return t.type_ == TokenType::MULTIPLICATION || t.type_ == TokenType::DIVISION;
    }

    static bool IsNumToken(Token t) {
        return t.type_ == TokenType::INTEGER || t.type_ == TokenType::DOUBLE;
    }

    static bool IsBoolToken(Token t) {
        return t.type_ == TokenType::TRUE || t.type_ == TokenType::FALSE;
    }
};

#endif // TWIG_TOKEN_H