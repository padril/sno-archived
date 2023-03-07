// Copyright 2023 Leo Peckham


#ifndef SRC_TYPES_LITERAL_H_
#define SRC_TYPES_LITERAL_H_


#include <variant>
#include <string>

#include "src/type_definitions.h"
#include "nulltype.h"
#include "rational.h"
#include "set.h"


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
    TemplateSet<set_type::integer>,
    TemplateSet<Rational>,
    TemplateSet<set_type::real>
> Set;


typedef std::variant<
    Null, 
    set_type::boolean,
    set_type::integer,
    Rational, 
    set_type::real, 
    std::wstring,
    Set
    > Literal;


#endif  // SRC_TYPES_LITERAL_H_
