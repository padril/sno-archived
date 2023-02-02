#include "rational.h"

Rational::Rational() { set(); }

Rational::Rational(TYPE_INT p, TYPE_INT q) {
//    std::enable_if<std::is_same<T, TYPE_INT>::value>::type*) {
    set(p, q);
}

Rational::~Rational() {}

TYPE_INT Rational::numerator() { return num; }
TYPE_INT Rational::denominator() { return den; }

Rational::operator TYPE_INT() const {
    return num / den;
}

Rational::operator TYPE_REAL() const {
    return static_cast<TYPE_REAL>(num) / den;
}

void Rational::set() {
    num = 0;
    den = 1;
}
void Rational::set(TYPE_INT x) {
    num = x;
    den = 1;
}
void Rational::set(TYPE_INT p, TYPE_INT q) {
    num = p; den = q; simplify();
}


void Rational::simplify() {
    auto gcd = std::gcd(num, den);
    num /= gcd;
    den /= gcd;
}


Rational operator+(const Rational& x) {
    return x;
}
Rational operator-(const Rational& x) {
    return { -x.num, x.den };
}

#define _ARITHMETIC_OPERATOR(symbol, ...)\
    Rational operator##symbol(const Rational& x, const Rational& y) {\
        return __VA_ARGS__;\
    }\
    Rational operator##symbol(const Rational& x, TYPE_INT y) {\
        return x symbol Rational(y);\
    }\
    Rational operator##symbol(TYPE_INT x, const Rational& y) {\
        return Rational(x) symbol y;\
    }\
    TYPE_REAL operator##symbol(const Rational& x, TYPE_REAL y) {\
        return TYPE_REAL(x) symbol y;\
    }\
    TYPE_REAL operator##symbol(TYPE_REAL x, const Rational& y) {\
        return x symbol TYPE_REAL(y);\
    }

_ARITHMETIC_OPERATOR(+, { x.num * y.den + y.num * x.den, x.den * y.den })
_ARITHMETIC_OPERATOR(-, { x.num * y.den - y.num * x.den, x.den * y.den })
_ARITHMETIC_OPERATOR(*, { x.num * y.num, x.den * y.den })
_ARITHMETIC_OPERATOR(/, { x.num * y.den, y.num * x.den })

#undef _ARITHMETIC_OPERATOR

std::ostream& operator<<(std::ostream& out, const Rational& x) {
    out << x.num << '/' << x.den;
    return out;
}