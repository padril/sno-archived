#ifndef SRC_TYPES_RATIONAL_H_
#define SRC_TYPES_RATIONAL_H_

#include "src/type_definitions.h"

// Gets around some stupid type deduction issues
#include <numeric>
#include <iostream>

class Rational {
public:
    Rational();
    Rational(TYPE_INT p, TYPE_INT q = 1);
    Rational(TYPE_REAL p, TYPE_INT q = 1) = delete;
    ~Rational();
   
    void set();
    void set(TYPE_INT x);
    void set(TYPE_INT p, TYPE_INT q);

    TYPE_INT numerator();
    TYPE_INT denominator();

    explicit operator TYPE_INT() const;
    explicit operator TYPE_REAL() const;

    friend Rational operator+(const Rational& x);
    friend Rational operator-(const Rational& x);

    // a mess, i hate this, but it will make everything happier
#define _ARITHMETIC_PERMUTATIONS(symbol)\
    friend Rational operator##symbol(const Rational& x, const Rational& y);\
    friend Rational operator##symbol(const Rational& x, TYPE_INT y);\
    friend Rational operator##symbol(TYPE_INT x, const Rational& y);\
    friend TYPE_REAL operator##symbol(const Rational& x, TYPE_REAL y);\
    friend TYPE_REAL operator##symbol(TYPE_REAL x, const Rational& y);

    _ARITHMETIC_PERMUTATIONS(+)
    _ARITHMETIC_PERMUTATIONS(-)
    _ARITHMETIC_PERMUTATIONS(*)
    _ARITHMETIC_PERMUTATIONS(/)

#undef _ARITHMETIC_PERMUTATIONS

    friend std::ostream& operator<<(std::ostream& out, const Rational& x);

private:
    TYPE_INT num;
    TYPE_INT den;
    void simplify();
};

#undef SELECTIVELY_ENABLE_TYPES

#endif  // SRC_TYPES_RATIONAL_H_