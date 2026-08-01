#include "../include/Tokenizer.h"

#include <stdexcept>


void Tokenizer::Tokenize(const std::string& src, OUT std::vector<Token>& tokens) {
    index_ = 0;
    src_ = src;
    tokens.clear();

    ConsumeWhitespace();

    while (Peek().has_value()) {
        ConsumeWhitespace();
        auto curr_char = Peek().value();

        switch (curr_char) {
            case '+': Consume(); tokens.push_back(Token{&curr_char, TokenType::PLUS}); break;
            case '-': Consume(); tokens.push_back(Token{&curr_char, TokenType::MINUS}); break;
            case '*': Consume(); tokens.push_back(Token{&curr_char, TokenType::MULTIPLICATION}); break;
            case '/': Consume(); tokens.push_back(Token{&curr_char, TokenType::DIVISION}); break;
            case '(': Consume(); tokens.push_back(Token{&curr_char, TokenType::LEFT_PAREN}); break;
            case ')': Consume(); tokens.push_back(Token{&curr_char, TokenType::RIGHT_PAREN}); break;
            case '{': Consume(); tokens.push_back(Token{&curr_char, TokenType::LEFT_BRACE}); break;
            case '}': Consume(); tokens.push_back(Token{&curr_char, TokenType::RIGHT_BRACE}); break;
            case '!': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    Consume();
                    tokens.push_back(Token{&curr_char, TokenType::BANG_EQUAL});
                    break;
                } else {
                    tokens.push_back(Token{&curr_char, TokenType::BANG});
                    break;
                }

            }
            case '=': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    Consume();
                    tokens.push_back(Token{&curr_char, TokenType::EQUAL_EQUAL});
                    break;
                } else {
                    tokens.push_back(Token{&curr_char, TokenType::EQUAL});
                    break;
                }

            }
            case '&': {
                if (PeekN(2) == "&&") {
                    Consume();
                    Consume();
                    tokens.push_back(Token{"&&", TokenType::AND});
                }

                break;
            }
            case '|': {
                if (PeekN(2) == "||") {
                    Consume();
                    Consume();
                    tokens.push_back(Token{"||", TokenType::OR});
                }

                break;
            }
            case '<': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    tokens.push_back(Token{"<=", TokenType::LESS_EQUAL});
                    Consume();
                } else {
                    tokens.push_back(Token{"<", TokenType::LESS});
                }

                break;
            }
            case '>': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    tokens.push_back(Token{">=", TokenType::GREATER_EQUAL});
                    Consume();
                }
                else
                    tokens.push_back(Token{">", TokenType::GREATER});

                break;
            }
            default: {
                // TODO: FIX
                if (std::isdigit(curr_char)) {
                    tokens.push_back(ConsumeNum());
                    break;
                }
                if (PeekN(4) == "true") {
                    // TODO: ConsumeN
                    tokens.push_back(Token{true});
                    break;
                }
                if (PeekN(5) == "false"){
                    tokens.push_back(Token{false});
                    break;
                }
            }

        }
    }

    tokens.push_back(Token{TokenType::EOF_});
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

Token Tokenizer::ConsumeNum() {
    char curr_char = Consume().value();
    std::string num {curr_char};


    while (Peek().has_value() && std::isdigit(Peek().value())) {
        num += Consume().value();
    }

    if (Peek().has_value() && Peek().value() == '.') {
        num += Consume().value();

        while (Peek().has_value() && std::isdigit(Peek().value())) {
            num += Consume().value();
        }

        return Token {std::stod(num)};
    }
    else
    {
        return Token {std::stoi(num)};
    }

    throw std::logic_error("Unidentified token");
};

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
