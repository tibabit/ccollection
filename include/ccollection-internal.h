#ifndef CCOLLECTION_INTERNAL_H

#define CCOLLECTION_INTERNAL_H

//==============================================================================
// c++ portability, Just in case :P
//==============================================================================
#ifdef __cplusplus
    #define EXTERN_C_BEGIN  extern "C" {
    #define EXTERN_C_END    }
#else
    #define EXTERN_C_BEGIN
    #define EXTERN_C_END
#endif

//==============================================================================
// Debugging macros
//==============================================================================
#ifdef _DEBUG_
    #define DEBUG(frmt, ...)    fprintf(stdout, frmt, ##__VA_ARGS__)
#else
    #define DEBUG(frmt, ...)
#endif

//==============================================================================
// macro functions
//==============================================================================
#define MAX(a,b)    ((a) > (b) ? (a) : (b))
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#define NEXT_POW2(n)    \
    n--; \
    n |= n >> 1; \
    n |= n >> 2; \
    n |= n >> 4; \
    n |= n >> 8; \
    n |= n >> 16; \
    n++;

//==============================================================================
// Header files used in almost all files
//==============================================================================
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>


EXTERN_C_BEGIN

//==============================================================================
// Error codes set by various functions
//==============================================================================
#define EOFFSET             1024
#define EBADELEMSIZE        (EOFFSET + 1)           /** Invalid element size */
#define EBADPOINTER         (EOFFSET + 2)           /** pointer points to NULL */
#define EOUTOFRANGE         (EOFFSET + 3)           /** Index was out of range */

#define ERROR_NONE          0                       /** No error */
#define ERROR_FAILED        -1                      /** function did not execute successfully */

//==============================================================================
// Assertion macros
//==============================================================================
// set errno and return
#define ASSERT_E(expr, err, ret) \
    if (!(expr)) {               \
        errno = err;             \
        return ret;              \
    }
// just return, do not set error number
#define ASSERT(expr, ...)        \
    if (!(expr)) {               \
        return __VA_ARGS__;      \
    }


//==============================================================================
// Memory allocation / de-allocation related macros
//==============================================================================
#define ccollection_calloc(size)            calloc(1, size);
#define ccollection_realloc(ptr, size)      realloc((void*)(ptr), size);

#define ccollection_free(ptr)  \
    if(((void*)(ptr)) != NULL) \
        free(ptr);

#define ccollection_copy(dst, src, size)    memcpy((void*)(dst), (void*)(src), size)

//==============================================================================
// Aliases / typedefs
//==============================================================================
/** opaque item type used in all containers */
typedef void item_t;

/** error code returned by functions, -ve error code indicates and error, 0 or +ve is successful */
typedef int cerror_t;


EXTERN_C_END

#endif /* end of include guard: CCOLLECTION_INTERNAL_H */
