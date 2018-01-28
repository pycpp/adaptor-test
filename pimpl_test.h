//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.

#include <pycpp/stl/cstdint.h>

// OBJECTS
// -------

struct structure
{
    uint64_t x;
};


// Provide a class managing a resource.
// If the class properly initializes for the copy and move
// constructors and assignment operators, `x_` will properly
// have a new pointer when copied and therefore will properly
// copy any managed resources. If `x_` is not copied properly,
// and rather uses the same address before `stack_pimpl` copies
// it, then the copy is treating the memory block as a series
// of dumb bytes.
struct int_wrapper
{
    uint64_t* x_ = nullptr;

    int_wrapper(
        uint64_t x = 0
    ):
        x_(new uint64_t(x))
    {}

    int_wrapper(
        const int_wrapper& x
    ):
        x_(x.x_ ? new uint64_t(*x.x_) : nullptr)
    {}

    int_wrapper&
    operator=(
        const int_wrapper& x
    )
    {
        delete x_;
        x_ = x.x_ ? new uint64_t(*x.x_) : nullptr;
        return *this;
    }

    int_wrapper(
        int_wrapper&& x
    )
    {
        swap(x_, x.x_);
    }

    int_wrapper&
    operator=(
        int_wrapper&& x
    )
    {
        swap(x_, x.x_);
        return *this;
    }

    ~int_wrapper()
    {
        delete x_;
    #ifndef NDEBUG
        x_ = nullptr;
    #endif
    }
};
