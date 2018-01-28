//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.
/**
 *  \addtogroup PyCPP
 *  \brief Singleton CRTP wrapper unittests.
 */

#include <gtest/gtest.h>
#include "singleton_test.h"

PYCPP_USING_NAMESPACE

// TESTS
// -----

TEST(singleton, stack_singleton)
{
    using single = stack_class<false>;
    using multi = stack_class<true>;

    single& s1 = single::get();
    single& s2 = single::get();
    EXPECT_EQ(&s1, &s2);

    multi& m1 = multi::get();
    multi& m2 = multi::get();
    EXPECT_EQ(&m1, &m2);

#ifndef NDEBUG
    ASSERT_DEATH(single(), "");
    ASSERT_DEATH(multi(), "");
#endif
}


TEST(singleton, heap_singleton)
{
    using single = heap_class<false>;
    using multi = heap_class<true>;

    single& s1 = single::get();
    single& s2 = single::get();
    EXPECT_EQ(&s1, &s2);

    multi& m1 = multi::get();
    multi& m2 = multi::get();
    EXPECT_EQ(&m1, &m2);

#ifndef NDEBUG
    ASSERT_DEATH(single(), "");
    ASSERT_DEATH(multi(), "");
#endif
}
