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

        UnaryOperation op;
        if (token->type_ == TokenType::BANG)
            op = UnaryOperation::LogicalNot;
        else if (token->type_ == TokenType::MINUS)
            op = UnaryOperation::Negate;

        return std::make_unique<Unary>(op, ParseUnary());
    }

    return ParsePrimary();
}

std::unique_ptr<ASTNode> Parser::ParseMult() {
    auto node = ParseUnary();

    while (MatchTokens({TokenType::MULTIPLICATION, TokenType::DIVISION})) {
        auto token = Consume();

        BinaryOperation op;
        if (token->type_ == TokenType::MULTIPLICATION)
            op = BinaryOperation::MULTIPLICATION;
        else if (token->type_ == TokenType::DIVISION)
            op = BinaryOperation::DIVISION;

        node = std::make_unique<Binary>(op, std::move(node), ParseUnary());
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::ParseAdd() {
    auto node = ParseMult();

    while (MatchTokens({TokenType::PLUS, TokenType::MINUS})) {
        auto token = Consume();

        BinaryOperation op;
        if (token->type_ == TokenType::PLUS)
            op = BinaryOperation::PLUS;
        else if (token->type_ == TokenType::MINUS)
            op = BinaryOperation::MINUS;

        node = std::make_unique<Binary>(op, std::move(node), ParseMult());
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::ParseInequality() {
    auto node = ParseAdd();

    while (MatchTokens({TokenType::LESS, TokenType::LESS_EQUAL, TokenType::GREATER, TokenType::GREATER_EQUAL})) {
        auto token = Consume();

        BinaryOperation op;
        if (token->type_ == TokenType::LESS)
            op = BinaryOperation::LESS;
        else if (token->type_ == TokenType::LESS_EQUAL)
            op = BinaryOperation::LESS_EQUAL;
        else if (token->type_ == TokenType::GREATER)
            op = BinaryOperation::GREATER;
        else if (token->type_ == TokenType::GREATER_EQUAL)
            op = BinaryOperation::GREATER_EQUAL;

        node = std::make_unique<Binary>(op, std::move(node), ParseAdd());
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::ParseLogical() {
    auto node = ParseInequality();

    while (MatchTokens({TokenType::AND, TokenType::OR})) {
        auto token = Consume();

        BinaryOperation op;
        if (token->type_ == TokenType::AND)
            op = BinaryOperation::AND;
        else if (token->type_ == TokenType::OR)
            op = BinaryOperation::OR;

        node = std::make_unique<Binary>(op, std::move(node), ParseInequality());
    }

    return node;
}

std::unique_ptr<ASTNode> Parser::ParseComparison() {
    auto node = ParseLogical();

    while (MatchTokens({TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL})) {
        auto token = Consume();

        BinaryOperation op;
        if (token->type_ == TokenType::BANG_EQUAL)
            op = BinaryOperation::BANG_EQUAL;
        else if (token->type_ == TokenType::EQUAL_EQUAL)
            op = BinaryOperation::EQUAL_EQUAL;

        node = std::make_unique<Binary>(op, std::move(node), ParseLogical());
    }

    return node;
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

bool Parser::MatchTokens(const std::vector<TokenType>& token_types) {
    if (!Peek().has_value())
        return false;

    auto it = std::find_if(token_types.begin(), token_types.end(), [this](auto token_type) {
        return token_type == Peek().value().type_;
    });

    return it != token_types.end();
}