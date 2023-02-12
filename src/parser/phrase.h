// Copyright 2023 Leo James Peckham

#ifndef SRC_PARSER_PHRASE_H_
#define SRC_PARSER_PHRASE_H_


#include <string>
#include <list>
#include <iostream>

#include "src/parser/tokens.h"
//#include "src/operators/operators.h"
#include "src/types/types.h"


struct Phrase {
    std::list<Token> tokens;
    std::list<Literal> literals;

    Literal evaluate(bool terminating = false);
};


#endif
