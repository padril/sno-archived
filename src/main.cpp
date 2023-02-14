// Copyright 2023 Leo James Peckham

#include "src/parser/expression.h"

int main() {
    //std::string string = "";
    //while (true) {
    //    std::cout << ">>> ";
    //    std::getline(std::cin, string);
    //    if (string == "EXIT") {
    //        break;
    //    }
    //    Expression p = Expression(string);
    //}

    Phrase p = Expression::parse("1 + (2 - 3) * 4 / 5");
    p.tree();
}
