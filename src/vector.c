#include "include/vector.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

EXTERN_C_BEGIN


typedef struct vector_t
{
    uint8_t *items;             /** stores all elements of the container */
    size_t element_size;        /** size of one element */
    size_t size;                /** total number of elements in container */
    size_t capacity;            /** capacity of the container */
} vector_t;

/**
 * returns true if size == capacity
 */
bool vector_is_full(vector_t* vector);
/**
 * resize vector to number of elements supplied by count
 */
bool vector_resize(vector_t* vector, size_t count);
/**
 * shrink vector to a smaller size
 */
bool vector_shrink(vector_t* vector, size_t count);

vector_t* vector_new(size_t elem_size)
{
    errno = 0;
    ASSERT_E(elem_size > 0, EBADELEMSIZE, NULL);

    vector_t* vector = ccollection_calloc(sizeof(vector_t));
    ASSERT(vector != NULL, NULL);

    vector->element_size = elem_size;
    vector_resize(vector, 1);

    return vector;
}

void vector_destroy(vector_t* vector)
{
    ASSERT(vector != NULL);

    ccollection_free(vector->items);
    ccollection_free(vector);
}

size_t vector_get_size(vector_t* vector)
{
    return vector->size;
}

size_t vector_get_capacity(vector_t* vector)
{
    return vector->capacity;
}

bool vector_is_empty(vector_t* vector)
{
    return (vector->size == 0);
}

bool vector_push_back(vector_t* vector, item_t* item)
{
    ASSERT_E(vector != NULL, EBADPOINTER, false);
    ASSERT_E(item != NULL, EBADPOINTER, false);

    if (vector_is_full(vector))
    {
        bool status = vector_resize(vector, vector->capacity * 2); // double the size when vector is full

        if (!status)
        {
            return status;
        }
    }
    memcpy(vector->items + (vector->size * vector->element_size), item, vector->element_size);
    vector->size++;

    return true;
}

bool vector_pop_back(vector_t* vector)
{
    ASSERT_E(vector != NULL, EBADPOINTER, false);

    bool status = true;

    if (!vector_is_empty(vector))
    {
        vector->size--;

        // if new size <= 25 % of capacity resize it half capacity
        if (vector->size <= vector->capacity / 4)
        {
            status = vector_shrink(vector, vector->capacity / 2);
        }
    }

    return status;
}

bool vector_at(vector_t* vector, size_t index, item_t* item)
{
    ASSERT_E(vector != NULL, EBADPOINTER, false);
    ASSERT_E(item != NULL, EBADPOINTER, false);
    ASSERT_E(vector->size > index, EOUTOFRANGE, false);

    memcpy(item, vector->items + (index * vector->element_size), vector->element_size);

    return true;
}

bool vector_is_full(vector_t* vector)
{
    return (vector->size == vector->capacity);
}

bool vector_reserve(vector_t* vector, size_t count)
{
    ASSERT_E(vector != NULL, EBADPOINTER, false);

    if (vector->capacity < count)
    {
        return vector_resize(vector, count);
    }

    return true;
}

bool vector_resize(vector_t* vector, size_t count)
{
    ASSERT_E(vector != NULL, EBADPOINTER, false);

    uint8_t *items = ccollection_realloc(vector->items, count * vector->element_size);
    ASSERT(items != NULL, false);

    vector->items = items;
    vector->capacity = count;

    return true;
}

bool vector_shrink(vector_t* vector, size_t count)
{
    ASSERT_E(vector != NULL, EBADPOINTER, false);

    if (count >= vector->capacity)
    {
        return true;
    }

    // allocate new array of reduced size
    uint8_t* items = ccollection_calloc(count * vector->element_size);
    ASSERT(items != NULL, false);

    // copy elements
    ccollection_copy(items, vector->items, count * vector->element_size);

    // free container elements
    ccollection_free(vector->items);

    vector->items = items;
    vector->capacity = count;

    return true;
}

EXTERN_C_END
