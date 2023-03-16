
// Copyright 2023 Leo Peckham


#include <algorithm>
#include <vector>
#include <string>

#include "interpreter/parser/tree.h"
#include "interface/output/screen.h"


namespace sno {




// ===
// Constructors
// ===

Screen::Screen(const Tree& tree) {
    mid = 0;
    std::wstring repr;
    repr = token_id_to_string(tree.root->id);

    if (tree.left == nullptr && tree.right == nullptr) {
        display = {repr};
        mid = repr.size() / 2;
    } else if (tree.left == nullptr && tree.right != nullptr) {
        Screen m(*tree.right);
        size_t mh = m.display.size(); size_t mw = m.display[0].size();
        size_t maxw = std::max(repr.size(), mw);

        std::vector<std::wstring> ret(mh + 2);

        ret[0] += std::wstring(maxw - mw, L' ') + repr;
        ret[1] += std::wstring(maxw - mw, L' ')
            + L'│' + std::wstring(repr.size() - 1, L' ');
        for (size_t i = 0; i < mh; ++i) {
            ret[i + 2] += m.display[i];
        }

        display = ret;
        mid = maxw - mw;
    } else if (tree.left != nullptr && tree.right != nullptr) {
        Screen l(*tree.left);
        Screen r(*tree.right);
        size_t lh = l.display.size(); size_t lw = l.display[0].size();
        size_t rh = r.display.size(); size_t rw = r.display[0].size();
        size_t mh = std::max(lh, rh); size_t mw = std::max(lw, rw);

        // extra 2 are the header
        std::vector<std::wstring> ret(mh + 2);

        // left
        ret[0] += std::wstring(lw, L' ');
        ret[1] += std::wstring(l.mid, L' ') + L'┌'
            + std::wstring(lw - l.mid - 1, L'─');
        l.pad(0, mh);
        for (size_t i = 0; i < mh; ++i) {
            ret[i + 2] += l.display[i];
        }

        // middle
        ret[0] += repr;
        ret[1] += L'┴' + std::wstring(repr.size() - 1, L'─');
        for (size_t i = 0; i < mh; ++i) {
            ret[i + 2] += std::wstring(repr.size(), L' ');
        }

        // right
        ret[0] += std::wstring(rw, L' ');
        ret[1] += std::wstring(r.mid, L'─') + L'┐'
            + std::wstring(rw - r.mid - 1, L' ');
        r.pad(0, mh);
        for (size_t i = 0; i < mh; ++i) {
            ret[i + 2] += r.display[i];
        }


        display = ret;
        mid = lw;
    } else if (tree.left != nullptr && tree.right == nullptr) {
        // ERROR
    }
}




// ===
// Member functions
// ===

void Screen::pad(size_t width, size_t height) {
    size_t w = display[0].size();
    size_t h = display.size();

    for (std::wstring& line : display) {
        line.append(std::wstring(width, L' '));
    }
    for (int i = 0; i < height - h; ++i) {
        display.push_back(std::wstring(w + width, ' '));
    }
}




// ===
// Operators
// ===

std::wostream& operator<<(std::wostream& out, Screen screen) {
    for (std::wstring_view line : screen.display) {
        out << line;
    }
    return out;
}




}  // namespace sno
