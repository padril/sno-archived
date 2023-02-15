#include "src/types/rational.h"


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
Rational operator+(const Rational& x, const Rational& y) {
    return { x.num * y.den + y.num * x.den, x.den * y.den };
}
Rational operator-(const Rational& x, const Rational& y) {
    return { x.num * y.den - y.num * x.den, x.den * y.den };
}
Rational operator*(const Rational & x, const Rational & y) {
    return { x.num * y.num, x.den * y.den };
}
Rational operator/(const Rational & x, const Rational & y) {
    return { x.num * y.den, y.num * x.den };
}

std::wostream& operator<<(std::wostream& out, const Rational& x) {
    out << x.num << '/' << x.den;
    return out;
}
