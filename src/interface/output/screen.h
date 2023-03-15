// Copyright 2023 Leo Peckham

#ifndef SRC_INTERFACE_OUTPUT_SCREEN_H_
#define SRC_INTERFACE_OUTPUT_SCREEN_H_

#include "src/interpreter/parser/tree.h"

#include <vector>
#include <string>

namespace sno {

class Screen {
    std::vector<std::wstring> display;
    size_t mid;

    explicit Screen(const Tree& some_tree);

    void pad(size_t width, size_t height);

    friend std::wostream& operator<<(std::wostream& out, Screen screen);
};

}  // namespace sno

#endif  // SRC_INTERPRETER_SCREEN_H_
