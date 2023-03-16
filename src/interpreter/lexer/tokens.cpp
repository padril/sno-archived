
// Copyright 2023 Leo Peckham


#include "interpreter/lexer/tokens.h"

#include <string>
#include <variant>
#include <numeric>
#include <optional>

#include "types/types.h"
#include "types/type_definitions.h"


namespace sno {




// ===
// Functions
// ===


std::wstring token_id_to_string(TokenID token_id) {
    wchar_t str[sizeof(token_type)] = {};
    for (int i = 0; i < sizeof(token_type); ++i) {
        str[i] = (static_cast<token_type>(token_id) & 0xFF << i * 8) >> i * 8;
    }
    return str;
}


TokenID string_to_token_id(std::wstring str) {
    token_type t = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        t |= static_cast<token_type>(str[i]) << (8 * (str.size() - i - 1));
    }
    return TokenID(t);
}



}  // namespace sno
