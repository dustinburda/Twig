//
// Created by Dustin on 3/15/26.
//

#include "../include/Interpreter.h"

void Interpreter::Interpret(std::string& src) {
    Tokenizer& tokenizer = Tokenizer::GetInstance();

    std::vector<Token> tokens;
    tokenizer.Tokenize(src, tokens);

    Parser& parser = Parser::GetInstance();
    auto ast = std::move(parser.Parse(tokens));

    auto result = Evaluate(ast);

    std::cout << result << std::endl;
}

Value Interpreter::Evaluate(std::unique_ptr<ASTNode>& ast) {
    if (ast->type_ == NodeType::Double)
        return Value{static_cast<DoubleNode*>(ast.get())->value_};
    if (ast->type_ == NodeType::Int)
        return Value{static_cast<IntNode*>(ast.get())->value_};

    if (ast->type_ == NodeType::Op) {
        auto operation = static_cast<OpNode*>(ast.get())->value_;
        auto left = Evaluate(ast->left_);
        auto right = Evaluate(ast->right_);

        auto left_num = left.type == ValueType::Int ? left.int_value : left.double_value;
        auto right_num = right.type == ValueType::Int ? right.int_value : right.double_value;

        switch (operation) {
            case '+':
                return Value{left_num + right_num};
            case '-':
                return Value{left_num - right_num};
            case '*':
                return Value{left_num * right_num};
            case '/':
                return Value{left_num / right_num};
        }
    }

    throw std::logic_error("Can't be evaluated!");
}
