#include "../include/Token.h"

#include <cstring>
#include <sstream>

Token::Token(int num) : type_{TokenType::INTEGER} {
    int_num_ = num;
}

Token::Token(double num) : type_{TokenType::DOUBLE} {
    double_num_ = num;
}

Token::Token(TokenType type, std::string s) : type_{type} {
    string_ = new char[s.size() + 1];
    std::memcpy(string_, s.data(), s.size());
    string_[s.size()] = '\0';
}

Token::Token(TokenType type) : type_{type} {}

Token::~Token() {
    if (type_ == TokenType::STRING)
        delete[] string_;
}