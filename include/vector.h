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

#ifndef VECTOR_H

#define VECTOR_H

#include "include/ccollection-internal.h"

EXTERN_C_BEGIN

//==============================================================================
// forward declarations
//==============================================================================

typedef struct vector_t vector_t;

//==============================================================================
// ctors and dtors
//==============================================================================

/**
 * returns a pointer to vector_t with initial capacity 0. Returns NULL of elem_size <=0 and sets errno.
 * call ccollection_strerror to get the error string;
 */
vector_t* vector_new(const size_t elem_size);
/**
 * destroy all elements and cleanup all elements
 */
cerror_t vector_destroy(vector_t* vector);


//==============================================================================
// Capacity
//==============================================================================

/**
 * increase capacity of vector to accommodate minimum number of elements supplied by count. Return true if successful.
 * Otherwise returns false.
 * If current capacity of the container is > count, nothing happens.
 * call ccollection_strerror to get the error string.
 */
cerror_t vector_reserve(vector_t* vector, const size_t count);
/**
 * get size of vector
 */
size_t vector_get_size(const vector_t* vector);
/**
 * get capacity of vector
 */
size_t vector_get_capacity(const vector_t* vector);
/**
 * check if vector is empty
 */
bool vector_is_empty(const vector_t* vector);


//==============================================================================
// vector modifiers
//==============================================================================

/**
 * add an item to the vector. Returns true if successful otherwise returns false and sets errno
 * call ccollection_strerror to get the error string;
 */
cerror_t vector_push_back(vector_t* vector, const item_t* item);
/**
 * Deletes last element present in the container.
 * NOTE: this function does not free memory every time an element is deleted, but only when the container
 * size is significantly less than capacity, nothhing happens if container is empty
 */
cerror_t vector_pop_back(vector_t* vector);
/**
 * assign first n elements vector to the val, if n is > size of vector then new elements are inserted
 */
cerror_t vector_assign_n(vector_t* vector, const size_t n, const item_t* val);
/**
 * Insert a single element at a location in the vector, The element is inserted before the
 * specified position.
 */
cerror_t vector_insert(vector_t* vector, const pos_t pos, const item_t* item);
/**
 * Erase one element from the vetor from specified position and shift all elements
 * to the left by 1 position
 */
cerror_t vector_erase(vector_t* vector, const pos_t pos);
/**
 * Swap content of one vector with the content of another vector
 */
cerror_t vector_swap(vector_t* first, vector_t* second);
/**
 * clear the vector by erasing all elements
 */
cerror_t vector_clear(vector_t* vector);


//==============================================================================
// Elements access
//==============================================================================

/**
 * get and item from vector, if index is < vector size then its value, is copied into item and function returns true.
 * Otherwise function returns false and sets errno.
 * call ccollection_strerror to get the error string;
 */
cerror_t vector_at(const vector_t* vector, const pos_t index, item_t* item);

EXTERN_C_END

#endif /* end of include guard: VECTOR_H */
