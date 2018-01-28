//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.
/**
 *  \addtogroup PyCPP
 *  \brief Heap Pimpl unittests.
 */

#include <pycpp/adaptor/heap_pimpl.h>
#include <gtest/gtest.h>

PYCPP_USING_NAMESPACE


// TESTS
// -----


TEST(unique_heap_pimpl, integer)
{
    using allocator_type = allocator<int>;
    using pint = unique_heap_pimpl<int, allocator_type>;
    static_assert(sizeof(pint) == sizeof(int*), "global allocator shouldn't have overhead.");

    // constructors
    allocator_type alloc;
    int x = 2;
    pint p1;
    pint p2(alloc);
    pint p3(p1);
    pint p4(p1, alloc);
    pint p5(x);
    pint p6(x, alloc);
    pint p7(move(p1));
    pint p8(move(p2), alloc);
    pint p9(2);
    pint p10(2, alloc);

    EXPECT_EQ(p5, 2);
    EXPECT_EQ(p6, 2);
    EXPECT_EQ(p9, 2);
    EXPECT_EQ(p10, 2);

    // assignment
    p2 = x;
    EXPECT_EQ(p2, 2);

    p1 = p9;
    EXPECT_EQ(p1, 2);
    EXPECT_EQ(p2, 2);

    // modifying a copy does not modify the original
    p1 = 5;
    EXPECT_EQ(p1, 5);
    EXPECT_EQ(p2, 2);
    EXPECT_EQ(p9, 2);

    // modifiers
    swap(p1, p2);
    EXPECT_EQ(p1, 2);
    EXPECT_EQ(p2, 5);

    p1.swap(p2);
    EXPECT_EQ(p2, 2);
    EXPECT_EQ(p1, 5);
}


TEST(unique_heap_pimpl, std_allocator)
{
    using allocator_type = std::allocator<int>;
    using pint = unique_heap_pimpl<int, allocator_type>;
    static_assert(sizeof(pint) == sizeof(int*), "std::allocator shouldn't have overhead.");
}


TEST(shared_heap_pimpl, integer)
{
    using allocator_type = allocator<int>;
    using pint = shared_heap_pimpl<int>;

    // constructors
    allocator_type alloc;
    int x = 2;
    pint p1;
    pint p2(alloc);
    pint p3(p1);
    pint p4(x);
    pint p5(x, alloc);
    pint p6(move(p1));
    pint p7(2);
    pint p8(2, alloc);

    EXPECT_EQ(p4, 2);
    EXPECT_EQ(p5, 2);
    EXPECT_EQ(p7, 2);
    EXPECT_EQ(p8, 2);

    // assignment
    p2 = x;
    EXPECT_EQ(p2, 2);

    p1 = p7;
    EXPECT_EQ(p1, 2);
    EXPECT_EQ(p2, 2);

    // modifying a copy does modify the original, but not
    // arbitrary ones
    p1 = 5;
    EXPECT_EQ(p1, 5);
    EXPECT_EQ(p2, 2);
    EXPECT_EQ(p7, 5);

    // modifiers
    swap(p1, p2);
    EXPECT_EQ(p1, 2);
    EXPECT_EQ(p2, 5);

    p1.swap(p2);
    EXPECT_EQ(p2, 2);
    EXPECT_EQ(p1, 5);
}
