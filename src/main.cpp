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
<<<<<<< Updated upstream
        Expression p = Expression(string);
        OPERATOR_REPRESENTATION(Null(), p.phrase.evaluate());
=======
        lexer::Sentence s(string);
        Phrase p = s.parse();
        if (p.nodes.front()->token.id != lexer::string_to_token_id(L"$") &&
            p.nodes.front()->token.id != lexer::string_to_token_id(L";$") ) {
            OPERATOR_REPRESENTATION(Null(), p.evaluate());
        }
        else {
            p.evaluate();
        }
>>>>>>> Stashed changes
    }

    //Phrase p = Expression::parse(L"4 / (3) + 2");
    //std::wcout << p.tree();
}
