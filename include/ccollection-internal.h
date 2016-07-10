#ifndef CCOLLECTION_INTERNAL_H

#define CCOLLECTION_INTERNAL_H

#ifdef __cplusplus
    #define EXTERN_C_BEGIN  extern "C" {
    #define EXTERN_C_END    }
#else
    #define EXTERN_C_BEGIN
    #define EXTERN_C_END
#endif

#ifdef _DEBUG_
    #define DEBUG(frmt, ...)    fprintf(stdout, frmt, ##__VA_ARGS__)
#else
    #define DEBUG(frmt, ...)
#endif

/* common include files */
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

EXTERN_C_BEGIN


/** ccollection error codes */
#define EOFFSET             1024
#define EBADELEMSIZE        (EOFFSET + 1)           /** Invalid element size */
#define EBADPOINTER         (EOFFSET + 2)           /** pointer points to NULL */
#define EOUTOFRANGE         (EOFFSET + 3)           /** Index was out of range */


/** error checking */
#define ASSERT_E(expr, err, ret) \
    if (!(expr)) {               \
        errno = err;             \
        return ret;              \
    }

#define ASSERT(expr, ...)        \
    if (!(expr)) {               \
        return __VA_ARGS__;      \
    }


/** memroy management */

#define ccollection_calloc(size)            calloc(1, size);
#define ccollection_realloc(ptr, size)      realloc((void*)(ptr), size);

#define ccollection_free(ptr)  \
    if(((void*)(ptr)) != NULL) \
        free(ptr);


/** typedefs */

typedef void item_t;            /** opaque item type used in all containers */


EXTERN_C_END

#endif /* end of include guard: CCOLLECTION_INTERNAL_H */
