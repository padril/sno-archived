// Copyright 2023 Leo James Peckham


#include "src/parser/expression.h"
#include "src/operators/operators.h"


// Constructors
Expression::Expression() {
    text = L"";
    phrase = {};
    Literal result = Null();
}

Expression::Expression(const std::wstring& str) {
    text = str;
    phrase = parse(text);
    Literal result = phrase.evaluate();
    OPERATOR_PRINT(Null(), result);
}

Expression::Expression(const wchar_t* str) {
    text = str;
    phrase = parse(text);
    Literal result = phrase.evaluate();
    OPERATOR_PRINT(Null(), result);
}

Expression::~Expression() {}

// Helper Functions
Literal Expression::parse_set(const std::wstring& str, int* pos) {
    using Universal = SN_real;

    std::deque<Universal> init;

    while (*pos < str.size()) {
        switch (str[*pos]) {
        case ',': break;
        case '}': goto end;
        default:
            Universal x;
            Literal y = parse_literal(str, pos);
            if (std::holds_alternative<SN_int>(y)) {
                x = std::get<SN_int>(y);
            } else if (std::holds_alternative<SN_real>(y)) {
                x = std::get<SN_real>(y);
            }
            init.push_back(x);
        }
        (*pos)++;
    }
end:
    (*pos)++;
    Set set = TemplateSet(init);
    return set;
}

Literal Expression::parse_literal(const std::wstring& str, int* pos) {
    auto is_digit = [](char c) { return '0' <= c && c <= '9'; };
    auto is_alpha = [](char c) {
      return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    };

    while (str[*pos] == ' ') (*pos)++;  // skip over spaces

    size_t start = *pos;
    size_t size = str.size();

    /* reference from TODO.txt until complete
    Literals
     o ` used for mathematical constants and stuff, `inf, `R, `C, `pi, `e
       to be honest idk if this one should be a literal, definitely do it last
     o "" used for strings
     x 123 ... numeric
     x . reals
     o 123i imaginary
	     o 123i + 456 complex (procresses faster)
     o abc123 variable
     o (12, 34] intervals
     o [12 34 56] higher dimensonal vectors
     
     o SET??? idk if they should be literals
    */

    // we have to do pos-- here to put pos back to the end of the literal
    // maybe change that into a defer statement
    // (tsoding's olive.c uses one with #DEFINE)
    if (str[*pos] == '"') {
        // STRING "I love pointers!"
        (*pos)++;
        while (str[*pos] != '"') {
            if (str[*pos] == '\\') {
                (*pos)++;
            }
            (*pos)++;
        }
        // some slightly weird shifts by one here to remove quotes
        start++;
        auto ret = Literal(str.substr(start, *pos - start).c_str());
        return ret;
    } else if (str[*pos] == '{') {
        (*pos)++;
        return parse_set(str, pos);
    } else if (is_alpha(str[*pos])) {
        // VARIABLE abc123
        while (start < size && (is_alpha(str[*pos]) || is_digit(str[*pos]))) {
            (*pos)++;
        }
    } else if (is_digit(str[*pos])) {
        // INTEGER or REAL 123 or 123.456
        while (is_digit(str[*pos])) (*pos)++;
        if (str[*pos] == '.') {
            // REAL 123.456
            (*pos)++;
            while (is_digit(str[*pos])) (*pos)++;
            return Literal(stof(str.substr(start, (*pos)-- - start)));
        // TODO: make rationals a literal?
        } else {
            // INTEGER 123
            return Literal(stoi(str.substr(start, (*pos)-- - start)));
        }
    } else {
        // TODO(padril): handle error unknown character in literal
    }
}


Phrase Expression::parse(const std::wstring& str) {
    size_t size = str.size();
    using enum Token;

    std::list<Token> local_phrase;
    std::list<Literal> local_literals;

    for (int pos = 0; pos < str.size(); pos++) {
        switch (str[pos]) {
            case ' ': continue;
            case '+': local_phrase.push_back(PLUS); break;
            case '-': local_phrase.push_back(MINUS); break;
            case '*': local_phrase.push_back(TIMES); break;
            case '/': local_phrase.push_back(SLASH); break;
            // CURRENTLY JUST A DEBUG TREE PRINT
            case '$': local_phrase.push_back(PRINT); break;
            case '(': local_phrase.push_back(BEGIN_PRIORITY); break;
            case ')': local_phrase.push_back(END_PRIORITY); break;
            case ':':
                switch (str[pos + 1]) {
                    case '=':
                      break;
                }
                break;
            default:  // literal or variable
                local_phrase.push_back(LITERAL);
                local_literals.push_back(parse_literal(str, &pos));
                break;
        }
    }

    return Phrase{ local_phrase, local_literals };
}
