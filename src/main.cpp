// Copyright 2023 Leo James Peckham

#include "src/operators/operators.h"
#include "src/parser/lexer.h"

#include <io.h>     // Permits us to use
#include <fcntl.h>  // unicode

int main() {

    _setmode(_fileno(stdout), _O_WTEXT);
    _setmode(_fileno(stdin), _O_WTEXT);

    std::wstring string = L"";
    while (true) {
        std::wcout << L">>> ";
        std::getline(std::wcin, string);
        if (string == L"exit") {
            break;
        }
        Sentence p = Sentence(string);
        OPERATOR_REPRESENTATION(Null(), p.phrase.evaluate());
    }

    //Phrase p = Sentence::parse(L"4 / (3) + 2");
    //std::wcout << p.tree();
}
