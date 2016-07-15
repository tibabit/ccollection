#ifndef CCOLLECTION_H

#define CCOLLECTION_H

#include "include/ccollection-internal.h"

EXTERN_C_BEGIN
/**
 * \brief get error description for errno defined by ccollection library
 */
const char* ccollection_strerror(int err);

EXTERN_C_END

#include "include/vector.h"

#endif /* end of include guard: CCOLLECTION_H */
