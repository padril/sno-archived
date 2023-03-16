
// Copyright Leo Peckham 2023


#ifndef SNO_SRC_LEXER_LEXEME_H_
#define SNO_SRC_LEXER_LEXEME_H_


#include <list>
#include <string>

#include "interpreter/lexer/tokens.h"
#include "interpreter/lexer/lexeme.h"


namespace sno {




enum LexemeID;

struct Lexeme {
    LexemeID id;
    std::wstring value;

    Token evaluate_lexeme();

    Token evaluate_literal();
    Token evaluate_symbol();
    // Token evaluate_identifier(lexeme lex);
};

std::list<Lexeme> scan(const std::wstring& str);
std::list<Token> evaluate(const std::list<Lexeme> lexeme_list);




}  // namespace sno


#endif  // SNO_SRC_LEXER_LEXEME_H_
