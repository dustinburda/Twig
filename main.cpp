#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <optional>
#include <variant>
#include <memory>

#define OUT

template<class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};

enum class TokenType {
    PLUS,
    MINUS,
    INTEGER,
    DOUBLE
};

struct Token {
    TokenType type_;
    std::variant<std::monostate,
                 int,
                 double,
                 char> value_;

    std::string toString() {
        std::stringstream ss;

        ss << "TokenType: ";
        switch (type_) {
            case TokenType::PLUS:
                ss << "PLUS";
            case TokenType::MINUS:
                ss << "MINUS";
            case TokenType::INTEGER:
                ss << "INTEGER";
            case TokenType::DOUBLE:
                ss << "DOUBLE";
        }

        ss << "\n";
        ss << "Value: ";

        std::visit(overloaded {
            [&ss](std::monostate) { ss << "None"; },
            [&ss](char c) {ss << c;},
            [&ss](double d){ ss << d;},
            [&ss](int i) { ss << i;}
        }, value_);

        return ss.str();
    }
};


class Tokenizer {
public:
    static Tokenizer& GetInstance() {
        static Tokenizer tokenizer;
        return tokenizer;
    }

    void Tokenize(const std::string& src, OUT std::vector<Token>& tokens) {
        index_ = 0;
        src_ = src;

        ConsumeWhitespace();

        while (Peek().has_value()) {
            ConsumeWhitespace();
            auto curr_char = Consume().value();

            switch (curr_char) {
                case '+': tokens.emplace_back(Token{TokenType::PLUS, curr_char });
                case '-': tokens.emplace_back(Token{TokenType::MINUS, curr_char });
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

                            tokens.emplace_back(Token{type, std::stod(num)});
                        }
                        else
                        {
                            tokens.emplace_back(Token{type, std::stoi(num)});
                        }


                    }
                }

            }
        }

    }


private:
    std::optional<char> Peek() {
        if (index_ >= src_.size())
            return std::nullopt;

        return src_[index_];
    }

    std::optional<char> Consume() {
        if (index_ >= src_.size())
            return std::nullopt;

        auto curr_char = src_[index_];
        index_;

        return curr_char;
    }

    std::string PeekN(int n) {
        std::string s;

        for (int i = 0; i < n; i++) {
            if (!Peek().has_value())
                break;

            s += Consume().value();
        }

        return s;
    }

    void ConsumeWhitespace() {
        while (Peek().has_value() && Peek().value() == ' ')
            Consume();
    }


    Tokenizer() = default;

    std::string src_;
    std::size_t index_;
};

struct ASTNode {
public:
    virtual ~ASTNode() = 0;
};

struct NumberNode : public ASTNode {
    NumberNode(double value) : value_{value} {}

    double value_;
    std::unique_ptr<ASTNode> left_;
    std::unique_ptr<ASTNode> right_;
};

struct OpNode : public ASTNode {
    OpNode(char value) : value_{value} {}

    char value_;
    std::unique_ptr<ASTNode> left_;
    std::unique_ptr<ASTNode> right_;
};



class Parser {
public:
    static Parser& GetInstance() {
        static Parser parser;
        return parser;
    }

    std::unique_ptr<ASTNode> Parse(const std::vector<Token>& tokens) {
        tokens_ = tokens;
        index_ = 0;

        return ParseExpr();
    }

private:
    std::unique_ptr<ASTNode> ParseExpr() {
        if (index_ == tokens_.size())
            return nullptr;

        auto number_token = tokens_[index_];
        index_++;

//        while
//
//        auto op_token = tokens_[index_];
//        index_++;
//
//        if (number_token.type_ != TokenType::INTEGER && number_token.type_ != TokenType::DOUBLE)
//            throw std::logic_error("Invalid program");
//
//        if (op_token.type_ != TokenType::MINUS && op_token.type_ != TokenType::PLUS)
//            throw std::logic_error("Invalid program");
//
//        auto node = std::make_unique<OpNode>(std::get<char>(op_token.value_));
//        node->left_ = std::make_unique<NumberNode>(std::get<double>(op_token.value_));
//        node->right_ = ParseExpr();
//
//        return node;
    }

    std::optional<Token> Peek() {
        // TODO:
    }

    std::optional<Token> PeekN(int n) {
         // TODO:
    }

    std::optional<Token> Consume() {
        // TODO:
    }

    Parser() = default;

    std::vector<Token> tokens_;
    std::size_t index_;
};

class Interpreter {
public:
    static Interpreter& GetInstance() {
        static Interpreter instance;
        return instance;
    }

    void Interpret(std::string& src) {
        Tokenizer& tokenizer = Tokenizer::GetInstance();

        std::vector<Token> tokens;
        tokenizer.Tokenize(src, tokens);

    }

private:
    Interpreter() = default;
};



int main() {
    Interpreter& interpreter = Interpreter::GetInstance();

    while (true) {
        std::cout << "Twig> " << std::flush;

        std::string line;
        std::getline(std::cin, line);

        if (std::cin.eof())
            exit(1);

        interpreter.Interpret(line);
    }

    return 0;
}