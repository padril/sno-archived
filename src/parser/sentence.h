// Copyright 2023 Leo Peckham

#ifndef SRC_PARSER_EXPRESSION_H_
#define SRC_PARSER_EXPRESSION_H_




// ===
// INCLUDES
// ===


#include "src/parser/phrase.h"
#include "src/parser/lexer.h"




// ===
// Sentence is the text representation of our code.
// It is the building block that becomes Phrases and Trees,
// which are far more flexible and memory efficient.
// ===


class Sentence
{
public:

    // Constructors
    explicit Sentence(const std::wstring& _text);
    ~Sentence();

    // Public Members
    
    // TODO(padril): implement the following
    // std::wstring to_latex();
    // Literal execute(/*IdentifierList& scope*/);

    Phrase parse();

private:

    // Attributes
    std::wstring text;
};




#endif  // SRC_EXPRESSION_H_
