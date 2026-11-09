#ifndef __STATIC_QUEUE_HPP_INCLUDED__
#define __STATIC_QUEUE_HPP_INCLUDED__

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace sdp
{
    template<typename T>
    class StaticQueue
    {
    public:
    ///
    //  --- Life Cycle ---

        explicit StaticQueue(size_t capacity = 16);

        StaticQueue(const StaticQueue& other);
        StaticQueue& operator=(const StaticQueue& other);
        
        ~StaticQueue() noexcept;

    ///
    //  --- Access ---

        void enqueue(const T& el);
        T    dequeue();

        T&   front();
        const T&   front() const;

    ///
    //  --- Query ---

        bool empty() const { return size == 0; }
        bool full()  const { return size == capacity; }

    private:

        void clear() noexcept;
        
        T* data;
        size_t head, size;
        size_t capacity;
    };

    #include "StaticQueue.inl"
}

#endif