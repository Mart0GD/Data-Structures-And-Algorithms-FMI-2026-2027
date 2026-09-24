#ifndef __STATIC_STACK_HPP_INCLUDED__
#define __STATIC_STACK_HPP_INCLUDED__

#include <cstddef>
#include <stdexcept>
#include <utility>


/*
*   Small static implementation of a traditional Stack DS
*/
namespace sdp
{
    template<typename T>
    class StaticStack
    {
    public:
    ///
    // --- Life Cycle ---

        StaticStack(size_t capacity = 16);

        StaticStack(const StaticStack&);
        StaticStack& operator=(const StaticStack&);

        ~StaticStack() noexcept;

    ///
    // --- Interaction  ---

        // Pushes the element on the top of the Stack
        void push(T&& element);
        void push(const T& element);

        // Returns element at the top
        T pop();

    ///
    //  --- Query ---

        inline bool empty()         const { return tos == 0; }
        inline bool full()          const { return tos == size; }

    private:
        void clear() noexcept;

        T* data;
        size_t tos;

        const size_t size;  // <- unchangable 
    };

    #include "StaticStack.inl"
}

#endif