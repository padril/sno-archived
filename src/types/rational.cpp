#include "src/types/rational.h"


namespace sno {

// Constructors
Rational::Rational (integer_type p, integer_type q /* = 1 */) { set(p, q); }
Rational::~Rational() {}


// Implicit Conversion
Rational::operator integer_type () const { return num / den; }
Rational::operator real_type() const { return static_cast<real_type>(num) / den; }


// Public members
integer_type Rational::numerator()         { return num; }
integer_type Rational::denominator()       { return den; }
void Rational::set(integer_type p, integer_type q) {
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

}  // namespace sno
