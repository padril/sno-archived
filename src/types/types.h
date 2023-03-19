
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_TYPES_LITERAL_H_
#define SNO_SRC_TYPES_LITERAL_H_


#include <variant>
#include <string>

#include "types/type_definitions.h"
#include "types/nulltype.h"
#include "types/rational.h"
#include "types/set.h"


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


#endif  // SNO_SRC_TYPES_LITERAL_H_
