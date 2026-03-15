#ifndef TWIG_TOKEN_H
#define TWIG_TOKEN_H

#include <string>

enum class TokenType {
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,
    INTEGER,
    DOUBLE,
    LEFT_PAREN,
    RIGHT_PAREN
};


struct Token {
    Token(int num);
    Token(double num);
    Token(char c, TokenType type);

    TokenType type_;

    union {
        int int_num_;
        double double_num_;
        char operation_;
        char character_;
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
};

#endif // TWIG_TOKEN_H