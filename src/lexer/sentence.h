// Copyright 2023 Leo Peckham


#ifndef SRC_PARSER_EXPRESSION_H_
#define SRC_PARSER_EXPRESSION_H_


#include "src/parser/phrase.h"
#include "src/lexer/lexeme.h"
#include "src/lexer/tokens.h"


namespace lexer {


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


}  // namespace lexer

#endif  // SRC_EXPRESSION_H_
