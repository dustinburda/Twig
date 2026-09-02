#include "../include/Parser.h"

Parser::Parser() : tokens_(), index_(0) {

}

Parser& Parser::GetInstance() {
    static Parser parser;
    return parser;
}


std::unique_ptr<ASTNode> Parser::ParseGrouping() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParsePrimary() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseUnary() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseMult() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseAdd() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseInequality() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseLogical() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseComparison() {
    return nullptr;
}



std::unique_ptr<ASTNode> Parser::ParseExpression() {
    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseProgram() {
    std::vector<std::unique_ptr<ASTNode>> expressions;
    while (Peek().has_value() && Peek().value().type_ != TokenType::EOF_) {
        expressions.push_back(ParseExpression());
    }

    return std::make_unique<Program> (std::move(expressions));
}

std::unique_ptr<ASTNode> Parser::Parse(const std::vector<Token>& tokens) {
    tokens_ = tokens;
    return ParseProgram();
}

std::optional<Token> Parser::Peek() {
    if (index_ >= tokens_.size())
        return std::nullopt;

    return tokens_[index_];
}

std::optional<Token> Parser::PeekN(int n) {
    if (index_ + n >= tokens_.size())
        return std::nullopt;

    return tokens_[index_ + n];
}

std::optional<Token> Parser::Consume() {
    if (index_ >= tokens_.size())
        return std::nullopt;

    auto token = tokens_[index_];
    index_++;

    return token;
}