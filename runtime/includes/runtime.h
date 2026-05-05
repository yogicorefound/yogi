//
// Created by Brayhan De Aza on 5/4/26.
//

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct {
        int64_t len;
        char *data;
    } String;

    String *create_string(const char *data, int64_t len);

#ifdef __cplusplus
}
#endif