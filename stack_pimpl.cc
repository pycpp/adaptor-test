//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.
/**
 *  \addtogroup PyCPP
 *  \brief Stack Pimpl unittests.
 */

#include <pycpp/adaptor/stack_pimpl.h>
#include <gtest/gtest.h>

PYCPP_USING_NAMESPACE

// FORWARD
// -------

struct structure;
struct int_wrapper;
using pstructure = stack_pimpl<structure, 8>;
using pint_wrapper = stack_pimpl<int_wrapper, sizeof(uintptr_t)>;

// Force the inclusion below
#include "pimpl_test.h"

// TESTS
// -----


TEST(stack_pimpl, integer)
{
    using pint = stack_pimpl<int>;

    pint x(2);
    pint y;
    EXPECT_EQ(x, 2);

    x = 5;
    EXPECT_EQ(x, 5);

    y = x;
    EXPECT_EQ(x, 5);
    EXPECT_EQ(y, 5);

    y = 2;
    EXPECT_EQ(x, 5);
    EXPECT_EQ(y, 2);

    swap(x, y);
    EXPECT_EQ(x, 2);
    EXPECT_EQ(y, 5);
}


TEST(stack_pimpl, structure)
{
    pstructure a = structure {2};
    pstructure b;
    EXPECT_EQ(a->x, 2);

    a->x = 5;
    EXPECT_EQ(a->x, 5);

    b = a;
    EXPECT_EQ(a->x, 5);
    EXPECT_EQ(b->x, 5);

    b->x = 2;
    EXPECT_EQ(a->x, 5);
    EXPECT_EQ(b->x, 2);

    swap(a, b);
    EXPECT_EQ(a->x, 2);
    EXPECT_EQ(b->x, 5);
}


TEST(stack_pimpl, int_wrapper)
{
    pint_wrapper a(int_wrapper {2});    // move ctor
    pint_wrapper b;

    // check null value is properly initalized
    ASSERT_TRUE(b->x_ != nullptr);
    b = int_wrapper {1};                // move assignment

    // check values are properly initialized
    ASSERT_TRUE(a->x_ != nullptr);
    ASSERT_TRUE(b->x_ != nullptr);
    EXPECT_EQ(*a->x_, 2);
    EXPECT_EQ(*b->x_, 1);
    EXPECT_NE(a->x_, b->x_);

    // check copy assignment and ctor
    b = a;
    pint_wrapper c(b);
    ASSERT_TRUE(b->x_ != nullptr);
    ASSERT_TRUE(c->x_ != nullptr);
    EXPECT_EQ(*b->x_, 2);
    EXPECT_EQ(*c->x_, 2);
    EXPECT_NE(a->x_, b->x_);
    EXPECT_NE(a->x_, c->x_);
    EXPECT_NE(b->x_, c->x_);
}
