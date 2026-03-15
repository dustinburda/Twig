#ifndef TWIG_INTERPRETER_H
#define TWIG_INTERPRETER_H

#include "Parser.h"
#include "Node.h"
#include "Tokenizer.h"
#include "Value.h"


class Interpreter {
public:
    static Interpreter& GetInstance() {
        static Interpreter instance;
        return instance;
    }

    void Interpret(std::string& src);

private:
    Value Evaluate(std::unique_ptr<ASTNode>& ast);
    Interpreter() = default;
};


#endif //TWIG_INTERPRETER_H
