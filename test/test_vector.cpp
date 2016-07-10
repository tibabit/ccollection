#include <cerrno>

#include "gtest/gtest.h"

#include "include/ccollection.h"

TEST(vectorTest, newVector)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);
    EXPECT_EQ(vector_is_empty(vector), true);
    EXPECT_EQ(vector_get_size(vector), 0);
    EXPECT_EQ(vector_get_capacity(vector), 0);

    vector_destroy(vector);
}

TEST(vectorTest, newVectorBadSize)
{
    // element size 0
    vector_t *vector = vector_new(0);
    EXPECT_TRUE(vector == NULL);
    EXPECT_EQ(errno, EBADELEMSIZE);
}

TEST(vectorTest, vectorAddInt)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    int t;
    bool status;

    t = 1;
    status = vector_add(vector, &t);
    EXPECT_EQ(status, true);

    t = 2;
    status = vector_add(vector, &t);
    EXPECT_EQ(status, true);

    t = 3;
    status = vector_add(vector, &t);
    EXPECT_EQ(status, true);

    EXPECT_EQ(vector_get_size(vector), 3);

    vector_destroy(vector);
}
TEST(vectorTest, vectorAddPointer)
{
    vector_t *vector = vector_new(sizeof(int*));

    ASSERT_TRUE(vector != NULL);

    int *t = new int[1];
    bool status;

    t[0] = 1;
    status = vector_add(vector, &t);
    EXPECT_EQ(status, true);

    t[0] = 2;
    status = vector_add(vector, &t);
    EXPECT_EQ(status, true);

    t[0] = 3;
    status = vector_add(vector, &t);
    EXPECT_EQ(status, true);

    EXPECT_EQ(vector_get_size(vector), 3);

    delete t;
    vector_destroy(vector);
}

TEST(vectorTest, vectorGetInt)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    int t;
    bool status;

    t = 1;
    vector_add(vector, &t);
    t = 2;
    vector_add(vector, &t);
    t = 3;
    vector_add(vector, &t);

    EXPECT_EQ(vector_get_size(vector), 3);

    status = vector_get(vector, 0, &t);
    EXPECT_EQ(status, true);
    EXPECT_EQ(t, 1);

    status = vector_get(vector, 1, &t);
    EXPECT_EQ(status, true);
    EXPECT_EQ(t, 2);

    status = vector_get(vector, 2, &t);
    EXPECT_EQ(status, true);
    EXPECT_EQ(t, 3);

    vector_destroy(vector);
}
TEST(vectorTest, vectorGetPointer)
{
    vector_t *vector = vector_new(sizeof(int*));

    ASSERT_TRUE(vector != NULL);

    int *t = new int[1];
    int *u = new int[1];
    int *v = new int[1];
    bool status;

    t[0] = 1;
    vector_add(vector, &t);

    u[0] = 2;
    vector_add(vector, &u);

    v[0] = 3;
    vector_add(vector, &v);

    EXPECT_EQ(vector_get_size(vector), 3);

    status = vector_get(vector, 0, &t);
    EXPECT_EQ(status, true);
    EXPECT_EQ(t[0], 1);

    status = vector_get(vector, 1, &u);
    EXPECT_EQ(status, true);
    EXPECT_EQ(u[0], 2);

    status = vector_get(vector, 2, &v);
    EXPECT_EQ(status, true);
    EXPECT_EQ(v[0], 3);

    delete t;
    delete u;
    delete v;
    vector_destroy(vector);
}
TEST(vectorTest, outOfRangeCheck)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    int t;
    bool status;

    status = vector_get(vector, 0, &t);
    EXPECT_EQ(status, false);
    EXPECT_EQ(errno, EOUTOFRANGE);

    t = 1;
    vector_add(vector, &t);

    status = vector_get(vector, 1, &t);
    EXPECT_EQ(status, false);
    EXPECT_EQ(errno, EOUTOFRANGE);

    vector_destroy(vector);
}
