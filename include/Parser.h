#ifndef TWIG_PARSER_H
#define TWIG_PARSER_H

#include <memory>
#include <optional>
#include <vector>

#include "Node.h"
#include "Token.h"

// TODO: Make sure to understand associativity and precedence

/*
 * Grammar:
 *
 * Program := Expression* EOF
 * Expression := Comparison
 * Comparison := Logical ( (BANG_EQUAL | EQUAL_EQUAL) Logical)*
 * Logical := Inequality ( (AND | OR) Inequality)*
 * Inequality := Add ( (LESS | LESS_EQ | GREATER | GREATER_EQ) Add)*
 * Add := Mult ( (PLUS | MINUS) Mult)*
 * Mult := Unary ( (MULT | DIVIDE) Unary)*
 * Unary := (BANG | MINUS) Unary | Primary
 * Primary := Grouping | INTEGER | DOUBLE | STRING | TRUE | FALSE |
 * Grouping := LEFT_PAREN Expression RIGHT_PAREN
 */

class Parser {
public:
    static Parser& GetInstance();

    std::unique_ptr<ASTNode> Parse(const std::vector<Token>& tokens);

private:
    std::unique_ptr<ASTNode> ParseProgram();
    std::unique_ptr<ASTNode> ParseExpression();
    std::unique_ptr<ASTNode> ParseComparison();
    std::unique_ptr<ASTNode> ParseLogical();
    std::unique_ptr<ASTNode> ParseInequality();
    std::unique_ptr<ASTNode> ParseAdd();
    std::unique_ptr<ASTNode> ParseMult();
    std::unique_ptr<ASTNode> ParseUnary();
    std::unique_ptr<ASTNode> ParsePrimary();
    std::unique_ptr<ASTNode> ParseGrouping();

    std::optional<Token> Peek();
    std::optional<Token> PeekN(int n);
    std::optional<Token> Consume();
    bool MatchTokens(const std::vector<TokenType>& tokens);

    Parser();

    std::vector<Token> tokens_;
    std::size_t index_;
};

#endif // TWIG_PARSER_H