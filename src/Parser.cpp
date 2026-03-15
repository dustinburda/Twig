#include "../include/Parser.h"

std::unique_ptr<ASTNode> Parser::Parse(const std::vector<Token>& tokens) {
    tokens_ = tokens;
    index_ = 0;

    return ParseExpr();
}


std::unique_ptr<ASTNode> Parser::ParseExpr() {
    if (index_ == tokens_.size())
        return nullptr;


    std::unique_ptr<ASTNode> root_node = ParseTerm();
    while (Peek().has_value() && Token::IsSumToken(Peek().value())) {
        auto op = ParseOp();
        auto num_node = ParseTerm();

        op->left_ = std::move(root_node);
        op->right_ = std::move(num_node);

        root_node = std::move(op);
    }

    return std::move(root_node);
}

std::unique_ptr<ASTNode> Parser::ParseTerm() {
    if (index_ == tokens_.size())
        return nullptr;

    auto root_node = ParseFactor();
    while (Peek().has_value() && Token::IsMultToken(Peek().value())) {
        auto op = ParseOp();
    }

    return root_node;
}

std::unique_ptr<ASTNode> Parser::ParseFactor() {
    if (!Peek().has_value())
        return nullptr;

    auto token = Peek().value();

    if (Token::IsNumToken(token)) {
        return ParseNum();
    }

    return ParseExpr();
}


std::unique_ptr<ASTNode> Parser::ParseNum() {
    if (!Peek().has_value())
        return nullptr;

    auto t = Consume().value();

    switch (t.type_) {
        case TokenType::DOUBLE:
            return std::make_unique<DoubleNode>(t.double_num_);
        case TokenType::INTEGER:
            return std::make_unique<IntNode>(t.int_num_);
        default:
            throw std::logic_error("Can't parse num node with non-number token.");
    }

    return nullptr;
}

std::unique_ptr<ASTNode> Parser::ParseOp() {
    if (!Peek().has_value())
        return nullptr;

    auto t = Consume().value();

    switch (t.type_) {
        case TokenType::PLUS:
            return std::make_unique<OpNode>(t.operation_);
        case TokenType::MINUS:
            return std::make_unique<IntNode>(t.operation_);
        case TokenType::MULTIPLICATION:
            return std::make_unique<IntNode>(t.operation_);
        case TokenType::DIVISION:
            return std::make_unique<IntNode>(t.operation_);
        default:
            throw std::logic_error("Can't parse num node with non-number token.");
    }

    return nullptr;
}

std::optional<Token> Parser::Peek() {
    if (index_ >= tokens_.size())
        return std::nullopt;

    return tokens_[index_];
}

std::optional<Token> Parser::PeekN(int n) {
    if (index_ + n - 1 >= tokens_.size())
        return std::nullopt;

    return tokens_[index_ + n - 1];
}

std::optional<Token> Parser::Consume() {
    if (index_ >= tokens_.size())
        return std::nullopt;

    Token token = tokens_[index_];
    index_++;

    return token;
}

Parser::Parser() = default;