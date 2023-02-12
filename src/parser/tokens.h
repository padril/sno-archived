#ifndef SRC_TOKENS_H_
#define SRC_TOKENS_H_

#include <string>
#include <variant>
#include <numeric>
#include "src/types/set.h"

enum class Token {
    END_PHRASE,

    BEGIN_PRIORITY,
    END_PRIORITY,
    BEGIN_SET,
    END_SET,

    LITERAL,

    POSITIVE,

    PLUS,
    MINUS,
    TIMES,
    SLASH,
};

#endif // SRC_TOKENS_H_
