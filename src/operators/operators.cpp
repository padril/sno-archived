// Copyright 2023 Leo Peckham


#include "src\operators\operators.h"


struct OPERATOR_REPRESENTATION_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(Null, std::wstring arg) {
		std::wcout << L'"' + arg + L'"' + L'\n';
		return arg;
	}
	
	Literal operator()(Null, Set arg) {
		std::visit([](auto x) {std::wcout << x << '\n'; }, arg);
		return arg;
	}
	
	Literal operator()(Null, auto arg) {
		std::wcout << arg << '\n';
		return arg;
	}
};

Literal OPERATOR_REPRESENTATION(Literal l, Literal r) {
	return std::visit(OPERATOR_REPRESENTATION_PACKAGE(), l, r);
}


struct OPERATOR_PRINT_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(Null, Null arg) {
		std::wcout << '\n';
		return arg;
	}
	
	Literal operator()(Null, Set arg) {
		std::visit([](auto x) {std::wcout << x << '\n'; }, arg);
		return arg;
	}
	
	Literal operator()(Null, auto arg) {
		std::wcout << arg << '\n';
		return arg;
	}
};

Literal OPERATOR_PRINT(Literal l, Literal r) {
	return std::visit(OPERATOR_PRINT_PACKAGE(), l, r);
}


struct OPERATOR_DEBUG_PRINT_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(Null, std::wstring arg) {
		int t = 0;
		Phrase p = Sentence::parse(arg, &t);
		std::wcout << p.tree();
		return arg;
	}
};

Literal OPERATOR_DEBUG_PRINT(Literal l, Literal r) {
	return std::visit(OPERATOR_DEBUG_PRINT_PACKAGE(), l, r);
}


struct OPERATOR_PLUS_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(Null, SN_int x) {
		return +x;
	}
	
	Literal operator()(Null, Rational x) {
		return +x;
	}
	
	Literal operator()(Null, SN_real x) {
		return +x;
	}
	
	Literal operator()(SN_int x, SN_int y) {
		return x + y;
	}
	
	Literal operator()(SN_int x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x + y;
	}
	
	Literal operator()(SN_int x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x + y;
	}
	
	Literal operator()(Rational x, SN_int y_) {
		Rational y = static_cast<Rational>(y_);
		return x + y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x + y;
	}
	
	Literal operator()(Rational x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x + y;
	}
	
	Literal operator()(SN_real x, SN_int y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x + y;
	}
	
	Literal operator()(SN_real x, Rational y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x + y;
	}
	
	Literal operator()(SN_real x, SN_real y) {
		return x + y;
	}
	
	Literal operator()(std::wstring x, std::wstring y) {
		return x + y;
	}
};

Literal OPERATOR_PLUS(Literal l, Literal r) {
	return std::visit(OPERATOR_PLUS_PACKAGE(), l, r);
}


struct OPERATOR_MINUS_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(Null, SN_int x) {
		return -x;
	}
	
	Literal operator()(Null, Rational x) {
		return -x;
	}
	
	Literal operator()(Null, SN_real x) {
		return -x;
	}
	
	Literal operator()(SN_int x, SN_int y) {
		return x - y;
	}
	
	Literal operator()(SN_int x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x - y;
	}
	
	Literal operator()(SN_int x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x - y;
	}
	
	Literal operator()(Rational x, SN_int y_) {
		Rational y = static_cast<Rational>(y_);
		return x - y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x - y;
	}
	
	Literal operator()(Rational x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x - y;
	}
	
	Literal operator()(SN_real x, SN_int y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x - y;
	}
	
	Literal operator()(SN_real x, Rational y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x - y;
	}
	
	Literal operator()(SN_real x, SN_real y) {
		return x - y;
	}
};

Literal OPERATOR_MINUS(Literal l, Literal r) {
	return std::visit(OPERATOR_MINUS_PACKAGE(), l, r);
}


struct OPERATOR_TIMES_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(SN_int x, SN_int y) {
		return x * y;
	}
	
	Literal operator()(SN_int x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x * y;
	}
	
	Literal operator()(SN_int x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x * y;
	}
	
	Literal operator()(Rational x, SN_int y_) {
		Rational y = static_cast<Rational>(y_);
		return x * y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x * y;
	}
	
	Literal operator()(Rational x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x * y;
	}
	
	Literal operator()(SN_real x, SN_int y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x * y;
	}
	
	Literal operator()(SN_real x, Rational y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x * y;
	}
	
	Literal operator()(SN_real x, SN_real y) {
		return x * y;
	}
};

Literal OPERATOR_TIMES(Literal l, Literal r) {
	return std::visit(OPERATOR_TIMES_PACKAGE(), l, r);
}


struct OPERATOR_SLASH_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(SN_int x, SN_int y) {
		return Rational{x, y};
	}
	
	Literal operator()(SN_int x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x / y;
	}
	
	Literal operator()(SN_int x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x / y;
	}
	
	Literal operator()(Rational x, SN_int y_) {
		Rational y = static_cast<Rational>(y_);
		return x / y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x / y;
	}
	
	Literal operator()(Rational x_, SN_real y) {
		SN_real x = static_cast<SN_real>(x_);
		return x / y;
	}
	
	Literal operator()(SN_real x, SN_int y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x / y;
	}
	
	Literal operator()(SN_real x, Rational y_) {
		SN_real y = static_cast<SN_real>(y_);
		return x / y;
	}
	
	Literal operator()(SN_real x, SN_real y) {
		return x / y;
	}
};

Literal OPERATOR_SLASH(Literal l, Literal r) {
	return std::visit(OPERATOR_SLASH_PACKAGE(), l, r);
}

