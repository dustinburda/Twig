#ifndef TWIG_NODES_H
#define TWIG_NODES_H

#include "Value.h"

struct ASTNode {

};



struct Literal : ASTNode {
    Value value_;
};

enum class BinaryOperation {
    PLUS,
    MINUS,
    MULTIPLICATION,
    DIVISION,


    BANG_EQUAL,
    EQUAL_EQUAL,

    LESS,
    LESS_EQUAL,
    GREATER,
    GREATER_EQUAL,

    AND,
    OR,
};

struct Binary : ASTNode {
    BinaryOperation operation_;
    std::unique_ptr<ASTNode> left_expr_;
    std::unique_ptr<ASTNode> right_expr_;
};

enum class UnaryOperation {
    LogicalNot,
    Negate
};

struct Unary : ASTNode {

    UnaryOperation operation_;
    std::unique_ptr<ASTNode> expr_;
};

struct Grouping : ASTNode {
    std::unique_ptr<ASTNode> expr_;
};


#endif //TWIG_NODES_H
