#include "include/vector.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

EXTERN_C_BEGIN

/**
 * vector data structure defenition
 */
typedef struct vector_t
{
    uint8_t *items;             /** stores all elements of the container */
    size_t element_size;        /** size of one element */
    size_t size;                /** total number of elements in container */
    size_t capacity;            /** capacity of the container */
} vector_t;

//==============================================================================
// Internal functions
//==============================================================================

/**
 * returns true if size == capacity
 */
bool vector_is_full(const vector_t* vector);
/**
 * resize vector to number of elements supplied by count
 */
cerror_t vector_resize(vector_t* vector, const size_t count);
/**
 * If the size of the vector is <= 1/4 of it's capacity then the container is resized to it's half capacity
 */
cerror_t vector_shrink(vector_t * vector);

//==============================================================================
// ctors and dtors
//==============================================================================
vector_t* vector_new(const size_t elem_size)
{
    errno = 0;
    ASSERT_E(elem_size > 0, EBADELEMSIZE, NULL);

    vector_t* vector = ccollection_calloc(sizeof(vector_t));
    ASSERT(vector != NULL, NULL);

    vector->element_size = elem_size;
    vector_resize(vector, 1);

    return vector;
}

cerror_t vector_destroy(vector_t* vector)
{
    ASSERT_E(vector != NULL, EBADELEMSIZE, ERROR_FAILED);

    ccollection_free(vector->items);
    ccollection_free(vector);

    return ERROR_NONE;
}

//==============================================================================
// Capacity
//==============================================================================
size_t vector_get_size(const vector_t* vector)
{
    return vector->size;
}

size_t vector_get_capacity(const vector_t* vector)
{
    return vector->capacity;
}

bool vector_is_empty(const vector_t* vector)
{
    return (vector->size == 0);
}

//==============================================================================
// vector modifiers
//==============================================================================
cerror_t vector_push_back(vector_t* vector, const item_t* item)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);
    ASSERT_E(item != NULL, EBADPOINTER, ERROR_FAILED);

    if (vector_is_full(vector))
    {
        cerror_t err = vector_resize(vector, vector->capacity * 2); // double the size when vector is full

        ASSERT(err == ERROR_NONE, err);
    }
    ccollection_copy(vector->items + (vector->size * vector->element_size), item, vector->element_size);
    vector->size++;

    return ERROR_NONE;
}

cerror_t vector_pop_back(vector_t* vector)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);

    cerror_t err = ERROR_NONE;

    if (!vector_is_empty(vector))
    {
        vector->size--;
        err = vector_shrink(vector);
    }

    return err;
}

cerror_t vector_assign_n(vector_t* vector, const size_t n, const item_t* val)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);
    ASSERT_E(n > 0, EINVAL, ERROR_FAILED);
    ASSERT_E(val != NULL, EBADPOINTER, ERROR_FAILED);

    // if n < capacity then copy the val to the target element, otherwise first
    // resize the vector then copy the val

    cerror_t err = ERROR_NONE;

    // calculate next power of 2
    int capacity = next_pow2(n);
    while (capacity > vector->capacity)
    {
        err = vector_resize(vector, capacity);
    }

    ASSERT(err == ERROR_NONE, err);

    for(int i = 0; i < n; i++)
    {
        ccollection_copy(vector->items + i * vector->element_size, val, vector->element_size);
    }

    vector->size = MAX(vector->size, n);

    return err;
}

cerror_t vector_insert(vector_t* vector, const pos_t pos, const item_t* item)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);
    ASSERT_E(item != NULL, EBADPOINTER, ERROR_FAILED);
    ASSERT_E(pos <= vector->size && pos >= 0, EOUTOFRANGE, ERROR_FAILED);

    // if size == capacity then reallocate
    if (vector->size == vector->capacity)
    {
        cerror_t err = vector_resize(vector, vector->capacity * 2);
        ASSERT(err == ERROR_NONE, err);
    }
    if (pos == vector->size) // insert at the end
    {
        ccollection_copy(vector->items + vector->size * vector->element_size, item, vector->element_size);
        vector->size++;

        return ERROR_NONE;
    }
    // shift all elements by 1 to right after starting from position pos
    for (int i = vector->size - 1; i >= pos; i--)
    {
        ccollection_copy(vector->items + vector->element_size * (i + 1),
                vector->items + vector->element_size * i,
                vector->element_size);
    }
    // now insert the new element
    ccollection_copy(vector->items + pos * vector->element_size, item, vector->element_size);
    vector->size++;

    return ERROR_NONE;
}

cerror_t vector_erase(vector_t* vector, const pos_t pos)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);
    ASSERT_E(pos < vector->size && pos >= 0, EOUTOFRANGE, ERROR_FAILED);

    cerror_t err = ERROR_NONE;
    if (pos < vector->size - 1) // any element but last
    {
        ccollection_copy(vector->items + pos * vector->element_size,
                vector->items + (pos + 1) * vector->element_size,
                vector->element_size * (vector->size - pos - 1));
    }

    vector->size--;
    return vector_shrink(vector);
}

//==============================================================================
// Elements access
//==============================================================================
cerror_t vector_at(const vector_t* vector, const pos_t index, item_t* item)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);
    ASSERT_E(item != NULL, EBADPOINTER, ERROR_FAILED);
    ASSERT_E(index < vector->size, EOUTOFRANGE, ERROR_FAILED);
    ASSERT_E(index >= 0, EOUTOFRANGE, ERROR_FAILED);

    ccollection_copy(item, vector->items + (index * vector->element_size), vector->element_size);

    return ERROR_NONE;
}

//==============================================================================
// Internal functions
//==============================================================================
bool vector_is_full(const vector_t* vector)
{
    return (vector->size == vector->capacity);
}

cerror_t vector_reserve(vector_t* vector, const size_t count)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);

    if (vector->capacity < count)
    {
        return vector_resize(vector, count);
    }

    return ERROR_NONE;
}

cerror_t vector_resize(vector_t* vector, const size_t count)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED);

    uint8_t *items = ccollection_realloc(vector->items, count * vector->element_size);
    ASSERT(items != NULL, ERROR_FAILED);

    vector->items = items;
    vector->capacity = count;

    return ERROR_NONE;
}

cerror_t vector_shrink(vector_t * vector)
{
    ASSERT_E(vector != NULL, EBADPOINTER, ERROR_FAILED); 
    if (vector->size < vector->capacity / 4)
    {
        return vector_resize(vector, vector->capacity);
    }

    return ERROR_NONE;
}

EXTERN_C_END
