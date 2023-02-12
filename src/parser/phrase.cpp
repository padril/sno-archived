// Copyright 2023 Leo Peckham

#include "src/parser/phrase.h"
#include "src/operators/operators.h"


Literal Phrase::evaluate(bool terminating) {
    using enum Token;
    using enum Type;

    Literal left = Null();

    while (tokens.size() > 0) {
        Token current_token = tokens.front();
        tokens.pop_front();
        switch (current_token) {
        case BEGIN_PRIORITY:
            left = evaluate();
            break;
        case END_PRIORITY:
            goto end;
        case PLUS:
            left = OPERATOR_PLUS(left, evaluate(true));
            break;
        case MINUS:
            left = OPERATOR_MINUS(left, evaluate(true));
            break;
        case TIMES:
            left = OPERATOR_TIMES(left, evaluate(true));
            break;
        case SLASH:
            left = OPERATOR_SLASH(left, evaluate(true));
            break;
        case LITERAL:
            left = literals.front();
            literals.pop_front();
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
    if (std::holds_alternative<SN_real>(left)) {
        auto f = std::get<SN_real>(left);
        if (f == std::floor(f)) {
            left = static_cast<SN_int>(f);
        }
    }
    if (std::holds_alternative<Rational>(left)) {
        if (std::get<Rational>(left).denominator() == 1) {
            left = SN_int(std::get<Rational>(left));
        }
    }
    return left;
}
