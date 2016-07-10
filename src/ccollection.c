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
