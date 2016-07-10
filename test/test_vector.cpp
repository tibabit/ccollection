#include <cerrno>

#include "gtest/gtest.h"

#include "include/ccollection.h"

TEST(vectorTest, newVector)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);
    EXPECT_EQ(vector_is_empty(vector), true);
    EXPECT_EQ(vector_get_size(vector), 0);
    EXPECT_EQ(vector_get_capacity(vector), 1);

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

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int val = rand();
        status = vector_push_back(vector, &val);
        EXPECT_EQ(status, true);
    }

    EXPECT_EQ(vector_get_size(vector), count);

    vector_destroy(vector);
}
TEST(vectorTest, vectorAddPointer)
{
    vector_t *vector = vector_new(sizeof(int*));

    ASSERT_TRUE(vector != NULL);

    bool status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int *t = new int[1];
        t[0] = rand();
        status = vector_push_back(vector, &t);
        EXPECT_EQ(status, true);
        delete t;
    }

    EXPECT_EQ(vector_get_size(vector), count);

    vector_destroy(vector);
}

TEST(vectorTest, vectorGetInt)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    int t;
    bool status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int val = rand();
        t = val;
        vector_push_back(vector, &t);

        status = vector_at(vector, i, &t);
        EXPECT_EQ(status, true);
        EXPECT_EQ(t, val);
    }

    vector_destroy(vector);
}
TEST(vectorTest, vectorGetPointer)
{
    vector_t *vector = vector_new(sizeof(int*));

    ASSERT_TRUE(vector != NULL);

    bool status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int *t = new int[1];
        int val = rand();
        t[0] = val;
        vector_push_back(vector, &t);

        status = vector_at(vector, i, &t);
        EXPECT_EQ(status, true);
        EXPECT_EQ(t[0], val);

        delete t;

    }
    vector_destroy(vector);
}
TEST(vectorTest, outOfRangeCheck)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    int t;
    bool status;

    status = vector_at(vector, 0, &t);
    EXPECT_EQ(status, false);
    EXPECT_EQ(errno, EOUTOFRANGE);

    t = 1;
    vector_push_back(vector, &t);

    status = vector_at(vector, 1, &t);
    EXPECT_EQ(status, false);
    EXPECT_EQ(errno, EOUTOFRANGE);

    vector_destroy(vector);
}

TEST(vectorTest, reserve)
{
    vector_t* vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    bool status;

    status = vector_reserve(vector, 10);
    EXPECT_EQ(status, true);
    EXPECT_EQ(vector_get_capacity(vector), 10);

    status = vector_reserve(vector, 5);
    EXPECT_EQ(status, true);
    EXPECT_EQ(vector_get_capacity(vector), 10);

    vector_destroy(vector);
}
