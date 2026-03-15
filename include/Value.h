//
// Created by Dustin on 3/15/26.
//

#ifndef TWIG_VALUE_H
#define TWIG_VALUE_H

#include <iostream>

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

std::ostream& operator<<(std::ostream& os, Value& v);

#endif //TWIG_VALUE_H
