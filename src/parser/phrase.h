// Copyright 2023 Leo James Peckham

#ifndef SRC_PARSER_PHRASE_H_
#define SRC_PARSER_PHRASE_H_


#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <optional>

#include "src/parser/tokens.h"
#include "src/types/types.h"

// TODO(padril): move node into a .h .cpp thing
struct Node {
    Token token;
    Literal value;  // use optional here in the future
    Node* left = nullptr;
    Node* right = nullptr;

    int size() {
        int count = 1;
        if (left != nullptr) {
            count += left->size();
        }
        if (right != nullptr) {
            count += right->size();
        }
        return count;
    }

    struct Screen {
        std::vector<std::wstring> screen;
        size_t mid;
    };

    void pad(Screen* screen, size_t height) {
        size_t w = screen->screen[0].size();
        size_t h = screen->screen.size();
        for (int i = 0; i < height - h; ++i) {
            screen->screen.push_back(std::wstring(w, ' '));
        }
    }

    Screen display() {
        Screen left_block, right_block;
        std::wstring repr;
        repr = token_to_string(token);
        if (left == nullptr && right == nullptr) {
            return { {repr}, repr.size() / 2 };
        }
        else if (left == nullptr && right != nullptr) {
            Screen m = right->display();
            size_t mh = m.screen.size(); size_t mw = m.screen[0].size();
            size_t maxw = std::max(repr.size(), mw);

            std::vector<std::wstring> ret(mh + 2);

            ret[0] += std::wstring(maxw - mw, L' ') + repr;
            ret[1] += std::wstring(maxw - mw, L' ')
                + L'│' + std::wstring(repr.size() - 1, L' ');
            for (int i = 0; i < mh; ++i) {
                ret[i + 2] += m.screen[i];
            }

            return { ret, maxw - mw };
        }
        else if (left != nullptr && right != nullptr) {
            Screen l = left->display();
            Screen r = right->display();
            size_t lh = l.screen.size(); size_t lw = l.screen[0].size();
            size_t rh = r.screen.size(); size_t rw = r.screen[0].size();
            size_t mh = std::max(lh, rh); size_t mw = std::max(lw, rw);

            // extra 2 are the header
            std::vector<std::wstring> ret(mh + 2);

            // left
            ret[0] += std::wstring(lw, L' ');
            ret[1] += std::wstring(l.mid, L' ') + L'┌'
                + std::wstring(lw - l.mid - 1, L'─');
            pad(&l, mh);
            for (int i = 0; i < mh; ++i) {
                ret[i + 2] += l.screen[i];
            }

            // middle
            ret[0] += repr;
            ret[1] += L'┴' + std::wstring(repr.size() - 1, L'─');
            for (int i = 0; i < mh; ++i) {
                ret[i + 2] += std::wstring(repr.size(), L' ');
            }

            // right
            ret[0] += std::wstring(rw, L' ');
            ret[1] += std::wstring(r.mid, L'─') + L'┐'
                + std::wstring(rw - r.mid - 1, L' ');
            pad(&r, mh);
            for (int i = 0; i < mh; ++i) {
                ret[i + 2] += r.screen[i];
            }


            return {ret, lw};
        }
        else if (left != nullptr && right == nullptr) {
            // ERROR
        }
    }

    friend std::wostream& operator<<(std::wostream& out, Node* node) {
        for (std::wstring line : node->display().screen) {
            out << line << '\n';
        }
        return out;
    }
    // Variant variant;

    // TODO(padril): a descructor that calls child destructors
};


struct Phrase {
    std::list<Node*> nodes;

    Node* tree();

    // TODO(padril): evaluate needs to be updated for trees
    Literal evaluate(bool terminating = false);
};


#endif
