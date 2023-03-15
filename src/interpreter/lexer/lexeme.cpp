// Copyright 2023 Leo Peckham


#include "lexeme.h"


namespace sno {


// Groups for regex pattern
enum LexemeID {
    literal     = 1,
    symbol      = 4,
    identifier  = 5,
};


std::list<Lexeme> scan(const std::wstring& str) {
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
    std::list<Lexeme> ret;
    std::wsmatch match;

    while (std::regex_search(str_copy, match, pattern)) {
        if (match[literal] != L"") {
            ret.push_back({ literal, match.str(literal) });
        }
        else if (match[symbol] != L"") {
            ret.push_back({ symbol, match.str(symbol) });
        }
        else if (match[identifier] != L"") {
            ret.push_back({ identifier, match.str(identifier) });
        }
        else {
            std::wcout << "ERROR: Improper match" << std::endl;
        }
        str_copy = match.suffix();
    }

    return ret;
}

static enum literal_type {
    boolean = 1,
    integer,
    rational,
    real = 6,  // has to skip a few because of submatches in rational
    string
};


Token evaluate_literal(Lexeme lexeme) {

    static std::wregex pattern(
        L"(true|false)|"
        "([0-9]+)|"
        "([0-9]+(\\.0+)?/[0-9]+(\\.0+)?)|"
        "([0-9]+\\.[0-9]+)|"
        "(\"[^\"]*\")",
        std::regex_constants::extended
    );

    std::wsmatch match;
    std::regex_match(lexeme.value, match, pattern);
    std::wstring match_str = match.str();

    if (match[boolean] != L"") {
        return Token{ TokenID::LITERAL, match_str == L"true" };
    }
    else if (match[integer] != L"") {
        return Token{ TokenID::LITERAL, std::stoi(match_str) };
    }
    else if (match[rational] != L"") {
        size_t slash = match_str.find(L'/');
        integer_type num = stoi(match_str.substr(0, slash));
        integer_type den = stoi(match_str.substr(slash + 1, match_str.size() - slash - 1));
        return Token{ TokenID::LITERAL, Rational(num, den) };
    }
    else if (match[real] != L"") {
        return Token{ TokenID::LITERAL, std::stof(match_str) };
    }
    else if (match[string] != L"") {
        return Token{ TokenID::LITERAL, match_str.substr(1, match_str.size() - 2) };
    }
    else {
        std::cout << "INVALID LITERAL" << std::endl;
    }
}


Token evaluate_symbol(Lexeme lexeme) {
    return Token{ string_to_token_id(lexeme.value), std::nullopt };
}


Token evaluate_lexeme(Lexeme lexeme) {
    switch (lexeme.id) {
    case literal: return evaluate_literal(lexeme);
    case symbol: return evaluate_symbol(lexeme);
    //case identifier:    return evaluate_identifier(lex);
    };
}


std::list<Token> evaluate(std::list<Lexeme> lexeme_list) {
    std::list<Token> ret;

    for (Lexeme lexeme : lexeme_list) {
        ret.push_back(evaluate_lexeme(lexeme));
    }

    return ret;
}


}  // namespace sno
