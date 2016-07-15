#include "include/ccollection.h"

#include <string.h>

const char* ccollection_strerror(int err)
{
    switch (err) {
        case EBADELEMSIZE:
            return "Invalid element size";
        case EBADPOINTER:
            return "Bad pointer";
        case EOUTOFRANGE:
            return "Index out of range";
        default:
            return strerror(err);
    }
}

inline int next_pow2(int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n++;

    return n;
}
