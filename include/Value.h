//
// Created by Dustin on 3/15/26.
//

#ifndef TWIG_VALUE_H
#define TWIG_VALUE_H

#include <iostream>


enum class ValueType {
    Int,
    Double,
    Boolean,
    String
};

struct Value {
public:
    ValueType type;

    union {
        int int_value;
        double double_value;
        bool bool_value;
        char* string_value_;
    };

    Value (int i) : type{ValueType::Int}, int_value{i} {}
    Value (double d) : type{ValueType::Double}, double_value{d} {}
    Value (const char* s) : type{ValueType::String} {
        int length = strlen(s);
        string_value_ = new char[length + 1];
        std::memcpy(string_value_, s, length);
        string_value_[length] = '\0';
    }
    Value (bool b) : type{ValueType::Boolean}, bool_value{b} {}

    ~Value() {
        if (type == ValueType::String)
            delete[] string_value_;
    }
};

#endif //TWIG_VALUE_H
