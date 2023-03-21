
// Copyright (C) 2023 Leo Peckham

#ifndef SRC_ERRORS_INVALID_ARITY_ERROR_H_
#define SRC_ERRORS_INVALID_ARITY_ERROR_H_


#include <iostream>

#include "errors/base_error.h"


namespace sno {




    class InvalidArityError : public BaseError {
    public:
        // able to include information about token in here
        InvalidArityError(auto line_, auto message_)
            : line(line_), message(message_) {}
        size_t line;
        std::wstring message;

        void display() {
            std::wcerr << message
                << L" on line " << line
                << std::endl;
        }
    };



}  // namespace sno


#endif  // SRC_ERRORS_INVALID_TOKEN_ERROR_H_


