
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_LEXER_SENTENCE_H_
#define SNO_SRC_LEXER_SENTENCE_H_


#include <string>

#include "interpreter/parser/tree.h"


namespace sno {




// ===
// Sentence is the text representation of our code.
// It is the building block that becomes Token lists and Trees,
// which are far more flexible and memory efficient.
// ===


class Sentence {
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




}  // namespace sno


#endif  // SNO_SRC_LEXER_SENTENCE_H_
