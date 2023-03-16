
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_INTERPRETER_PARSER_TREE_DISPLAY_H_
#define SNO_SRC_INTERPRETER_PARSER_TREE_DISPLAY_H_


#include <vector>
#include <string>
#include <iostream>

#include "interpreter/parser/tree.h"


namespace sno {




class TreeDisplay {
    std::vector<std::wstring> display;
    size_t mid;

    explicit TreeDisplay(const Tree& tree);

    void pad(size_t width, size_t height);

    friend std::wostream& operator<<(std::wostream& out,
        TreeDisplay tree_display);
};




}  // namespace sno


#endif  // SNO_SRC_INTERPRETER_PARSER_TREE_DISPLAY_H_
