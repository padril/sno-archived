// Copyright 2023 Leo James Peckham

#include "src/parser/expression.h"

#include <io.h>     // Permits us to use
#include <fcntl.h>  // unicode

int main() {

    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    //std::wstring string = "";
    //while (true) {
    //    std::wcout << ">>> ";
    //    std::getline(std::wcin, string);
    //    if (string == "EXIT") {
    //        break;
    //    }
    //    Expression p = Expression(string);
    //}

    Phrase p = Expression::parse(L"1 * (3 - 6) + 4 + 4");
    std::wcout << p.tree();
}
