#ifndef TWIG_TOKEN_H
#define TWIG_TOKEN_H

#include "TokenType.h"

#include <string>

class Token {
public:
    Token(TokenType type);

    // Tokens with runtime values
    Token(int num);
    Token(double num);
    Token(TokenType, std::string c);

    ~Token();

public:
    TokenType type_;

    // Runtime values
    union {
        int int_num_;
        double double_num_;
        char* string_;
    };
};

#endif // TWIG_TOKEN_H