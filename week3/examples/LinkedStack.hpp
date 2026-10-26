#ifndef __LINKED_STACK_HPP_INCLUDED__
#define __LINKED_STACK_HPP_INCLUDED__

#include <utility>
#include <stdexcept>
#include <cassert>

namespace sdp
{
    template<typename T>
    class LinkedStack
    {
        // Special node wrapper for data
        struct node
        {
            T data;
            node* next;

            node() : data({}), next(nullptr) {};
            node(const T& el, node* next = nullptr) : data(el), next(next) {};
        };

    public:
    /// 
    //  --- Life Cycle 

        LinkedStack() : tos(nullptr) {};

        LinkedStack(const LinkedStack&);
        LinkedStack& operator=(const LinkedStack&);

        LinkedStack(LinkedStack&&);
        LinkedStack& operator=(LinkedStack&&);

        ~LinkedStack() noexcept;

    ///
    //  --- Interaction ---

        void push(const T& el);
        void pop();

    ///
    //  --- Query ---

        T& top();

        inline bool empty() const { return tos == nullptr; } 

    private:    
        void clear(node*& n) noexcept;

        /* 
        *   Recursive copy
        *   Causes segmentation fault for large data sets because of Stack Overflow
        * 
        *   DON'T USE!!!
        */ 
        node* copy(const node* otherTos);

        // Iterative copy --> safe to use 
        void  copy(const LinkedStack<T>& other);
        
        node* tos;
    };

    #include "LinkedStack.inl"
}

#endif