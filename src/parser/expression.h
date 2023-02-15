// Copyright 2023 Leo Peckham

#ifndef SRC_PARSER_EXPRESSION_H_
#define SRC_PARSER_EXPRESSION_H_


#include "src/parser/phrase.h"
//#include "src/operators/operators.h"


class Expression {
 public:
    // Constructors
    Expression();
    explicit Expression(const std::wstring& _text);
    explicit Expression(const wchar_t* _text);
    ~Expression();

    
    // Public Members
    std::wstring to_latex();
    Phrase get_phrase();
    Literal execute(/*IdentifierList& scope*/);


    static Phrase parse(const std::wstring& str);

 private:
    // Attributes
    std::wstring text;
    Phrase phrase;


    // Parsing
    static Literal parse_literal(const std::wstring& str, int* pos);
    static Literal parse_set(const std::wstring& str, int* pos);
};


#endif  // SRC_EXPRESSION_H_
