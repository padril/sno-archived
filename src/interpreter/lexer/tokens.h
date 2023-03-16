
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_LEXER_TOKENS_H_
#define SNO_SRC_LEXER_TOKENS_H_


#include <string>
#include <optional>

#include "types/types.h"
#include "types/type_definitions.h"


namespace sno {




enum class TokenID : token_type {
    INVALID_TOKEN = 'IT',

    BEGIN_PHRASE = 'BP',
    END_PHRASE = 'EP',
    EMPTY = 'EM',

    BEGIN_PRIORITY = '(',
    END_PRIORITY = ')',
    BEGIN_SET = '{',
    END_SET = '}',

    LITERAL = 'L',

    SYMBOL,
    PLUS = '+',
    MINUS = '-',
    TIMES = '*',
    SLASH = '/',
    PRINT = '$',
    DEBUG_PRINT = ';$',
};

std::wstring token_id_to_string(TokenID token);
TokenID string_to_token_id(std::wstring string);

struct Token {
    TokenID id;
    std::optional<Literal> value;
};




}  // namespace sno

#endif  // SNO_SRC_LEXER_TOKENS_H_
