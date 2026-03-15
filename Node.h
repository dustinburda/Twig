#ifndef TWIG_NODES_H
#define TWIG_NODES_H

#include <memory>

enum class NodeType {
    Double,
    Int,
    Op
};

struct ASTNode {
public:
    ASTNode(NodeType type) : type_{type} {}
    virtual ~ASTNode() = default;

    NodeType type_;
    std::unique_ptr<ASTNode> left_;
    std::unique_ptr<ASTNode> right_;
};


struct DoubleNode : public ASTNode {
    DoubleNode(double value) : ASTNode(NodeType::Double), value_{value} {}
    virtual ~DoubleNode() = default;


    double value_;

};

struct IntNode : public ASTNode {
    IntNode(int value) : ASTNode(NodeType::Int), value_{value} {}
    virtual ~IntNode() = default;


    int value_;
};

struct OpNode : public ASTNode {
    OpNode(char value)  :ASTNode(NodeType::Op), value_{value} {}
    virtual ~OpNode() = default;

    char value_;
};

#endif //TWIG_NODES_H
