//  :copyright: (c) 2017-2018 Alex Huszagh.
//  :license: MIT, see licenses/mit.md for more details.

#include <pycpp/adaptor/singleton.h>

PYCPP_BEGIN_NAMESPACE

// OBJECTS
// -------


template <bool ThreadSafe = true>
class heap_class: public heap_singleton<heap_class<ThreadSafe>, ThreadSafe>
{};


template <bool ThreadSafe = true>
class stack_class: public stack_singleton<stack_class<ThreadSafe>, sizeof(int), alignof(int), ThreadSafe>
{
    int x;
};

PYCPP_END_NAMESPACE
