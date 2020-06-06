#include <gtest/gtest.h>
#include "matrix.h"
#include <algorithm>

using namespace OTUS;

TEST(matrix, create)
{
    const int default_val = -1;
    OTUS::Matrix<int, default_val> m;
    ASSERT_EQ(0, m.size());
}

TEST(matrix, assign)
{
    const int default_val = -1;
    OTUS::Matrix<int, default_val> m;
    m[100][100] = 314;
    ASSERT_EQ(1, m.size());
    int val = m[100][100];
    ASSERT_EQ(314, val);
}

TEST(matrix, long)
{
    const int default_val = -1;
    OTUS::Matrix<long, default_val> m;
    m[100][100] = 314;
    ASSERT_EQ(1, m.size());
    int val = m[100][100];
    ASSERT_EQ(314, val);
}

TEST(matrix, assign_advanced)
{
    const int default_val = -1;
    OTUS::Matrix<int, default_val> m;
    ((m[100][100] = 314) = default_val) = 217;
    ASSERT_EQ(1, m.size());
    int val = m[100][100];
    ASSERT_EQ(217, val);
}

// Assigning the default value should free the cell
TEST(matrix, assign_default)
{
    const int default_val = -1;
    OTUS::Matrix<int, default_val> m;
    ASSERT_EQ(0, m.size());
    m[100][100] = 314;
    ASSERT_EQ(1, m.size());
    m[100][100] = default_val;
    ASSERT_EQ(0, m.size());
}

TEST(matrix, iterators)
{
    const int default_val = -1;
    OTUS::Matrix<int, default_val> m;
    int val1 = 10;
    int val2 = 20;
    m[200][100] = val1;
    m[100][200] = val2;
    ASSERT_EQ(2, m.size());
    bool seen1 = false;
    bool seen2 = false;

    for(auto  e: m)
    {
        auto [i, v] = e;
        if(v == val1)
            seen1 = true;
        if(v == val2)
            seen2 = true;
    }
    ASSERT_TRUE(seen1 && seen2);
}

// Creating 3D matrix
TEST(matrix, higher_dim)
{
    const int default_val = -1;
    OTUS::Matrix<int, default_val, 3> m;
    ASSERT_EQ(0, m.size());
    m[100][100][100] = 314;
    ASSERT_EQ(1, m.size());
    m[100][100][100] = default_val;
    ASSERT_EQ(0, m.size());
}

// Creating 1D matrix
TEST(matrix, dim_1)
{
    const int default_val = -1;
    OTUS::Matrix<int, default_val, 1> m;
    ASSERT_EQ(0, m.size());
    int exp_val = 314;
    m[100] = exp_val;
    ASSERT_EQ(1, m.size());
    int val = m[100];
    ASSERT_EQ(exp_val, val);
    m[100] = default_val;
    ASSERT_EQ(0, m.size());
}
