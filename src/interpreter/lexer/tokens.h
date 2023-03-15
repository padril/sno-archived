// Copyright 2023 Leo Peckham


#ifndef SRC_LEXER_TOKENS_H_
#define SRC_LEXER_TOKENS_H_


#include "src/types/types.h"
#include "src/type_definitions.h"

#include <string>
#include <variant>
#include <numeric>
#include <optional>


namespace sno {

enum class TokenID : token_type {
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


}  // namespace sno

#endif // SRC_TOKENS_H_