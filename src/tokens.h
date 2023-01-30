#ifndef SRC_TOKENS_H_
#define SRC_TOKENS_H_

#include <string>
#include <variant>
#include <numeric>
#include "src/set.h"

struct nulltype {};

// TODO: move to it's own class
class rational {
public:
    int numerator = 0;
    int denominator = 1;
    rational(int p, int q) {
        numerator = p; denominator = q;
        this->simplify();
    }
    ~rational() {}
    explicit operator float() { return float(numerator) / denominator; }
    explicit operator int() { return numerator; }

    void simplify() {
        int gcd = std::gcd(numerator, denominator);
        numerator /= gcd;
        denominator /= gcd;
    }
};

inline rational operator*(rational x, rational y) {
    return { x.numerator * y.numerator, x.denominator * y.denominator };
}
inline rational operator*(int x, rational y) {
    return { y.numerator * x, y.denominator };
}
inline rational operator*(rational x, int y) { return y * x; }
inline rational operator+(int x, rational y) {
    return { y.numerator + x * y.denominator, y.denominator };
}
inline rational operator+(rational x, int y) { return y + x; }
inline rational operator+(rational x, rational y) {
    return { x.numerator * y.denominator + y.numerator * x.denominator,
             x.denominator * y.denominator };
}
inline rational operator+(rational x) { return x; }
inline std::ostream& operator<<(std::ostream& out, rational x) {
    out << x.numerator << '/' << x.denominator;
    return out;
}
inline rational operator/(int x, rational y) {
    return { x * y.denominator, y.numerator };
}
inline rational operator/(rational x, int y) {
    return { x.numerator, x.denominator * y };
}
inline rational operator/(rational x, rational y) {
    return { x.numerator * y.denominator, y.numerator * x.denominator };
}


typedef std::variant<nulltype, int, rational, float, std::string> Literal;


enum class Type : size_t {
    LITERAL_NULL,
    LITERAL_INT,
    LITERAL_RATIONAL,
    LITERAL_REAL,
    LITERAL_STRING,
};

enum class Token {
    END_PHRASE,

    BEGIN_PRIORITY,
    END_PRIORITY,

    LITERAL,

    POSITIVE,

    DYADS,  // admin token, used to determine monadic/dyadic
    // usage of operators in `parse`
    PLUS,
    TIMES,
    SLASH,
};

#endif // SRC_TOKENS_H_
