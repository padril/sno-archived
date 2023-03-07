#ifndef SRC_TOKENS_H_
#define SRC_TOKENS_H_

#include <string>
#include <variant>
#include <numeric>
#include <optional>
#include "src/types/set.h"
#include "src/types/types.h"

enum class TokenID : SN_token {
    BEGIN_PHRASE = 'B',
    END_PHRASE = 'E',
    EMPTY = 'X',


    BEGIN_PRIORITY = '(',
    END_PRIORITY = ')',
    BEGIN_SET = '{',
    END_SET = '}',

    STRING = 'S',
    LITERAL = 'L',

    SYMBOL,
    PLUS = '+',
    MINUS = '-',
    TIMES = '*',
    SLASH = '/',
    PRINT = '$',
    DEBUG_PRINT = ';$',
};

struct Token {
    TokenID id;
    std::optional<Literal> value;
};

std::wstring token_id_to_string(TokenID token);
TokenID string_to_token_id(std::wstring string);

#endif // SRC_TOKENS_H_
