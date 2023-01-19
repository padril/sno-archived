// Copyright 2023 Leo James Peckham

#include "src/phrase.h"

enum Phrase::Token {
    END_PHRASE,

    BEGIN_PRIORITY,
    END_PRIORITY,

    LITERAL_NULL,
    LITERAL_INT,
    LITERAL_VAR,

    POSITIVE,

    DYADS,  // admin token, used to determine monadic/dyadic
            // usage of operators in `parse`
    ADD,
};

Phrase::Phrase(const char* str) {
    expression = str;
    phrase = parse(expression);
    int t = 0;
    auto temp_result = evaluate(phrase.tokens);
    switch (temp_result.type) {
    case LITERAL_INT:
        result = std::to_string(*reinterpret_cast<int*>(temp_result.ptr));
        delete reinterpret_cast<int*>(temp_result.ptr);
        break;
    }
    std::cout << result;
}

Phrase::~Phrase() {}

auto parse_literal_or_variable(const std::string& str, int* pos) {
    struct returnType {
        Phrase::Token type;
        void* value;
    };

    auto is_digit = [](char c) { return '0' <= c && c <= '9'; };
    auto is_alpha = [](char c) {
      return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    };

    while (str[*pos] == ' ') (*pos)++;  // skip over spaces

    // TODO(padri): if it starts with "", dont return a variable type
    int start = *pos;
    size_t size = str.size();
    while (*pos < size && is_alpha(str[*pos])) (*pos)++;
    if (*pos > start) {  // there was a letter, its a variable
        while (start < size && (is_alpha(str[*pos]) || is_digit(str[*pos]))) {
            (*pos)++;
        }
        // have to do pos-- here to put pos back to the end of the literal
        return returnType{Phrase::LITERAL_VAR,
                          new std::string(str.substr(start, (*pos)-- - start))};
    } else {  // no letter,
        while (is_digit(str[*pos]) || str[*pos] == '.') (*pos)++;
        return returnType{Phrase::LITERAL_INT,
                          new int(stoi(str.substr(start, (*pos)-- - start)))};
    }
}


Phrase::PhraseType Phrase::parse(const std::string& str) {
    size_t size = str.size();

    std::vector<Token> local_phrase;
    std::list<void*> local_literals;

    for (int pos = 0; pos < str.size(); pos++) {
        switch (str[pos]) {
        case ' ': break;
        case '+':
            if (local_phrase.size() == 0 || local_phrase.back() > DYADS) {
                local_phrase.push_back(POSITIVE);
            } else {
                local_phrase.push_back(ADD);
            }
            break;
        case '(': local_phrase.push_back(BEGIN_PRIORITY); break;
        case ')': local_phrase.push_back(END_PRIORITY); break;
        case ':':
            switch (str[pos + 1]) {
            case '=' :
                break;
            }
        default:  // literal or variable
            auto temp = parse_literal_or_variable(str, &pos);
            local_phrase.push_back(temp.type);
            local_literals.push_back(temp.value);
            break;
        }
    }

    return PhraseType{ local_phrase, local_literals };
}

typedef Phrase::TypedPtr Tptr;
typedef Phrase::Token Token;

Tptr OPERATOR_POSITIVE(Tptr arg1) {
    using enum Token;
    switch (arg1.type) {
    case LITERAL_INT:
        return Tptr{ new int(+*reinterpret_cast<int*>(arg1.ptr)), LITERAL_INT };
        break;
    default: return Tptr{ nullptr, LITERAL_NULL }; break;
    }
}

Tptr OPERATOR_ADD(Tptr arg1, Tptr arg2) {
    using enum Token;
    // hacky way to get dynamic type deduction w/ ternary operator
    auto arg1val =
        arg1.type == LITERAL_INT ? *reinterpret_cast<int*>(arg1.ptr)
        /* else */ : 0;
    auto arg2val =
        arg2.type == LITERAL_INT ? *reinterpret_cast<int*>(arg2.ptr)
        /* else */ : 0;
    auto retval = arg1val + arg2val;
    Token rettype;
    if (std::is_same<decltype(retval), int>::value) {
        rettype = LITERAL_INT;
    }
    return Tptr{ new auto(retval), rettype };
}

Tptr Phrase::evaluate(std::vector<Token> token_list, bool terminating) {
    using enum Token;

    // this left thing is magic it works so much better than a stack approach
    Tptr left = {nullptr, LITERAL_NULL};
    static std::list<void*> literal_list = phrase.literals;
    static std::vector<Tptr> used;
    static int pos = 0;

    // the pos++; before an evaluate call prevents infinite loops
    for (; pos < token_list.size(); pos++) {
        switch (token_list[pos]) {
        case BEGIN_PRIORITY:
            pos++;
            left = evaluate(token_list, false);
            break;
        case END_PRIORITY:
            goto end;  // this is probably memory unsafe, check later
        case POSITIVE:
            pos++;
            left = OPERATOR_POSITIVE(evaluate(token_list, true));
            break;
        case ADD:
            switch (left.type) {
            case LITERAL_INT:
                pos++;
                left = OPERATOR_ADD(left, evaluate(token_list, true));
                break;
            }
            break;
        case LITERAL_INT:
            left = { literal_list.front(), LITERAL_INT };
            literal_list.pop_front();
            break;
        }
        // if left changed, add to used
        if (used.size() == 0 || left.ptr != used.back().ptr) {
            used.push_back(left);
        }
        if (terminating) break;
    }

    end:
    if (pos == token_list.size()) {
        // heavily indented, ik, maybe refactor later
        for (Tptr i : used) {
            if (i.ptr != left.ptr) {
                switch (i.type) {
                case LITERAL_INT: delete reinterpret_cast<int*>(i.ptr);
                }
            }
        }
    }
    return left;
}
