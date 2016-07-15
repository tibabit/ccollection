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
    cerror_t status;

    const size_t count = 1 << 20;

    for (int i = 0; i < count; i++)
    {
        int val = rand();
        status = vector_push_back(vector, &val);
        EXPECT_EQ(status, ERROR_NONE);
    }

    EXPECT_EQ(vector_get_size(vector), count);

    vector_destroy(vector);
}
TEST(vectorTest, vectorPopBack)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    int t;
    cerror_t status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int val = rand();
        status = vector_push_back(vector, &val);
        EXPECT_EQ(status, ERROR_NONE);
    }
    EXPECT_EQ(vector_get_size(vector), count);
    for (int i = 0; i < count; i++)
    {
        status = vector_pop_back(vector);
        EXPECT_EQ(status, ERROR_NONE);
    }

    EXPECT_EQ(vector_get_size(vector), 0);

    vector_destroy(vector);
}
TEST(vectorTest, pushAfterPop)
{
    vector_t *vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    int t;
    cerror_t status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int val = rand();
        status = vector_push_back(vector, &val);
        EXPECT_EQ(status, ERROR_NONE);
    }
    EXPECT_EQ(vector_get_size(vector), count);
    for (int i = 0; i < count; i++)
    {
        status = vector_pop_back(vector);
        EXPECT_EQ(status, ERROR_NONE);
    }
    EXPECT_EQ(vector_get_size(vector), 0);

    for (int i = 0; i < count; i++)
    {
        int val = rand();
        status = vector_push_back(vector, &val);
        EXPECT_EQ(status, ERROR_NONE);
    }
    EXPECT_EQ(vector_get_size(vector), count);

    vector_destroy(vector);
}
TEST(vectorTest, vectorAddPointer)
{
    vector_t *vector = vector_new(sizeof(int*));

    ASSERT_TRUE(vector != NULL);

    cerror_t status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int *t = new int[1];
        t[0] = rand();
        status = vector_push_back(vector, &t);
        EXPECT_EQ(status, ERROR_NONE);
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
    cerror_t status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int val = rand();
        t = val;
        vector_push_back(vector, &t);

        status = vector_at(vector, i, &t);
        EXPECT_EQ(status, ERROR_NONE);
        EXPECT_EQ(t, val);
    }

    vector_destroy(vector);
}
TEST(vectorTest, vectorGetPointer)
{
    vector_t *vector = vector_new(sizeof(int*));

    ASSERT_TRUE(vector != NULL);

    cerror_t status;

    const size_t count = 1000000;

    for (int i = 0; i < count; i++)
    {
        int *t = new int[1];
        int val = rand();
        t[0] = val;
        vector_push_back(vector, &t);

        status = vector_at(vector, i, &t);
        EXPECT_EQ(status, ERROR_NONE);
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
    cerror_t status;

    status = vector_at(vector, 0, &t);
    EXPECT_EQ(status, ERROR_FAILED);
    EXPECT_EQ(errno, EOUTOFRANGE);

    t = 1;
    vector_push_back(vector, &t);

    status = vector_at(vector, 1, &t);
    EXPECT_EQ(status, ERROR_FAILED);
    EXPECT_EQ(errno, EOUTOFRANGE);

    vector_destroy(vector);
}

TEST(vectorTest, reserve)
{
    vector_t* vector = vector_new(sizeof(int));

    ASSERT_TRUE(vector != NULL);

    cerror_t status;

    status = vector_reserve(vector, 10);
    EXPECT_EQ(status, ERROR_NONE);
    EXPECT_EQ(vector_get_capacity(vector), 10);

    status = vector_reserve(vector, 5);
    EXPECT_EQ(status, ERROR_NONE);
    EXPECT_EQ(vector_get_capacity(vector), 10);

    vector_destroy(vector);
}
TEST(vectorTest, assign_fill)
{
    vector_t *vector = vector_new(sizeof(int));

    const int val = 100;
    const int count = 1 << 20;

    ASSERT_TRUE(vector != NULL);

    vector_assign_n(vector, count, &val);
    EXPECT_EQ(vector_get_size(vector), count);
    for (int i = 0; i < count; i++)
    {
        int out;
        cerror_t status = vector_at(vector, i, &out);

        EXPECT_EQ(status, ERROR_NONE);
        EXPECT_EQ(out, val);
    }
    EXPECT_EQ(vector_get_size(vector), count);
    EXPECT_EQ(vector_get_capacity(vector), count);
    vector_destroy(vector);
}

TEST(vectorTest, insertAt0InEmptyVector)
{
    vector_t* vector = vector_new(sizeof(int));

    int val = 100, out = 0;
    cerror_t err = vector_insert(vector, 0, &val);

    ASSERT_EQ(err, ERROR_NONE);

    EXPECT_EQ(vector_get_size(vector), 1);
    vector_at(vector, 0, &out);
    EXPECT_EQ(val, out);
}

TEST(vectorTest, insertAt1InEmptyVector)
{
    vector_t* vector = vector_new(sizeof(int));

    int val = 100, out = 0;
    cerror_t err = vector_insert(vector, 5, &val);

    ASSERT_EQ(err, ERROR_FAILED);
    ASSERT_EQ(errno, EOUTOFRANGE);

    EXPECT_EQ(vector_get_size(vector), 0);
}

TEST(vectorTest, insertAt0InNonEmptyVector)
{
    vector_t* vector = vector_new(sizeof(int));

    int val = 100, out = 0;
    const size_t count = 1 << 10;

    for (int i = 0; i < count; i++)
    {
        val = (i + 1) * 10;
        vector_push_back(vector, &val);
    }
    cerror_t err = vector_insert(vector, 0, &val);

    ASSERT_EQ(err, ERROR_NONE);
    EXPECT_EQ(vector_get_size(vector), count + 1);

    vector_at(vector, 0, &out);
    EXPECT_EQ(val, out);
    for (int i = 1; i < count + 1; i++)
    {
        vector_at(vector, i, &out);
        EXPECT_EQ(out, i * 10);
    }
}

TEST(vectorTest, insertInMiddleInNonEmptyVector)
{
    vector_t* vector = vector_new(sizeof(int));

    int val = 100, out = 0;
    const size_t count = 1 << 10;

    for (int i = 0; i < count; i++)
    {
        val = (i + 1) * 10;
        vector_push_back(vector, &val);
    }
    cerror_t err = vector_insert(vector, 5, &val);

    ASSERT_EQ(err, ERROR_NONE);
    EXPECT_EQ(vector_get_size(vector), count + 1);

    vector_at(vector, 5, &out);
    EXPECT_EQ(val, out);
    for (int i = 6; i < count + 1; i++)
    {
        vector_at(vector, i, &out);
        EXPECT_EQ(out, i * 10);
    }
}

TEST(vectorTest, eraseAt0InEmptyVector)
{
    vector_t* vector = vector_new(sizeof(int));

    cerror_t err = vector_erase(vector, 0);

    ASSERT_EQ(err, ERROR_FAILED);
    ASSERT_EQ(errno, EOUTOFRANGE);
}

TEST(vectorTest, eraseAt0InAnOneElementVector)
{
    vector_t* vector = vector_new(sizeof(int));

    int val = 100, out = 0;
    cerror_t err = vector_push_back(vector, &val);

    ASSERT_EQ(err, ERROR_NONE);

    err = vector_erase(vector, 0);
    ASSERT_EQ(err, ERROR_NONE);
    EXPECT_EQ(vector_get_size(vector), 0);
}

TEST(vectorTest, eraseInMiddleInNonEmptyVector)
{
    vector_t* vector = vector_new(sizeof(int));

    int val = 100, out = 0;
    const size_t count = 1 << 10;

    for (int i = 0; i < count; i++)
    {
        val = (i + 1) * 10;
        vector_push_back(vector, &val);
    }
    cerror_t err = vector_erase(vector, 5);

    ASSERT_EQ(err, ERROR_NONE);
    EXPECT_EQ(vector_get_size(vector), count - 1);

    for (int i = 5; i < count - 1; i++)
    {
        vector_at(vector, i, &out);
        EXPECT_EQ(out, (i + 2) * 10);
    }
}
