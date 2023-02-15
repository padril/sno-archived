#ifndef SRC_TOKENS_H_
#define SRC_TOKENS_H_

#include <string>
#include <variant>
#include <numeric>
#include "src/types/set.h"

enum class Token : SN_token {
    BEGIN_PHRASE = 'B',
    END_PHRASE = 'E',

    BEGIN_PRIORITY = '(',
    END_PRIORITY = ')',
    BEGIN_SET = '{',
    END_SET = '}',

    LITERAL = 'L',

    PLUS = '+',
    MINUS = '-',
    TIMES = '*',
    SLASH = '/',
    PRINT = '$',
    DEBUG_PRINT = ';$',
};

std::wstring token_to_string(Token token);

#endif // SRC_TOKENS_H_
