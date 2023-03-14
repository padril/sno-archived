// Copyright 2023 Leo James Peckahm

#ifndef SRC_TYPES_SET_H_
#define SRC_TYPES_SET_H_


#include "src/type_definitions.h"

#include <iostream>
#include <deque>
#include <algorithm>


// TODO(padril): I have a feeling most of the different Set types could
//               be an actual use of, and I hate to say this, inheritance.
template <class T>
class TemplateSet {
 public:
    // Constants
    static const size_t MAX_SIZE = 64;
    static const size_t MAX_DISPLAY = 15;
    static const bool DISPLAY_AROUND_ZERO = true;
    static const __int64 MAX_ATTEMPTS = 1000000;
    static inline const double DEFAULT_GRAIN = 0.001;
    static inline const bool NULL_RULE(T x) { return false; };


    // Static Set
    TemplateSet()
        : rule(NULL_RULE),
          left(0),
          right(std::is_same<T, int>::value ? -1 : -DEFAULT_GRAIN) {}
    TemplateSet(std::initializer_list<T> values)
        : elements(truncate(values).elements) {}
    explicit TemplateSet(std::deque<T> values)
        : elements(truncate(values).elements) {}
    ~TemplateSet() {}


    // Dynamic Set
    explicit TemplateSet(bool (*mask)(T x), int attempts = MAX_ATTEMPTS,
                 float grain = DEFAULT_GRAIN) {
        if (std::is_same<T, int>::value) grain = 1;

        rule = mask;
        left = 0;
        right = -grain;  // start at negative so that right's first check is 0

        int size = 0;
        int attempt_number = 0;

        auto search_left = [&]() {
            left -= grain;
            if (rule(left)) {
                elements.push_front(left);
                size++;
            }
            return size >= MAX_SIZE;
        };
        auto search_right = [&]() {
            right += grain;
            if (rule(right)) {
                elements.push_back(right);
                size++;
            }
            return size >= MAX_SIZE;
        };

        while (attempt_number <= MAX_ATTEMPTS) {
            if (search_right()) break;
            if (search_left()) break;
            attempt_number++;
        }
    }


    // Operators
    template <class S>
    TemplateSet<S>& operator=(const TemplateSet<S>& other) {
        if (this == &other) {  // guard self assignment
            return *this;
        }

        elements = other.elements;
        rule = other.rule;
        left = other.left; right = other.right;

        return *this;
    }

    friend std::wostream& operator<<(std::wostream& os, const TemplateSet<T>& S) {
        auto truncated = truncate(S.elements, MAX_DISPLAY, DISPLAY_AROUND_ZERO);
        os << '{';
        if (truncated.on_left) os << "...";
        for (T i : truncated.elements) {
            os << i << ", ";
        }
        // making use of \b to remove the final ", "
        if (truncated.elements.size() > 0) os << "\b\b";
        if (truncated.on_right) os << "...";
        os << "} ";
        return os;
    }


 private:
    // Attributes
    std::deque<T> elements;  // containter
    bool (*rule)(T x);  // rule for generating new elements
    T left;  // how far left we've checked
    T right;  // how far right we've checked


    // Private Methods
    // returns a custom struct with "Set elements, bool truncated"
    // allowing us to easily prune our set for printing or other
    // TODO(padril): change from 'around_zero' to centered,
    //              and give an option to center at a specific point
    //              this will be useful when overloading operators
    static auto truncate(std::deque<T> values, size_t new_size = MAX_SIZE,
                         bool around_zero = false) {
        struct returnValues {
            std::deque<T> elements;
            bool on_left;
            bool on_right;
        };
        // return returnValues{ values, false, false };

        size_t size = values.size();
        auto begin = values.begin();
        auto end = values.end();

        if (size > new_size) {
            if (around_zero) {
                // since values is sorted, finding the min of abs(values)
                // means finding where it changes to positive
                int min_i = 1;
                while (static_cast<set_type::real>(values[min_i]) < 0) min_i++;
                min_i = -values[min_i - 1] < values[min_i] ? min_i - 1 : min_i;
                __int64 end_i = end - begin;
                int l = min_i - 1, r = min_i + 1;

                T min = values[min_i];
                int found = 1;
                std::deque<T> new_values = { min };

                // search radially away from the min_i to find values to print
                while (found < new_size) {
                    if (l < 0) {
                        for (int i = r; i < found; i++) {
                        new_values.push_back(values[i]);
                        }
                        return returnValues { new_values, true, false };
                    } else if (r > end_i) {
                        for (int i = l; i >= 0; i--) {
                        new_values.push_back(values[i]);
                        }
                        return returnValues { new_values, false, true };
                    } else if ((min - values[l]) < (values[r] - min)) {
                        new_values.push_front(values[l]);
                        l--; found++;
                    } else {
                        new_values.push_back(values[r]);
                        r++; found++;
                    }
                }
                return returnValues{ new_values, true, true };
            } else {
                size_t remove = size - new_size;
                size_t remove_l = remove / 2;
                size_t remove_r = remove - remove_l;
                values.erase(begin, begin + remove_l);
                values.erase(end - remove_r, end);

                return returnValues{ values, true, true };
            }
        } else {
            return returnValues{ values, false, false };
        }
    }
};


#endif  // SRC_TYPES_SET_H_
