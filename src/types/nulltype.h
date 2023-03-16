
// Copyright 2023 Leo Peckham


#ifndef SNO_SRC_TYPES_NULLTYPE_H_
#define SNO_SRC_TYPES_NULLTYPE_H_


#include <iostream>


namespace sno {




struct Null {
    friend std::wostream& operator<<(std::wostream& out, Null) {
        out << L"NULL" << L"\n";
        return out;
    }
};




}  // namespace sno

#endif  // SNO_SRC_TYPES_NULLTYPE_H_
