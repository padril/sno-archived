#include "lexer.h"

enum lexer::lexeme_id {
    literal = 1,
    symbol = 4,
    identifier,
};

std::list<lexer::lexeme> lexer::scan(const std::wstring& str) {
    static std::wregex pattern(
        L"("
        "true|false|"
        "[0-9]+|"
        "[0-9]+(\\.0+)?/[0-9]+(\\.0+)?|"
        "[0-9]+\\.[0-9]+|"
        "\"[^\"]*\""
        ")|"
        "([,(){}]|\\+|-|\\*|/|\\$|;\\$)|"
        "([a-zA-Z][a-zA-Z0-9]*)",
        std::regex_constants::extended
    );

    std::wstring str_copy = str;
    std::list<lexer::lexeme> ret;
    std::wsmatch match;

    while (std::regex_search(str_copy, match, pattern)) {
        if (match[literal] != L"") {
            ret.push_back({ literal, match.str(literal) });
        } else if (match[symbol] != L"") {
            ret.push_back({ symbol, match.str(symbol) });
        } else if (match[identifier] != L"") {
            ret.push_back({ identifier, match.str(identifier) });
        } else {
            std::wcout << "ERROR: Improper match" << std::endl;
        }
        str_copy = match.suffix();
    }

    return ret;
}

Token lexer::evaluate_literal(lexer::lexeme lex) {
    static enum literal_type {
        boolean = 1,
        integer,
        rational,
        real = 6,  // has to skip a few because of submatches in rational
        string
    };

    static std::wregex pattern(
        L"(true|false)|"
        "([0-9]+)|"
        "([0-9]+(\\.0+)?/[0-9]+(\\.0+)?)|"
        "([0-9]+\\.[0-9]+)|"
        "(\"[^\"]*\")",
        std::regex_constants::extended
    );

    std::wsmatch match;
    std::regex_match(lex.value, match, pattern);
    std::wstring match_str = match.str();

    if (match[boolean] != L"") {
        return Token{ TokenID::LITERAL, match_str == L"true" };
    } else if (match[integer] != L"") {
        return Token{ TokenID::LITERAL, stoi(match_str) };
    } else if (match[rational] != L"") {
        size_t slash = match_str.find(L'/');
        SN_int num = stoi(match_str.substr(0, slash));
        SN_int den = stoi(match_str.substr(slash+1, match_str.size()-slash-1));
        return Token{ TokenID::LITERAL, Rational(num, den) };
    } else if (match[real] != L"") {
        return Token{ TokenID::LITERAL, stof(match_str) };
    } else if (match[string] != L"") {
        return Token{ TokenID::LITERAL, match_str.substr(1, match_str.size() - 2) };
    } else {
        std::cout << "INVALID LITERAL" << std::endl;
    }
}

Token lexer::evaluate_symbol(lexer::lexeme lex) {
    return Token{ string_to_token_id(lex.value), std::nullopt };
}

Token lexer::evaluate_lexeme(lexer::lexeme lex) {
    switch (lex.id) {
    case literal:       return evaluate_literal(lex);
    case symbol:     return evaluate_symbol(lex);
    //case identifier:    return evaluate_identifier(lex);
    };
}

std::list<Token> lexer::evaluate(std::list<lexer::lexeme> lexeme_list) {
    std::list<Token> ret;

    for (lexer::lexeme lex : lexeme_list) {
        ret.push_back(lexer::evaluate_lexeme(lex));
    }

    return ret;
}
