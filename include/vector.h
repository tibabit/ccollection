#ifndef VECTOR_H

#define VECTOR_H

#include "include/ccollection-internal.h"

EXTERN_C_BEGIN

typedef struct vector_t vector_t; /** opaque pointer definition for vector */

/* ctor and dtor */

/**
 * returns a pointer to vector_t with inital capacity 0. returns NULL of elem_size <=0 and sets errno.
 * call ccollection_strerror to get the error string;
 */
vector_t* vector_new(size_t elem_size);
/**
 * destroy all elements and cleanup all elements
 */
void vector_destroy(vector_t* vector);
/**
 * increase capacity of vector to accomodate minimum number of elements supplied by count. Return true if successful.
 * Otherwise returns false.
 * If current capacity of the container is > count, nothing happens.
 * call ccollection_strerror to get the error string.
 */
bool vector_reserve(vector_t* vector, size_t count);

/** vector manipulation */
/**
 * add an item to the vector. Returns true if successful otherwise returns false and sets errno
 * call ccollection_strerror to get the error string;
 */
bool vector_add(vector_t* vector, item_t* item);

/**
 * get and item from vector, if index is < vector size then its value, is copied into item and function returns true.
 * Otherwise function returns false and sets errno.
 * call ccollection_strerror to get the error string;
 */
bool vector_get(vector_t* vector, size_t index, item_t* item);

/**
 * get size of vector
 */
size_t vector_get_size(vector_t* vector);
/**
 * get capacity of vector
 */
size_t vector_get_capacity(vector_t* vector);
/**
 * check if vector is empty
 */
bool vector_is_empty(vector_t* vector);

EXTERN_C_END

#endif /* end of include guard: VECTOR_H */
