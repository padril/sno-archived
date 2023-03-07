#include "src/parser/tokens.h"

std::wstring token_id_to_string(TokenID token_id) {
    wchar_t str[sizeof(SN_token)] = {};
    for (int i = 0; i < sizeof(SN_token); ++i) {
        str[i] = (static_cast<SN_token>(token_id) & 0xFF << i * 8) >> i * 8;
    }
    return str;
}

TokenID string_to_token_id(std::wstring str) {
    SN_token t = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        t += static_cast<SN_token>(str[i]) * pow(16, i);
    }
    return TokenID(t);
}

