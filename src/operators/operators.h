// Copyright 2023 Leo Peckham


#ifndef SRC_OPERATORS_OPERATORS_H_
#define SRC_OPERATORS_OPERATORS_H_


#include <iostream>
#include "src/interpreter/lexer/tokens.h"
#include "src/types/types.h"
#include "src/type_definitions.h"


namespace sno {

Literal OPERATOR_REPRESENTATION(Literal l, Literal r);

Literal OPERATOR_PRINT(Literal l, Literal r);

Literal OPERATOR_DEBUG_PRINT(Literal l, Literal r);

Literal OPERATOR_PLUS(Literal l, Literal r);

Literal OPERATOR_MINUS(Literal l, Literal r);

Literal OPERATOR_TIMES(Literal l, Literal r);

Literal OPERATOR_SLASH(Literal l, Literal r);


}  // namespace sno

#endif  // SRC_OPERATORS_OPERATORS_H_
