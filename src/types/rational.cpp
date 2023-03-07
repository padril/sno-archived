#include "src/types/rational.h"


// Constructors
Rational::Rational (set_type::integer p, set_type::integer q /* = 1 */) { set(p, q); }
Rational::~Rational() {}


// Implicit Conversion
Rational::operator set_type::integer () const { return num / den; }
Rational::operator set_type::real() const { return static_cast<set_type::real>(num) / den; }


// Public members
set_type::integer Rational::numerator()         { return num; }
set_type::integer Rational::denominator()       { return den; }
void Rational::set(set_type::integer p, set_type::integer q) {
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
