// Copyright 2023 Leo Peckham


#include "operators/operators.h"


#include <iostream>
#include "interpreter/lexer/tokens.h"
#include "types/types.h"
#include "types/type_definitions.h"


namespace sno {




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


struct OPERATOR_PLUS_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(Null, integer_type x) {
		return +x;
	}
	
	Literal operator()(Null, Rational x) {
		return +x;
	}
	
	Literal operator()(Null, real_type x) {
		return +x;
	}
	
	Literal operator()(integer_type x, integer_type y) {
		return x + y;
	}
	
	Literal operator()(integer_type x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x + y;
	}
	
	Literal operator()(integer_type x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x + y;
	}
	
	Literal operator()(Rational x, integer_type y_) {
		Rational y = static_cast<Rational>(y_);
		return x + y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x + y;
	}
	
	Literal operator()(Rational x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x + y;
	}
	
	Literal operator()(real_type x, integer_type y_) {
		real_type y = static_cast<real_type>(y_);
		return x + y;
	}
	
	Literal operator()(real_type x, Rational y_) {
		real_type y = static_cast<real_type>(y_);
		return x + y;
	}
	
	Literal operator()(real_type x, real_type y) {
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
	Literal operator()(Null, integer_type x) {
		return -x;
	}
	
	Literal operator()(Null, Rational x) {
		return -x;
	}
	
	Literal operator()(Null, real_type x) {
		return -x;
	}
	
	Literal operator()(integer_type x, integer_type y) {
		return x - y;
	}
	
	Literal operator()(integer_type x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x - y;
	}
	
	Literal operator()(integer_type x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x - y;
	}
	
	Literal operator()(Rational x, integer_type y_) {
		Rational y = static_cast<Rational>(y_);
		return x - y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x - y;
	}
	
	Literal operator()(Rational x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x - y;
	}
	
	Literal operator()(real_type x, integer_type y_) {
		real_type y = static_cast<real_type>(y_);
		return x - y;
	}
	
	Literal operator()(real_type x, Rational y_) {
		real_type y = static_cast<real_type>(y_);
		return x - y;
	}
	
	Literal operator()(real_type x, real_type y) {
		return x - y;
	}
};

Literal OPERATOR_MINUS(Literal l, Literal r) {
	return std::visit(OPERATOR_MINUS_PACKAGE(), l, r);
}


struct OPERATOR_TIMES_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(integer_type x, integer_type y) {
		return x * y;
	}
	
	Literal operator()(integer_type x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x * y;
	}
	
	Literal operator()(integer_type x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x * y;
	}
	
	Literal operator()(Rational x, integer_type y_) {
		Rational y = static_cast<Rational>(y_);
		return x * y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x * y;
	}
	
	Literal operator()(Rational x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x * y;
	}
	
	Literal operator()(real_type x, integer_type y_) {
		real_type y = static_cast<real_type>(y_);
		return x * y;
	}
	
	Literal operator()(real_type x, Rational y_) {
		real_type y = static_cast<real_type>(y_);
		return x * y;
	}
	
	Literal operator()(real_type x, real_type y) {
		return x * y;
	}
};

Literal OPERATOR_TIMES(Literal l, Literal r) {
	return std::visit(OPERATOR_TIMES_PACKAGE(), l, r);
}


struct OPERATOR_SLASH_PACKAGE {
	Literal operator()(auto, auto) { return Null(); }  // Error
	Literal operator()(integer_type x, integer_type y) {
		return Rational{x, y};
	}
	
	Literal operator()(integer_type x_, Rational y) {
		Rational x = static_cast<Rational>(x_);
		return x / y;
	}
	
	Literal operator()(integer_type x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x / y;
	}
	
	Literal operator()(Rational x, integer_type y_) {
		Rational y = static_cast<Rational>(y_);
		return x / y;
	}
	
	Literal operator()(Rational x, Rational y) {
		return x / y;
	}
	
	Literal operator()(Rational x_, real_type y) {
		real_type x = static_cast<real_type>(x_);
		return x / y;
	}
	
	Literal operator()(real_type x, integer_type y_) {
		real_type y = static_cast<real_type>(y_);
		return x / y;
	}
	
	Literal operator()(real_type x, Rational y_) {
		real_type y = static_cast<real_type>(y_);
		return x / y;
	}
	
	Literal operator()(real_type x, real_type y) {
		return x / y;
	}
};

Literal OPERATOR_SLASH(Literal l, Literal r) {
	return std::visit(OPERATOR_SLASH_PACKAGE(), l, r);
}




}  // namespace sno
