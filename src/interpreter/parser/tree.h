
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_INTERPRETER_PARSER_TREE_H_
#define SNO_SRC_INTERPRETER_PARSER_TREE_H_


#include <iostream>
#include <optional>
#include <list>

#include "types/types.h"
#include "interpreter/parser/tree.h"
#include "interpreter/lexer/tokens.h"


namespace sno {




struct Tree {
    std::optional<Token> root;
    Tree* left = nullptr;
    Tree* right = nullptr;

    size_t size();

    Literal execute();

    friend std::wostream& operator<<(std::wostream& out, Tree tree);
    // TODO(padril): a descructor that calls child destructors
};

Tree* create_tree(std::list<Tree*> trees);




}  // namespace sno


#endif  // SNO_SRC_INTERPRETER_PARSER_TREE_H_
