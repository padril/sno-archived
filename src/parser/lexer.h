#ifndef SRC_PARSER_LEXER_H_
#define SRC_PARSER_LEXER_H_

#include "src/parser/tokens.h"
#include "src/types/types.h"

#include <list>
#include <string>
#include <regex>
#include <iostream>

namespace lexer
{

    enum lexeme_id;
    struct lexeme {
        lexeme_id id;
        std::wstring value;
    };

    std::list<Token> evaluate(const std::list<lexeme> lexeme_list);
    std::list<lexeme> scan(const std::wstring& str);

    Token evaluate_lexeme(lexeme lex);

    Token evaluate_literal(lexeme lex);
    Token evaluate_symbol(lexeme lex);
    //Token evaluate_identifier(lexeme lex);

}

#endif
