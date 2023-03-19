
// Copyright 2023 Leo Peckham


#include "interface/output/output.h"

#include <iostream>
#include <string>

#include "types/types.h"
#include "operators/operators.h"


namespace sno {




void TerminalOutput::display(
    DisplayOption option,
    void* result,
    ResultType type) {
    BaseError* error = nullptr;
    Literal* lit = nullptr;
    switch (type) {
    case ResultType::error:
        break;
    case ResultType::literal:
        lit = reinterpret_cast<Literal*>(result);
        OPERATOR_REPRESENTATION(Null(), *lit);
        break;
    }
}

}