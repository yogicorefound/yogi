//
// Created by Brayhan De Aza on 5/4/26.
//


#include <stdlib.h>
#include <string.h>
#include "runtime.h"
#include <iostream>


String* create_string(const char* data, int64_t len) {
    const auto s = static_cast<String *>(malloc(sizeof(String)));

    s->len = len;
    s->data = static_cast<char *>(malloc(len + 1));

    memcpy(s->data, data, len);
    s->data[len] = '\0';

    return s;
}
