// Copyright 2023 Leo James Peckham

#ifndef SETNOTATION_SRC_PHRASE_H_
#define SETNOTATION_SRC_PHRASE_H_

#include <string>
#include <list>
#include <iostream>
#include <tuple>
#include <vector>

class Phrase {
 public:
    enum Token;

    struct PhraseType {
        std::vector<Token> tokens;
        std::list<void*> literals;
    };

    struct TypedPtr {
        void* ptr;
        Phrase::Token type;
    };

    std::vector<void*> data;

    // TODO(padri): make these actually do something
    // Phrase(const std::string& expression);
    explicit Phrase(const char* expression);
    // Phrase(std::list<Token> token_list);
    // Phrase(const Phrase& other);

    ~Phrase();

 private:
    PhraseType parse(const std::string& str);
    TypedPtr evaluate(std::vector<Phrase::Token> token_list, bool terminating = false);

    int t = 0;  // used for int&pos

    std::string expression;
    PhraseType phrase;
    std::string result;
};


#endif
