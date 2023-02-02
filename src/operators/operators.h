#ifndef SRC_OPERATORS_OPERATORS_H_
#define SRC_OPERATORS_OPERATORS_H_

#include <iostream>
#include "src/tokens.h"
#include "src/types/types.h"
#include "src/type_definitions.h"

struct OPERATOR_PRINT_PACKAGE {
	Literal operator()(auto, auto) {
		return Null();  // ERROR
	}
	Literal operator()(Null , Null arg) {
		std::cout << "NULL\n";
		return arg;
	}
	Literal operator()(Null , auto arg) {
		std::cout << arg << '\n';
		return arg;
	}
};
Literal OPERATOR_PRINT(Literal l, Literal r) {
	return std::visit(OPERATOR_PRINT_PACKAGE(), l, r);
}


struct OPERATOR_PLUS_PACKAGE {
	Literal operator()(auto, auto) {
		return Null();  // ERROR
	}
	Literal operator()(Null , TYPE_INT x) {
		return +x;
	}
	Literal operator()(Null , Rational x) {
		return +x;
	}
	Literal operator()(Null , TYPE_REAL x) {
		return +x;
	}
	Literal operator()(TYPE_INT x, TYPE_INT y) {
		return x + y;
	}
	Literal operator()(TYPE_INT x, Rational y) {
		return x + y;
	}
	Literal operator()(TYPE_INT x, TYPE_REAL y) {
		return x + y;
	}
	Literal operator()(Rational x, TYPE_INT y) {
		return x + y;
	}
	Literal operator()(Rational x, Rational y) {
		return x + y;
	}
	Literal operator()(Rational x, TYPE_REAL y) {
		return x + y;
	}
	Literal operator()(TYPE_REAL x, TYPE_INT y) {
		return x + y;
	}
	Literal operator()(TYPE_REAL x, Rational y) {
		return x + y;
	}
	Literal operator()(TYPE_REAL x, TYPE_REAL y) {
		return x + y;
	}
	Literal operator()(std::string x, std::string y) {
		return x + y;
	}
};
Literal OPERATOR_PLUS(Literal l, Literal r) {
	return std::visit(OPERATOR_PLUS_PACKAGE(), l, r);
}


struct OPERATOR_TIMES_PACKAGE {
	Literal operator()(auto, auto) {
		return Null();  // ERROR
	}
	Literal operator()(TYPE_INT x, TYPE_INT y) {
		return x * y;
	}
	Literal operator()(TYPE_INT x, Rational y) {
		return x * y;
	}
	Literal operator()(TYPE_INT x, TYPE_REAL y) {
		return x * y;
	}
	Literal operator()(Rational x, TYPE_INT y) {
		return x * y;
	}
	Literal operator()(Rational x, Rational y) {
		return x * y;
	}
	Literal operator()(Rational x, TYPE_REAL y) {
		return x * y;
	}
	Literal operator()(TYPE_REAL x, TYPE_INT y) {
		return x * y;
	}
	Literal operator()(TYPE_REAL x, Rational y) {
		return x * y;
	}
	Literal operator()(TYPE_REAL x, TYPE_REAL y) {
		return x * y;
	}
};
Literal OPERATOR_TIMES(Literal l, Literal r) {
	return std::visit(OPERATOR_TIMES_PACKAGE(), l, r);
}


struct OPERATOR_SLASH_PACKAGE {
	Literal operator()(auto, auto) {
		return Null();  // ERROR
	}
	Literal operator()(TYPE_INT x, TYPE_INT y) {
		return Rational(x, y);
	}
	Literal operator()(TYPE_INT x, Rational y) {
		return x / y;
	}
	Literal operator()(TYPE_INT x, TYPE_REAL y) {
		return x / y;
	}
	Literal operator()(Rational x, TYPE_INT y) {
		return x / y;
	}
	Literal operator()(Rational x, Rational y) {
		return x / y;
	}
	Literal operator()(Rational x, TYPE_REAL y) {
		return x / y;
	}
	Literal operator()(TYPE_REAL x, TYPE_INT y) {
		return x / y;
	}
	Literal operator()(TYPE_REAL x, Rational y) {
		return x / y;
	}
	Literal operator()(TYPE_REAL x, TYPE_REAL y) {
		return x / y;
	}
};
Literal OPERATOR_SLASH(Literal l, Literal r) {
	return std::visit(OPERATOR_SLASH_PACKAGE(), l, r);
}


#endif  // SRC_OPERATORS_OPERATORS_H_