
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_INTERFACE_OUTPUT_SCREEN_H_
#define SNO_SRC_INTERFACE_OUTPUT_SCREEN_H_


#include <vector>
#include <string>
#include <iostream>

#include "interpreter/parser/tree.h"


namespace sno {




class Screen {
    std::vector<std::wstring> display;
    size_t mid;

    explicit Screen(const Tree& some_tree);

    void pad(size_t width, size_t height);

    friend std::wostream& operator<<(std::wostream& out, Screen screen);
};




}  // namespace sno


#endif  // SNO_SRC_INTERPRETER_SCREEN_H_
