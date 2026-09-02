//
// Created by Dustin on 8/2/26.
//

#ifndef TWIG_TOKENTYPE_H
#define TWIG_TOKENTYPE_H

#include <string>
#include <unordered_map>

enum class TokenType {
    // Math operators

    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,

    // Literals
    STRING,

    // NUMBER
    INTEGER,
    DOUBLE,

    // Keywords
    TRUE,
    FALSE,

    // Identifier
    IDENTIFIER,

    // Groupings
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,

    // Logical Unary Operator
    BANG,

    // Assignment
    EQUAL,

    // Logical Binary Operators
    BANG_EQUAL,
    EQUAL_EQUAL,

    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,

    AND,
    OR,

    EOF_
};

static std::unordered_map<std::string, TokenType> reserved_words = {
    {"true", TokenType::TRUE},
    {"false", TokenType::FALSE}
};

#endif //TWIG_TOKENTYPE_H
