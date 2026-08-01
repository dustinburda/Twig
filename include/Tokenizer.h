#ifndef TWIG_TOKENIZER_H
#define TWIG_TOKENIZER_H

#include <optional>
#include <string>
#include <vector>

#include "Token.h"
#include "Util.h"

class Tokenizer {
public:
    static Tokenizer& GetInstance() {
        static Tokenizer tokenizer;
        return tokenizer;
    }

    void Tokenize(const std::string& src, OUT std::vector<Token>& tokens);


private:
    std::optional<char> Peek();
    std::string PeekN(int n);
    std::optional<char> Consume();
    Token ConsumeNum();
    void ConsumeWhitespace();


    Tokenizer();

    std::string src_;
    std::size_t index_;
};

#endif // TWIG_TOKENIZER_H