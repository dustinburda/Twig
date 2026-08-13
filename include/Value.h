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
        const char* string_value_;
    };

    Value (int i) : type{ValueType::Int}, int_value{i} {}
    Value (double d) : type{ValueType::Double}, double_value{d} {}
};

#endif //TWIG_VALUE_H
