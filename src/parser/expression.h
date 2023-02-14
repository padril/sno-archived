// Copyright 2023 Leo Peckham

#ifndef SRC_PARSER_EXPRESSION_H_
#define SRC_PARSER_EXPRESSION_H_


#include "src/parser/phrase.h"
//#include "src/operators/operators.h"


class Expression {
 public:
    // Constructors
    Expression();
    explicit Expression(const std::string& _text);
    explicit Expression(const char* _text);
    ~Expression();

    
    // Public Members
    std::string to_latex();
    Phrase get_phrase();
    Literal execute(/*IdentifierList& scope*/);


    static Phrase parse(const std::string& str);

 private:
    // Attributes
    std::string text;
    Phrase phrase;


    // Parsing
    static Literal parse_literal(const std::string& str, int* pos);
    static Literal parse_set(const std::string& str, int* pos);
};


#endif  // SRC_EXPRESSION_H_
