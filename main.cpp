#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <optional>
#include <variant>
#include <memory>

#define OUT

enum class TokenType {
    PLUS,
    MINUS,
    INTEGER,
    DOUBLE,
    LEFT_PAREN,
    RIGHT_PAREN
};


struct Token {
    Token(int num) : type_{TokenType::INTEGER} {
        int_num_ = num;
    }

    Token(double num) : type_{TokenType::DOUBLE} {
        double_num_ = num;
    }

    Token(char c, TokenType type) : type_{type}, operation_{c} {}

    TokenType type_;

    union {
        int int_num_;
        double double_num_;
        char operation_;
    };

    std::string toString() {
        std::stringstream ss;

        ss << "TokenType: ";
        switch (type_) {
            case TokenType::PLUS:
                ss << "PLUS";
                break;
            case TokenType::MINUS:
                ss << "MINUS";
                break;
            case TokenType::INTEGER:
                ss << "INTEGER";
                break;
            case TokenType::DOUBLE:
                ss << "DOUBLE";
                break;
        }

        ss << "\n";
        ss << "Value: ";

        switch (type_) {
            case TokenType::PLUS:
            case TokenType::MINUS:
                ss << operation_;
                break;
            case TokenType::INTEGER:
                ss << int_num_;
                break;
            case TokenType::DOUBLE:
                ss << double_num_;
                break;
        }

        return ss.str();
    }

    static bool IsOpToken(Token t) {
        return t.type_ == TokenType::PLUS || t.type_ == TokenType::MINUS;
    }

    static bool IsNumToken(Token t) {
        return t.type_ == TokenType::INTEGER || t.type_ == TokenType::DOUBLE;
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
        tokens.clear();

        ConsumeWhitespace();

        while (Peek().has_value()) {
            ConsumeWhitespace();
            auto curr_char = Consume().value();

            switch (curr_char) {
                case '+': tokens.push_back(Token{curr_char, TokenType::PLUS}); break;
                case '-': tokens.push_back(Token{curr_char, TokenType::MINUS}); break;
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
        index_++;

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

enum class NodeType {
    Double,
    Int,
    Op
};

struct ASTNode {
public:
    ASTNode(NodeType type) : type_{type} {}
    virtual ~ASTNode() = 0;

    NodeType type_;
    std::unique_ptr<ASTNode> left_;
    std::unique_ptr<ASTNode> right_;
};
ASTNode::~ASTNode() = default;


// TODO: Virtual destructors
struct DoubleNode : public ASTNode {
    DoubleNode(double value) : ASTNode(NodeType::Double), value_{value} {}
    virtual ~DoubleNode() = default;


    double value_;

};

// TODO: Virtual destructors
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


        std::unique_ptr<ASTNode> root_node = ParseNumNode(Consume().value());
        while (Peek().has_value() && Token::IsOpToken(Peek().value())) {
            auto op = std::make_unique<OpNode>(Consume().value().operation_);
            auto num_node = ParseNumNode(Consume().value());

            op->left_ = std::move(root_node);
            op->right_ = std::move(num_node);

            root_node = std::move(op);
        }

        return std::move(root_node);
    }

    std::unique_ptr<ASTNode> ParseNumNode(const Token& t) {
        switch (t.type_) {
            case TokenType::DOUBLE:
                return std::make_unique<DoubleNode>(t.double_num_);
            case TokenType::INTEGER:
                return std::make_unique<IntNode>(t.int_num_);
            default:
                throw std::logic_error("Can't parse num node with non-number token.");
        }

        return nullptr;
    }

    std::optional<Token> Peek() {
        if (index_ >= tokens_.size())
            return std::nullopt;

        return tokens_[index_];
    }

    std::optional<Token> PeekN(int n) {
         if (index_ + n - 1 >= tokens_.size())
             return std::nullopt;

         return tokens_[index_ + n - 1];
    }

    std::optional<Token> Consume() {
        if (index_ >= tokens_.size())
            return std::nullopt;

        Token token = tokens_[index_];
        index_++;

        return token;
    }

    Parser() = default;

    std::vector<Token> tokens_;
    std::size_t index_;
};

enum class ValueType {
    Int,
    Double
};

struct Value {
public:
    ValueType type;

    union {
        int int_value;
        double double_value;
    };

    Value (int i) : type{ValueType::Int}, int_value{i} {}
    Value (double d) : type{ValueType::Double}, double_value{d} {}

    friend std::ostream& operator<<(std::ostream& os, Value& v);
};

std::ostream& operator<<(std::ostream& os, Value& v) {
    switch (v.type) {
        case ValueType::Int:
            os << v.int_value; break;
        case ValueType::Double:
            os << v.double_value; break;
    }

    return os;
}

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

        Parser& parser = Parser::GetInstance();
        auto ast = std::move(parser.Parse(tokens));

        auto result = Evaluate(ast);

        std::cout << result << std::endl;
    }

private:
    Value Evaluate(std::unique_ptr<ASTNode>& ast) {
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
            }
        }
    }

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