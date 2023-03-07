// Copyright 2023 Leo Peckham


#ifndef SRC_OPERATORS_OPERATORS_H_
#define SRC_OPERATORS_OPERATORS_H_


#include <iostream>
#include "src/lexer/tokens.h"
#include "src/types/types.h"
#include "src/type_definitions.h"
#include "src/lexer/sentence.h"
#include "src/parser/phrase.h"


Literal OPERATOR_REPRESENTATION(Literal l, Literal r);

Literal OPERATOR_PRINT(Literal l, Literal r);

Literal OPERATOR_DEBUG_PRINT(Literal l, Literal r);

Literal OPERATOR_PLUS(Literal l, Literal r);

Literal OPERATOR_MINUS(Literal l, Literal r);

Literal OPERATOR_TIMES(Literal l, Literal r);

Literal OPERATOR_SLASH(Literal l, Literal r);


#endif  // SRC_OPERATORS_OPERATORS_H_
