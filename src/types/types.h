// Copyright 2023 Leo Peckham


#ifndef SRC_TYPES_LITERAL_H_
#define SRC_TYPES_LITERAL_H_


#include <variant>
#include <string>

#include "src/type_definitions.h"
#include "nulltype.h"
#include "rational.h"
#include "set.h"

namespace sno {

enum class Type {
    null,
    error,
    boolean,
    integer,
    rational,
    real,
    string,
    set,
};


typedef std::variant<
    TemplateSet<integer_type>,
    TemplateSet<Rational>,
    TemplateSet<real_type>
> Set;


typedef std::variant<
    Null, 
    boolean_type,
    integer_type,
    Rational, 
    real_type, 
    std::wstring,
    Set
    > Literal;


}  // namespace sno

#endif  // SRC_TYPES_LITERAL_H_
