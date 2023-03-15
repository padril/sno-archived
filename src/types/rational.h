// Copyright 2023 Leo Peckham

#ifndef SRC_TYPES_RATIONAL_H_
#define SRC_TYPES_RATIONAL_H_

#include <compare>

#include <numeric>
#include <iostream>

#include "src/type_definitions.h"

namespace sno {

class Rational {
 public:
    // Constructors
    // TODO(padril): declare explicit and do conversions in operator_generator
    Rational(integer_type p = 0, integer_type q = 1);
    ~Rational();


    // Public Methods
    integer_type numerator();
    integer_type denominator();
    void set(integer_type p = 0, integer_type q = 1);


    // Conversion
    explicit operator integer_type() const;
    explicit operator real_type() const;


    // Operators
    friend Rational operator+(const Rational& x);
    friend Rational operator-(const Rational& x);
    friend Rational operator+(const Rational& x, const Rational& y);
    friend Rational operator-(const Rational& x, const Rational& y);
    friend Rational operator*(const Rational& x, const Rational& y);
    friend Rational operator/(const Rational& x, const Rational& y);

    auto operator<=>(const Rational& x) const {
        return real_type(*this) - real_type(x);
    }

    friend std::wostream& operator<<(std::wostream& out, const Rational& x);


 private:
    // Attributes
    integer_type num;
    integer_type den;
};

}  // namespace sno

#endif  // SRC_TYPES_RATIONAL_H_
