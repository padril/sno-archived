// Copyright 2023 Leo Peckham

#ifndef SRC_INTERPRETER_TREE_H_
#define SRC_INTERPRETER_TREE_H_

#include "src/interpreter/lexer/tokens.h"
#include "src/operators/operators.h"
#include <vector>
#include <optional>
#include <set>
#include <stack>
#include <list>

namespace sno {

struct Tree {
    std::optional<sno::Token> root;
    Tree* left = nullptr;
    Tree* right = nullptr;

    size_t size();

    sno::Literal evaluate();

    friend std::wostream& operator<<(std::wostream& out, Tree tree);
    // TODO(padril): a descructor that calls child destructors
};

Tree* create_tree(std::list<Tree*> trees);

}

#endif  // SRC_INTERPRETER_TREE_H_
