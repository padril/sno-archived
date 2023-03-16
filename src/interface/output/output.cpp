
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
    Error* error = nullptr;
    Literal* lit = nullptr;
    switch (type) {
    case ResultType::error:
        error = reinterpret_cast<Error*>(result);
        std::wcout
            << L"Error #" << static_cast<int>(error->id)
            << L" at line (" << error->line
            << L"):" << std::endl
            << L"\t" << error->message << std::endl;
        break;
    case ResultType::literal:
        lit = reinterpret_cast<Literal*>(result);
        OPERATOR_REPRESENTATION(Null(), *lit);
        break;
    }
}

}