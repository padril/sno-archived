// Copyright 2023 Leo James Peckham

#include "src/phrase.h"

int main() {
    std::string expression = "";
    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, expression);
        if (expression == "EXIT") {
            break;
        }
        Phrase p = Phrase(expression);
    }
}
