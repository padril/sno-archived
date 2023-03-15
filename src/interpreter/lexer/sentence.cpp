// Copyright 2023 Leo James Peckham


#include "src/interpreter/lexer/sentence.h"


namespace sno {

// ===
// Constructors
// ===


Sentence::Sentence(const std::wstring& str) {
    text = str;
    int t = 0;;
}


Sentence::~Sentence() {}


// ===
// Public Members
// ===


Tree* Sentence::parse() {
    if (text.size() == 0) {
        return {};
    }

    using enum TokenID;
    std::list<Tree*> trees;
    std::list<Token> tokens = evaluate(scan(text));

    for (Token t : tokens) {
        Tree* tree = new Tree{t};  // can throw InvalidToken
        trees.push_back(tree);
    }

    return create_tree(trees);
}


}  // namespace sno
