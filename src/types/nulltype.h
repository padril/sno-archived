#ifndef SRC_TYPES_NULLTYPE_H_
#define SRC_TYPES_NULLTYPE_H_

#include <iostream>

namespace sno {

    struct Null {
        friend std::wostream& operator<<(std::wostream& out, Null) {
            out << L"NULL" << L"\n";
            return out;
        }
    };

}  // namespace sno

#endif  // SRC_TYPES_NULLTYPE_H_
