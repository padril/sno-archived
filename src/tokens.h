#ifndef SRC_TOKENS_H_
#define SRC_TOKENS_H_

#include <string>
#include <variant>
#include "src/set.h"

typedef struct{} nulltype;
typedef std::variant<nulltype, int, float, std::string> Literal;

enum class Type : size_t {
    LITERAL_NULL,
    LITERAL_INT,
    LITERAL_REAL,
    LITERAL_STRING,
};

enum class Token {
    END_PHRASE,

    BEGIN_PRIORITY,
    END_PRIORITY,

    LITERAL,

    POSITIVE,

    DYADS,  // admin token, used to determine monadic/dyadic
    // usage of operators in `parse`
    PLUS,
};

#endif // SRC_TOKENS_H_
