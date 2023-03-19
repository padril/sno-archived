#ifndef SRC_ERRORS_BASE_ERROR_H_
#define SRC_ERRORS_BASE_ERROR_H_


#include <string>


namespace sno {




enum class ErrorID {
    unspecified_error,
    invalid_token,
    invalid_literal,
    syntax_error,
};


class BaseError {
 public:
    virtual void display() = 0;
};



}  // namespace sno


#endif  // SRC_ERRORS_BASE_ERROR_H_
