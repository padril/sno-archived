#ifndef SRC_TYPES_LITERAL_H_
#define SRC_TYPES_LITERAL_H_

#include <variant>
#include <string>

#include "src/type_definitions.h"
#include "nulltype.h"
#include "rational.h"

enum class Type {
    LITERAL_NULL,
    LITERAL_INT,
    LITERAL_BOOL,
    LITERAL_RATIONAL,
    LITERAL_REAL,
    LITERAL_STRING,
};

typedef std::variant<
    Null, 
    TYPE_BOOL, 
    TYPE_INT,
    Rational, 
    TYPE_REAL, 
    std::string
    > Literal;

#endif  // SRC_TYPES_LITERAL_H_
