#ifndef SRC_TYPES_RATIONAL_H_
#define SRC_TYPES_RATIONAL_H_

#include "src/type_definitions.h"

#include <numeric>
#include <iostream>
#include <compare>


// TODO: all of this mess could probably be something in operator_generator.py
#define _ARITHMETIC_PERMUTATIONS(symbol)\
    friend Rational operator##symbol(const Rational& x, const Rational& y);\
    friend Rational operator##symbol(const Rational& x, SN_int            y);\
    friend Rational operator##symbol(SN_int            x, const Rational& y);\
    friend SN_real    operator##symbol(const Rational& x, SN_real           y);\
    friend SN_real    operator##symbol(SN_real           x, const Rational& y);\


class Rational {
public:
    // Constructors
    // TODO: declare explicit and do type conversions in operator_generator.py
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

    _ARITHMETIC_PERMUTATIONS(+)
    _ARITHMETIC_PERMUTATIONS(-)
    _ARITHMETIC_PERMUTATIONS(*)
    _ARITHMETIC_PERMUTATIONS(/)

    auto operator<=>(const Rational& x) const {
        return SN_real(*this) - SN_real(x);
    }

    friend std::ostream& operator<<(std::ostream& out, const Rational& x);


private:
    // Attributes
    SN_int num;
    SN_int den;
};


#undef _ARITHMETIC_PERMUTATIONS


#endif  // SRC_TYPES_RATIONAL_H_
