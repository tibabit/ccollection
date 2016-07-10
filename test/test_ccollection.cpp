#include "gtest/gtest.h"

#include "include/ccollection-internal.h"

TEST(CCollection, ccollectionStrerror)
{
    EXPECT_STREQ(ccollection_strerror(EBADELEMSIZE), "Invalid element size");
    EXPECT_STREQ(ccollection_strerror(EBADPOINTER), "Bad pointer");
    EXPECT_STREQ(ccollection_strerror(EOUTOFRANGE), "Index out of range");
}
