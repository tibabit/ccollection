# ccollection
Implementation of containers like vector, list, queue, deque, stack, set, map, priority queue etc. in C

## Container in progress : vector

```C
/* Create a new vector */
vector_t* vector_new(const size_t elem_size);
/* destory vector, free all memory */
cerror_t vector_destroy(vector_t* vector);
/* Reserve a predetermind size for vector */
cerror_t vector_reserve(vector_t* vector, const size_t count);
/* get number of elements in vector */
size_t vector_get_size(const vector_t* vector);
/* get current capacity of vector */
size_t vector_get_capacity(const vector_t* vector);
/* check if vector is empty */
bool vector_is_empty(const vector_t* vector);
/* insert one element at the end of the vector */
cerror_t vector_push_back(vector_t* vector, const item_t* item);
/* erase an element from the end of the vector */
cerror_t vector_pop_back(vector_t* vector);
cerror_t vector_assign_n(vector_t* vector, const size_t n, const item_t* val);
cerror_t vector_insert(vector_t* vector, const pos_t pos, const item_t* item);
cerror_t vector_erase(vector_t* vector, const pos_t pos);
cerror_t vector_swap(vector_t* first, vector_t* second);
cerror_t vector_clear(vector_t* vector);
cerror_t vector_at(const vector_t* vector, const pos_t index, item_t* item);
```
## How to use
```C
#include <stdio.h>

#include "include/ccollection.h"

int main()
{
    vector_t * vec = vector_new(sizeof(int));

    int value = 100, i;
    vector_push_back(vec, &value);
    vector_push_back(vec, &value);
    vector_push_back(vec, &value);

    for (i = 0; i < vector_get_size(vec); i++)
    {
        vector_at(vec, i, &val);
        printf("%d ", val);
    }

    vector_destroy(vec);
}
```

## Containers to be implemented
- list
- queue
- dequeue
- stack
- set
- map
- priority queue

## Tasks pending
- More unit tests
- benchmarking against STL vector
