// Copyright 2023 Leo James Peckham

#include "src/phrase.h"
#include "src/tokens.h"
#include "src/operators/operators.h"

Phrase::Phrase() {
    expression = "";
    Literal result = Null();
    OPERATOR_PRINT(Null(), result);
}

Phrase::Phrase(const std::string& str) {
    expression = str;
    phrase = parse(expression);
    Literal result = evaluate(phrase);
    OPERATOR_PRINT(Null(), result);
}

Phrase::Phrase(const char* str) {
    expression = str;
    phrase = parse(expression);
    Literal result = evaluate(phrase);
    OPERATOR_PRINT(Null(), result);
}

Phrase::~Phrase() {}

Literal parse_literal(const std::string& str, int* pos) {
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


Phrase::PhraseType Phrase::parse(const std::string& str) {
    size_t size = str.size();
    using enum Token;

    std::list<Token> local_phrase;
    std::list<Literal> local_literals;

    for (int pos = 0; pos < str.size(); pos++) {
        switch (str[pos]) {
            case ' ': continue;
            case '+': local_phrase.push_back(PLUS); break;
            case '*': local_phrase.push_back(TIMES); break;
            case '/': local_phrase.push_back(SLASH); break;
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

    return PhraseType{ local_phrase, local_literals };
}

Literal Phrase::evaluate(PhraseType& local_phrase, bool terminating) {
    using enum Token;
    using enum Type;

    // this left thing is magic it works so much better than a stack approach
    Literal left = {Null()};
    std::list<Token>* tokens = &local_phrase.tokens;
    std::list<Literal>* literals = &local_phrase.literals;

    // the pos++; before an evaluate call prevents infinite loops
    while (tokens->size() > 0) {
        switch (tokens->front()) {
            case BEGIN_PRIORITY:
                tokens->pop_front();
                left = evaluate(local_phrase, false);
                break;
            case END_PRIORITY:
                tokens->pop_front();
                return left;
            case PLUS:
                tokens->pop_front();
                left = OPERATOR_PLUS(left, evaluate(local_phrase, true));
                break;
            case TIMES:
                tokens->pop_front();
                left = OPERATOR_TIMES(left, evaluate(local_phrase, true));
                break;
            case SLASH:
                tokens->pop_front();
                left = OPERATOR_SLASH(left, evaluate(local_phrase, true));
                break;
            case LITERAL:
                tokens->pop_front();
                left = literals->front();
                literals->pop_front();
                if (terminating) {
                    goto end;
                }
                else {
                    break;
                }
        }
    }
end:
    // do some conversions down under certain circumstances
    if (std::holds_alternative<TYPE_REAL>(left)) {
        auto f = std::get<TYPE_REAL>(left);
        if (f == std::floor(f)) {
            left = static_cast<TYPE_INT>(f);
        }
    }
    if (std::holds_alternative<Rational>(left)) {
        if (std::get<Rational>(left).denominator() == 1) {
            left = TYPE_INT(std::get<Rational>(left));
        }
    }
    return left;
}
