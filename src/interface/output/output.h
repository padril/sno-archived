
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_INTERFACE_OUTPUT_OUTPUT_H_
#define SNO_SRC_INTERFACE_OUTPUT_OUTPUT_H_


#include <iostream>
#include <variant>

#include "types/types.h"
#include "errors/base.h"


namespace sno {




typedef void* Result;  // can be Error* or Literal*

enum class ResultType {
    error,
    literal,
};

enum class DisplayOption {
    halt,
    wait,
    cont,
};

class Output {
 public:
    // Context context (contains the dbgp options)
    //                 (+ variables for eval)
    virtual void display(
        DisplayOption option,
        void* result,
        ResultType type) = 0;
};

class TerminalOutput : public Output {
 public:
    void display(
        DisplayOption option,
        void* result,
        ResultType type);
};
// Evaluate input based on options
// Catch errors, output put error messages into screen
// else put evaluation into screen




}  // namespace sno


#endif  // SNO_SRC_INTERFACE_OUTPUT_OUTPUT_H_
