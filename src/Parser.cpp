#include "../include/Parser.h"

#include <cassert>

Parser::Parser() : tokens_(), index_(0) {

}

Parser& Parser::GetInstance() {
    static Parser parser;
    return parser;
}


std::unique_ptr<ASTNode> Parser::ParseGrouping() {
    if (!Peek().has_value())
        throw std::logic_error("There should be a token when parsing grouping");

    auto left_paren = Consume();
    assert (left_paren.has_value() && left_paren->type_ == TokenType::LEFT_PAREN );

    auto expr = ParseExpression();

    auto right_paren = Consume();
    assert (right_paren.has_value() && Consume()->type_ == TokenType::RIGHT_PAREN );

    return expr;
}

std::unique_ptr<ASTNode> Parser::ParsePrimary() {
    if (!Peek().has_value())
        throw std::logic_error("There should be a token when parsing primary");

    auto token = Peek().value();
    Consume();

    if (token.type_ == TokenType::LEFT_PAREN)
        return ParseGrouping();
    else if (token.type_ == TokenType::INTEGER) {
        Value value{token.int_num_};
        return std::make_unique<Literal>(value);
    } else if (token.type_ == TokenType::DOUBLE) {
        Value value{token.double_num_};
        return std::make_unique<Literal>(value);
    } else if (token.type_ == TokenType::STRING) {
        Value value {token.string_};
        return std::make_unique<Literal>(value);
    } else if (token.type_ == TokenType::TRUE || token.type_ == TokenType::FALSE) {
        Value value {token.type_ == TokenType::TRUE};
        return std::make_unique<Literal>(value);
    }

    throw std::logic_error("Unknown token");

}

std::unique_ptr<ASTNode> Parser::ParseUnary() {
    if (MatchTokens({TokenType::BANG, TokenType::MINUS})) {
        auto token = Consume();
        // TODO: Transform
        auto unary = ParseUnary();

        return nullptr;
        // return std::make_unique<Unary>()
    }

    return ParsePrimary();
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
    auto logical = ParseLogical();


}



std::unique_ptr<ASTNode> Parser::ParseExpression() {
    return ParseComparison();
}

std::unique_ptr<ASTNode> Parser::ParseProgram() {
    std::vector<std::unique_ptr<ASTNode>> expressions;
    while (Peek().has_value() && Peek().value().type_ != TokenType::EOF_) {
        Consume();
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

bool Parser::MatchTokens( [[ maybe_unused ]] const std::vector<TokenType>& tokens) {
    return false;
}