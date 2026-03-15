#include <cassert>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <optional>
#include <variant>
#include <memory>

#include "Interpreter.h"

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