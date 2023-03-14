// Copyright 2023 Leo Peckham


#include "src/lexer/tokens.h"


namespace lexer {


std::wstring token_id_to_string(TokenID token_id) {
    wchar_t str[sizeof(set_type::token)] = {};
    for (int i = 0; i < sizeof(set_type::token); ++i) {
        str[i] = (static_cast<set_type::token>(token_id) & 0xFF << i * 8) >> i * 8;
    }
    return str;
}


TokenID string_to_token_id(std::wstring str) {
    set_type::token t = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        t |= static_cast<set_type::token>(str[i]) << (8 * (str.size() - i - 1));
    }
    return TokenID(t);
}


}  // namespace lexer
