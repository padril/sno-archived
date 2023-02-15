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
    Rational(SN_int p = 0, SN_int q = 1);
    ~Rational();


    // Public Methods
    SN_int numerator();
    SN_int denominator();
    void set(SN_int p = 0, SN_int q = 1);


    // Conversion
    explicit operator SN_int() const;
    explicit operator SN_real() const;


    // Operators
    friend Rational operator+(const Rational& x);
    friend Rational operator-(const Rational& x);
    friend Rational operator+(const Rational& x, const Rational& y);
    friend Rational operator-(const Rational& x, const Rational& y);
    friend Rational operator*(const Rational& x, const Rational& y);
    friend Rational operator/(const Rational& x, const Rational& y);

    auto operator<=>(const Rational& x) const {
        return SN_real(*this) - SN_real(x);
    }

    friend std::wostream& operator<<(std::wostream& out, const Rational& x);


 private:
    // Attributes
    SN_int num;
    SN_int den;
};


#endif  // SRC_TYPES_RATIONAL_H_
