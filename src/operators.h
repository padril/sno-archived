#ifndef SRC_OPERATORS_H_
#define SRC_OPERATORS_H_

#include <iostream>
#include "src/tokens.h"

struct OPERATOR_PRINT_PACKAGE {
	auto operator()(auto, nulltype) { /* ERROR */ }
	auto operator()(nulltype _, nulltype arg) {
		std::cout << "NULL\n";
	}
	auto operator()(nulltype _, auto arg) {
		std::cout << arg << '\n';
	}
};

struct OPERATOR_PLUS_PACKAGE {
	auto operator()(auto, nulltype) { /* ERROR */ }
	auto operator()(nulltype _, int x) {
		return +x;
	}
	auto operator()(nulltype _, float x) {
		return +x;
	}
	auto operator()(int x, int y) {
		return x + y;
	}
	auto operator()(int x, float y) {
		return x + y;
	}
	auto operator()(float x, int y) {
		return x + y;
	}
	auto operator()(float x, float y) {
		return x + y;
	}
	auto operator()(std::string x, std::string y) {
		return x + y;
	}
};

struct OPERATOR_TIMES_PACKAGE {
	auto operator()(auto, nulltype) { /* ERROR */ }
	auto operator()(int x, int y) {
		return x * y;
	}
	auto operator()(int x, float y) {
		return x * y;
	}
	auto operator()(float x, int y) {
		return x * y;
	}
	auto operator()(float x, float y) {
		return x * y;
	}
};

#endif  // SRC_OPERATORS_H_