// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_OPERATORS_OPERATORS_H_
#define SNO_SRC_OPERATORS_OPERATORS_H_


#include "types/types.h"


namespace sno {




Literal OPERATOR_REPRESENTATION(Literal l, Literal r);

Literal OPERATOR_PRINT(Literal l, Literal r);

Literal OPERATOR_PLUS(Literal l, Literal r);

Literal OPERATOR_MINUS(Literal l, Literal r);

Literal OPERATOR_TIMES(Literal l, Literal r);

Literal OPERATOR_SLASH(Literal l, Literal r);




}  // namespace sno

#endif  // SNO_SRC_OPERATORS_OPERATORS_H_
