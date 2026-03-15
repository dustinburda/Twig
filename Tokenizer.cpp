#include "Tokenizer.h"




void Tokenizer::Tokenize(const std::string& src, OUT std::vector<Token>& tokens) {
    index_ = 0;
    src_ = src;
    tokens.clear();

    ConsumeWhitespace();

    while (Peek().has_value()) {
        ConsumeWhitespace();
        auto curr_char = Consume().value();

        switch (curr_char) {
            case '+': tokens.push_back(Token{curr_char, TokenType::PLUS}); break;
            case '-': tokens.push_back(Token{curr_char, TokenType::MINUS}); break;
            case '*': tokens.push_back(Token{curr_char, TokenType::PLUS}); break;
            case '/': tokens.push_back(Token{curr_char, TokenType::MINUS}); break;
            case '(': tokens.push_back(Token{curr_char, TokenType::LEFT_PAREN}); break;
            case ')': tokens.push_back(Token{curr_char, TokenType::RIGHT_PAREN}); break;
            default: {
                if (std::isdigit(curr_char)) {

                    std::string num {curr_char};

                    TokenType type = TokenType::INTEGER;

                    while (Peek().has_value() && std::isdigit(Peek().value())) {
                        num += Consume().value();
                    }

                    if (Peek().has_value() && Peek().value() == '.') {
                        num += Consume().value();
                        type = TokenType::DOUBLE;

                        while (Peek().has_value() && std::isdigit(Peek().value())) {
                            num += Consume().value();
                        }

                        tokens.push_back(Token {std::stod(num)});
                    }
                    else
                    {
                        tokens.push_back(Token {std::stoi(num)});
                    }


                }
            }

        }
    }

}

std::optional<char> Tokenizer::Peek() {
    if (index_ >= src_.size())
        return std::nullopt;

    return src_[index_];
}

std::optional<char> Tokenizer::Consume() {
    if (index_ >= src_.size())
        return std::nullopt;

    auto curr_char = src_[index_];
    index_++;

    return curr_char;
}

std::string Tokenizer::PeekN(int n) {
    std::string s;

    for (int i = 0; i < n; i++) {
        if (!Peek().has_value())
            break;

        s += Consume().value();
    }

    return s;
}

void Tokenizer::ConsumeWhitespace() {
    while (Peek().has_value() && Peek().value() == ' ')
        Consume();
}


Tokenizer::Tokenizer() = default;
