/**
 * The MIT License (MIT)
 * 
 * Copyright (c) 2016 Vikash Kesarwani
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

//==============================================================================
// Header files used in almost all files
//==============================================================================
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>


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
typedef int pos_t;

/** error code returned by functions, -ve error code indicates and error, 0 or +ve is successful */
typedef int cerror_t;


//==============================================================================
// Helper functions
//==============================================================================

extern int next_pow2(int n);
void swap_size(size_t *ptr1, size_t *ptr2);
void swap_ptr(uint8_t **ptr1, uint8_t **ptr2);

EXTERN_C_END

#endif /* end of include guard: CCOLLECTION_INTERNAL_H */
