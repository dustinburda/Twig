#include "Token.h"

#include <sstream>

Token::Token(int num) : type_{TokenType::INTEGER} {
    int_num_ = num;
}

Token::Token(double num) : type_{TokenType::DOUBLE} {
    double_num_ = num;
}

Token::Token(char c, TokenType type) : type_{type}, operation_{c} {}

std::string Token::toString() {
    std::stringstream ss;

    ss << "TokenType: ";
    switch (type_) {
        case TokenType::PLUS:
            ss << "PLUS";
            break;
        case TokenType::MINUS:
            ss << "MINUS";
            break;
        case TokenType::MULTIPLICATION:
            ss << "MULTIPLICATION";
            break;
        case TokenType::DIVISION:
            ss << "DIVISION";
            break;
        case TokenType::INTEGER:
            ss << "INTEGER";
            break;
        case TokenType::DOUBLE:
            ss << "DOUBLE";
            break;
        case TokenType::LEFT_PAREN:
            ss << "DOUBLE";
            break;
        case TokenType::RIGHT_PAREN:
            ss << "DOUBLE";
            break;
    }

    ss << "\n";
    ss << "Value: ";

    switch (type_) {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::MULTIPLICATION:
        case TokenType::DIVISION:
            ss << operation_;
            break;
        case TokenType::INTEGER:
            ss << int_num_;
            break;
        case TokenType::DOUBLE:
            ss << double_num_;
            break;
        case TokenType::LEFT_PAREN:
        case TokenType::RIGHT_PAREN:
            ss << character_;
            break;
    }

    return ss.str();
}