#include "src/parser/tokens.h"

std::wstring token_to_string(Token token) {
    wchar_t str[sizeof(SN_token)] = {};
    for (int i = 0; i < sizeof(SN_token); ++i) {
        str[i] = (static_cast<SN_token>(token) & 0xFF << i * 8) >> i * 8;
    }
    return str;
}
