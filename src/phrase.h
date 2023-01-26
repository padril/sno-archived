// Copyright 2023 Leo James Peckham

#ifndef SETNOTATION_SRC_PHRASE_H_
#define SETNOTATION_SRC_PHRASE_H_

#include <string>
#include <list>
#include <iostream>
#include <tuple>
#include <vector>

#include "src/tokens.h"

class Phrase {
 public:
    struct PhraseType {
        std::vector<Token> tokens;
        std::list<Literal> literals;
    };

    std::vector<Literal> data;

    // TODO(padri): make these actually do something
    // Phrase(const std::string& expression);
    explicit Phrase(const char* expression);
    // Phrase(std::list<Token> token_list);
    // Phrase(const Phrase& other);

    ~Phrase();

 private:
    PhraseType parse(const std::string& str);
    Literal evaluate(std::vector<Token> token_list,
                    bool terminating = false);
    
    int t = 0;  // used for int&pos

    std::string expression;
    PhraseType phrase;
    std::string result;
};


#endif
