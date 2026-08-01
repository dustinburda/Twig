#include "../include/Token.h"

#include <cstring>
#include <sstream>

Token::Token(int num) : type_{TokenType::INTEGER} {
    int_num_ = num;
}

Token::Token(double num) : type_{TokenType::DOUBLE} {
    double_num_ = num;
}

Token::Token(std::string s) : type_{TokenType::STRING} {
    string_ = new char[s.size() + 1];
    std::memcpy(string_, s.data(), s.size());
    string_[s.size() + 1] = '\0';
}

Token::Token(operation o,TokenType type) : type_{type} {
    std::strcpy(operation_, o);
}

Token::Token(bool b) : type_{b ? TokenType::TRUE : TokenType::FALSE}, bool_{b} {}

Token::Token(TokenType type) : type_{type} {}

Token::~Token() {
    if (type_ == TokenType::STRING)
        delete[] string_;
}

std::string Token::toString() {
    std::stringstream ss;

    // TODO: true and false

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
            ss << "LEFT PAREN";
            break;
        case TokenType::RIGHT_PAREN:
            ss << "RIGHT PAREN";
            break;
        case TokenType::LEFT_BRACE:
            ss << "LEFT BRACE";
            break;
        case TokenType::RIGHT_BRACE:
            ss << "RIGHT BRACE";
            break;
        case TokenType::TRUE:
            ss << "TRUE";
            break;
        case TokenType::FALSE:
            ss << "FALSE";
            break;
        case TokenType::BANG:
            ss << "BANG";
            break;
        case TokenType::BANG_EQUAL:
            ss << "BANG_EQUAL";
            break;
        case TokenType::LESS:
            ss << "LESS";
            break;
        case TokenType::LESS_EQUAL:
            ss << "LESS EQUAL";
            break;
        case TokenType::GREATER:
            ss << "GREATER";
            break;
        case TokenType::GREATER_EQUAL:
            ss << "GREATER EQUAL";
            break;
        case TokenType::EQUAL:
            ss << "GREATER";
            break;
        case TokenType::EQUAL_EQUAL:
            ss << "GREATER EQUAL";
            break;
        case TokenType::AND:
            ss << "AND";
            break;
        case TokenType::OR:
            ss << "OR";
            break;
        case TokenType::EOF_:
            ss << "EOF";
            break;
        case TokenType::STRING:
            ss << "STRING";
            break;
    }

    ss << "\n";
    ss << "Value: ";

    switch (type_) {
        case TokenType::PLUS:
        case TokenType::MINUS:
        case TokenType::MULTIPLICATION:
        case TokenType::DIVISION:
        case TokenType::BANG:
        case TokenType::BANG_EQUAL:
        case TokenType::LESS:
        case TokenType::LESS_EQUAL:
        case TokenType::GREATER:
        case TokenType::GREATER_EQUAL:
        case TokenType::EQUAL:
        case TokenType::EQUAL_EQUAL:
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
        case TokenType::LEFT_BRACE:
        case TokenType::RIGHT_BRACE:
            ss << character_;
            break;
        case TokenType::TRUE:
            ss << "TRUE";
            break;
        case TokenType::FALSE:
            ss << "FALSE";
            break;
        case TokenType::AND:
            ss << "AND";
            break;
        case TokenType::OR:
            ss << "OR";
            break;
        case TokenType::EOF_:
            ss << "EOF";
            break;
        case TokenType::STRING:
            ss << string_;
            break;
    }

    return ss.str();
}