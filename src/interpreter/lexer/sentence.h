// Copyright 2023 Leo Peckham


#ifndef SRC_LEXER_SENTENCE_H_
#define SRC_LEXER_SENTENCE_H_


#include "src/interpreter/parser/tree.h"
#include "src/interpreter/lexer/lexeme.h"
#include "src/interpreter/lexer/tokens.h"


namespace sno {


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
    
    Tree* parse();

private:

    // Attributes
    std::wstring text;
};


}  // namespace Lexer

#endif  // SRC_SENTENCE_H_
