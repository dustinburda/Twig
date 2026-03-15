#ifndef TWIG_PARSER_H
#define TWIG_PARSER_H

#include <optional>
#include <vector>

#include "Node.h"
#include "Token.h"

class Parser {
public:
    static Parser& GetInstance() {
        static Parser parser;
        return parser;
    }

    std::unique_ptr<ASTNode> Parse(const std::vector<Token>& tokens);

private:
    std::unique_ptr<ASTNode> ParseExpr();
    std::unique_ptr<ASTNode> ParseTerm();
    std::unique_ptr<ASTNode> ParseFactor();
    std::unique_ptr<ASTNode> ParseNum();
    std::unique_ptr<ASTNode> ParseOp();

    std::optional<Token> Peek();
    std::optional<Token> PeekN(int n);
    std::optional<Token> Consume();

    Parser();

    std::vector<Token> tokens_;
    std::size_t index_;
};

#endif // TWIG_PARSER_H