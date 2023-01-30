#ifndef SRC_OPERATORS_H_
#define SRC_OPERATORS_H_

#include <iostream>
#include "src/tokens.h"

struct OPERATOR_PRINT_PACKAGE {
	Literal operator()(auto, auto) {
		return nulltype();  // ERROR
	}
	Literal operator()(nulltype , nulltype arg) {
		std::cout << "NULL\n";return arg;
	}
	Literal operator()(nulltype , auto arg) {
		std::cout << arg << '\n';return arg;
	}
};

Literal OPERATOR_PRINT(Literal l, Literal r) {
	return std::visit(OPERATOR_PRINT_PACKAGE(), l, r);
}
struct OPERATOR_PLUS_PACKAGE {
	Literal operator()(auto, auto) {
		return nulltype();  // ERROR
	}
	Literal operator()(nulltype , int x) {
		return +x;
	}
	Literal operator()(nulltype , rational x) {
		return +x;
	}
	Literal operator()(nulltype , float x) {
		return +x;
	}
	Literal operator()(int x, int y) {
		return x + y;
	}
	Literal operator()(int x, rational y) {
		return x + y;
	}
	Literal operator()(int x, float y) {
		return x + y;
	}
	Literal operator()(rational x, int y) {
		return x + y;
	}
	Literal operator()(rational x, rational y) {
		return x + y;
	}
	Literal operator()(rational x, float y) {
		return x + y;
	}
	Literal operator()(float x, int y) {
		return x + y;
	}
	Literal operator()(float x, rational y) {
		return x + y;
	}
	Literal operator()(float x, float y) {
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
		return nulltype();  // ERROR
	}
	Literal operator()(int x, int y) {
		return x * y;
	}
	Literal operator()(int x, rational y) {
		return x * y;
	}
	Literal operator()(int x, float y) {
		return x * y;
	}
	Literal operator()(rational x, int y) {
		return x * y;
	}
	Literal operator()(rational x, rational y) {
		return x * y;
	}
	Literal operator()(rational x, float y) {
		return x * y;
	}
	Literal operator()(float x, int y) {
		return x * y;
	}
	Literal operator()(float x, rational y) {
		return x * y;
	}
	Literal operator()(float x, float y) {
		return x * y;
	}
};

Literal OPERATOR_TIMES(Literal l, Literal r) {
	return std::visit(OPERATOR_TIMES_PACKAGE(), l, r);
}
struct OPERATOR_SLASH_PACKAGE {
	Literal operator()(auto, auto) {
		return nulltype();  // ERROR
	}
	Literal operator()(int x, int y) {
		return rational{x, y};
	}
	Literal operator()(int x, rational y) {
		return x / y;
	}
	Literal operator()(int x, float y) {
		return x / y;
	}
	Literal operator()(rational x, int y) {
		return x / y;
	}
	Literal operator()(rational x, rational y) {
		return x / y;
	}
	Literal operator()(rational x, float y) {
		return x / y;
	}
	Literal operator()(float x, int y) {
		return x / y;
	}
	Literal operator()(float x, rational y) {
		return x / y;
	}
	Literal operator()(float x, float y) {
		return x / y;
	}
};

Literal OPERATOR_SLASH(Literal l, Literal r) {
	return std::visit(OPERATOR_SLASH_PACKAGE(), l, r);
}
#endif  // SRC_OPERATORS_H_