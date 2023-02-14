// Copyright 2023 Leo James Peckham

#ifndef SRC_PARSER_PHRASE_H_
#define SRC_PARSER_PHRASE_H_


#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <set>

#include "src/parser/tokens.h"
#include "src/types/types.h"


struct Node {
    Token token;
    Node* left = nullptr;
    Node* right = nullptr;
    // Variant variant;

    // TODO(padril): a descructor that calls child destructors
};


struct Phrase {
    std::list<Token> tokens;
    std::list<Literal> literals;

    Node* tree();

    // TODO(padril): evaluate needs to be updated for trees
    Literal evaluate(bool terminating = false);
};


#endif
