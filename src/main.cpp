
// Copyright 2023 Leo James Peckham


#include <io.h>     // Permits us to use
#include <fcntl.h>  // unicode

#include <iostream>
#include <string>

#include "interface/output/output.h"
#include "types/types.h"
#include "interpreter/lexer/tokens.h"
#include "interpreter/parser/tree.h"
#include "operators/operators.h"
#include "interpreter/lexer/sentence.h"
#include "interpreter/lexer/lexeme.h"


int main() {

    (void)_setmode(_fileno(stdout), _O_WTEXT);
    (void)_setmode(_fileno(stdin), _O_WTEXT);


    sno::TerminalOutput terminal_output = sno::TerminalOutput();
    sno::Output* output = &terminal_output;


    std::wstring string = L"";
    while (true) {
        std::wcout << L">>> ";
        std::getline(std::wcin, string);
        if (string == L"exit") {
            break;
        }
        sno::Sentence s(string);
        sno::Tree* p = s.parse();
        auto res = p->execute();
        if (p->root->id != sno::string_to_token_id(L"$")) {
            output->display(
                sno::DisplayOption::cont,
                &res,
                sno::ResultType::literal);
        }
    }
}
