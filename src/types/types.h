#ifndef SRC_TYPES_LITERAL_H_
#define SRC_TYPES_LITERAL_H_

#include <variant>
#include <string>

#include "src/type_definitions.h"
#include "nulltype.h"
#include "rational.h"
#include "set.h"

enum class Type {
    LITERAL_NULL,
    LITERAL_BOOL,
    LITERAL_INT,
    LITERAL_RATIONAL,
    LITERAL_REAL,
    LITERAL_STRING,
    LITERAL_SET,
};

typedef std::variant<
    TemplateSet<TYPE_INT>,
    TemplateSet<Rational>,
    TemplateSet<TYPE_REAL>
> Set;

//std::ostream& operator<<(std::ostream& out, const Set& set) {
//    std::cout << "lmafo";
//    return out;
//}

typedef std::variant<
    Null, 
    TYPE_BOOL, 
    TYPE_INT,
    Rational, 
    TYPE_REAL, 
    std::string,
    Set
    > Literal;

#endif  // SRC_TYPES_LITERAL_H_
