// Copyright 2023 Leo James Peckham


#include "src/parser/expression.h"
#include "src/operators/operators.h"
#include <optional>




// ===
// Constructors
// ===


Expression::Expression() {
    text = L"";
    phrase = {};
    Literal result = Null();
}


Expression::Expression(const std::wstring& str) {
    text = str;
    int t = 0;
    phrase = parse(text, &t);
}


Expression::Expression(const wchar_t* str) {
    text = str;
    int t = 0;
    phrase = parse(text, &t);
}


Expression::~Expression() {}




// ===
// Parsing
// ===


#include "src/parser/lexer.h"


Phrase Expression::parse(const std::wstring& str, int* pos = 0) {
    using enum TokenID;
    std::list<Node*> nodes;
    std::list<Token> tokens = lexer::evaluate(lexer::scan(str));

    for (Token t : tokens) {
        Node* node = new Node{t};  // can throw InvalidToken
        nodes.push_back(node);;
    }

    return {nodes};
}
