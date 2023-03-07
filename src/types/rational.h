// Copyright 2023 Leo Peckham

#ifndef SRC_TYPES_RATIONAL_H_
#define SRC_TYPES_RATIONAL_H_

#include <compare>

#include <numeric>
#include <iostream>

#include "src/type_definitions.h"

class Rational {
 public:
    // Constructors
    // TODO(padril): declare explicit and do conversions in operator_generator
    Rational(set_type::integer p = 0, set_type::integer q = 1);
    ~Rational();


    // Public Methods
    set_type::integer numerator();
    set_type::integer denominator();
    void set(set_type::integer p = 0, set_type::integer q = 1);


    // Conversion
    explicit operator set_type::integer() const;
    explicit operator set_type::real() const;


    // Operators
    friend Rational operator+(const Rational& x);
    friend Rational operator-(const Rational& x);
    friend Rational operator+(const Rational& x, const Rational& y);
    friend Rational operator-(const Rational& x, const Rational& y);
    friend Rational operator*(const Rational& x, const Rational& y);
    friend Rational operator/(const Rational& x, const Rational& y);

    auto operator<=>(const Rational& x) const {
        return set_type::real(*this) - set_type::real(x);
    }

    friend std::wostream& operator<<(std::wostream& out, const Rational& x);


 private:
    // Attributes
    set_type::integer num;
    set_type::integer den;
};


#endif  // SRC_TYPES_RATIONAL_H_
