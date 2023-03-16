#ifndef SRC_ERRORS_BASE_H_
#define SRC_ERRORS_BASE_H_


#include <string>


namespace sno {




enum class ErrorID {
    invalid_token,
    invalid_literal,
    syntax_error,
};


struct Error {
    ErrorID id;
    std::wstring message;
    size_t line;
};



}  // namespace sno


#endif  // SRC_ERRORS_BASE_H_
