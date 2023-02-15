#ifndef SRC_TYPES_NULLTYPE_H_
#define SRC_TYPES_NULLTYPE_H_

struct Null {
    friend std::wostream& operator<<(std::wostream& out, Null) {
        out << 'NULL' << '\n';
        return out;
    }
};

#endif  // SRC_TYPES_NULLTYPE_H_
