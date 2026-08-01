//
// Created by Dustin on 3/15/26.
//

#include "../include/Value.h"

std::ostream& operator<<(std::ostream& os, Value& v) {
    switch (v.type) {
        case ValueType::Int:
            os << v.int_value; break;
        case ValueType::Double:
            os << v.double_value; break;
        case ValueType::Boolean:
            os << v.bool_value; break;
    }

    return os;
}