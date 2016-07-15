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
cerror_t vector_insert(vector_t* vector, const size_t pos, const item_t* item);


//==============================================================================
// Elements access
//==============================================================================

/**
 * get and item from vector, if index is < vector size then its value, is copied into item and function returns true.
 * Otherwise function returns false and sets errno.
 * call ccollection_strerror to get the error string;
 */
cerror_t vector_at(const vector_t* vector, const size_t index, item_t* item);

EXTERN_C_END

#endif /* end of include guard: VECTOR_H */
