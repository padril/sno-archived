#include "src/types/rational.h"


// TODO (padril): all of this mess should be in operator_generator.py
// These typedefinitions are only used to condense the macro
#define _CRR const Rational&
#define _RAT Rational
#define _ARITHMETIC_OPERATOR(sym, ... /* Operation */)\
    _RAT  operator##sym(_CRR  x, _CRR  y) { return __VA_ARGS__; /* Op */  }\
    _RAT  operator##sym(_CRR  x, SN_int  y) { return      (x) sym _RAT (y); }\
    _RAT  operator##sym(SN_int  x, _CRR  y) { return _RAT (x) sym      (y); }\
    SN_real operator##sym(_CRR  x, SN_real y) { return SN_real(x) sym      (y); }\
    SN_real operator##sym(SN_real x, _CRR  y) { return      (x) sym SN_real(y); }\


// Constructors
Rational::Rational (SN_int p, SN_int q /* = 1 */) { set(p, q); }
Rational::~Rational() {}


// Implicit Conversion
Rational::operator SN_int () const { return num / den; }
Rational::operator SN_real() const { return static_cast<SN_real>(num) / den; }


// Public members
SN_int Rational::numerator()         { return num; }
SN_int Rational::denominator()       { return den; }
void Rational::set(SN_int p, SN_int q) {
    auto gcd = std::gcd(p, q);
    num = p / gcd;
    den = q / gcd;
}


// Operators
Rational operator+(const Rational& x) { return x; }
Rational operator-(const Rational& x) { return { -x.num, x.den }; }
_ARITHMETIC_OPERATOR(+, { x.num * y.den + y.num * x.den, x.den * y.den })
_ARITHMETIC_OPERATOR(-, { x.num * y.den - y.num * x.den, x.den * y.den })
_ARITHMETIC_OPERATOR(*, { x.num * y.num, x.den * y.den })
_ARITHMETIC_OPERATOR(/, { x.num * y.den, y.num * x.den })
std::ostream& operator<<(std::ostream& out, const Rational& x) {
    out << x.num << '/' << x.den;
    return out;
}


#undef _CRR
#undef _RAT
#undef _ARITHMETIC_OPERATOR
