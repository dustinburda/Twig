#include "../include/Tokenizer.h"

#include <stdexcept>


std::vector<Token> Tokenizer::Tokenize(const std::string& src) {
    std::vector<Token> tokens;

    index_ = 0;
    src_ = src;

    ConsumeWhitespace();

    while (Peek().has_value()) {
        ConsumeWhitespace();

        if (!Peek().has_value())
            break;

        auto curr_char = Peek().value();

        switch (curr_char) {
            case '+': Consume(); tokens.emplace_back(TokenType::PLUS); break;
            case '-': Consume(); tokens.emplace_back(TokenType::MINUS); break;
            case '*': Consume(); tokens.emplace_back(TokenType::MULTIPLICATION); break;
            case '/': Consume(); tokens.emplace_back(TokenType::DIVISION); break;
            case '(': Consume(); tokens.emplace_back(TokenType::LEFT_PAREN); break;
            case ')': Consume(); tokens.emplace_back(TokenType::RIGHT_PAREN); break;
            case '{': Consume(); tokens.emplace_back(TokenType::LEFT_BRACE); break;
            case '}': Consume(); tokens.emplace_back(TokenType::RIGHT_BRACE); break;
            case '"': {
                Consume(); // "

                std::string literal;
                while (Peek().has_value() && Peek().value() != '"')
                    literal += Consume().value();

                Consume(); // "

                tokens.emplace_back(TokenType::STRING, literal);
                break;
            }
            case '!': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    Consume();
                    tokens.emplace_back(TokenType::BANG_EQUAL);
                    break;
                } else {
                    tokens.emplace_back(TokenType::BANG);
                    break;
                }

            }
            case '=': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    Consume();
                    tokens.emplace_back(TokenType::EQUAL_EQUAL);
                    break;
                } else {
                    tokens.emplace_back(TokenType::EQUAL);
                    break;
                }

            }
            case '&': {
                if (PeekN(2) == "&&") {
                    Consume();
                    Consume();
                    tokens.emplace_back(TokenType::AND);
                }

                break;
            }
            case '|': {
                if (PeekN(2) == "||") {
                    Consume();
                    Consume();
                    tokens.emplace_back(TokenType::OR);
                }

                break;
            }
            case '<': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    tokens.emplace_back(TokenType::LESS_EQUAL);
                    Consume();
                } else {
                    tokens.emplace_back(TokenType::LESS);
                }

                break;
            }
            case '>': {
                Consume();
                if (Peek().has_value() && Peek().value() == '=') {
                    tokens.emplace_back(TokenType::GREATER_EQUAL);
                    Consume();
                }
                else
                    tokens.emplace_back(TokenType::GREATER);

                break;
            }
            default: {
                if (std::isdigit(curr_char)) {
                    tokens.emplace_back(ConsumeNum());
                    break;
                }
                else if (std::isalpha(curr_char)) {
                    tokens.emplace_back(ConsumeIdentifier());
                }
                else {
                    throw std::runtime_error("Wrong token");
                }
            }

        }
    }

    tokens.emplace_back(TokenType::EOF_);

    return tokens;
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

Token Tokenizer::ConsumeIdentifier() {
    std::string identifier;
    while (Peek().has_value() && (std::isalnum(Peek().value()) || Peek().value() == '_'))
        identifier += Consume().value();

    if (reserved_words.contains(identifier))
        return Token{reserved_words[identifier]};

    return Token {TokenType::IDENTIFIER, identifier};
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
