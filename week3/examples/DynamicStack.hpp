#ifndef __DYNAMIC_STACK_HPP_INCLUDED__
#define __DYNAMIC_STACK_HPP_INCLUDED__

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "DynamicArray.hpp"

/*
    Implementation of a traditional Stack DS
    using the adapter design pattern with a dynamic array
*/
namespace sdp
{
    template<typename T>
    class DynamicStack
    {   
    public:
    ///
    //  --- Life Cycle ---

        DynamicStack(size_t capacity = 16)  : data(capacity) {};
        
    ///
    //  --- Interaction ---

        void push(const T& el) { data.pushBack(el); }
        T pop(const T& el) 
        {
            T el = std::move(data.back());
            data.popBack();

            return el;
        }

        // STL like implementation
        inline T& top()             { return data.back(); }
        inline const T& top() const { return data.back(); }

        inline void pop() { data.popBack(); }

    /// 
    //  --- Query ---

        bool empty() const { return data.empty(); }

    private:
        DynamicArray<T> data;
    };
} 

#endif
