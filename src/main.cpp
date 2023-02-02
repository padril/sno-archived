// Copyright 2023 Leo James Peckham

#include "src/phrase.h"

int main() {
    Phrase p0("3/2/4.1");
    // TODO: bug because literal_list is static,
    // change literal_list into a passed by reference
    // pos held thing like token_list, or something?
    Phrase p1("3/2/4");
}
