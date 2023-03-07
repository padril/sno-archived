// Copyright Leo Peckham 2023


#ifndef SRC_LEXER_LEXEME_H_
#define SRC_LEXER_LEXEME_H_


#include "src/lexer/tokens.h"
#include "src/types/types.h"

#include <list>
#include <string>
#include <regex>
#include <iostream>


namespace lexer {


enum LexemeID;

struct Lexeme {
    LexemeID id;
    std::wstring value;
};

std::list<Token> evaluate(const std::list<Lexeme> lexeme_list);
std::list<Lexeme> scan(const std::wstring& str);

Token evaluate_lexeme(Lexeme lex);

Token evaluate_literal(Lexeme lex);
Token evaluate_symbol(Lexeme lex);
//Token evaluate_identifier(lexeme lex);


}  // namespace lexer

#endif  // SRC_LEXER_LEXEME_H_
