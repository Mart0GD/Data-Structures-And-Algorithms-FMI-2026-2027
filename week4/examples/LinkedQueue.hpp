#ifndef __LINKED_QUEUE_HPP_INCLUDED__
#define __LINKED_QUEUE_HPP_INCLUDED__

#include <utility>
#include <stdexcept>

namespace sdp
{
    template<typename T>
    class LinkedQueue
    {

        struct node
        {
            T data;
            node* next;

            node(const T& data, node* next = nullptr) : data(data), next(next) {};
        };

    public:

        LinkedQueue() : head(nullptr), tail(nullptr) {};

        LinkedQueue(const LinkedQueue& other);
        LinkedQueue& operator=(const LinkedQueue& other);

        LinkedQueue(LinkedQueue&& other) noexcept;
        LinkedQueue& operator=(LinkedQueue&& other) noexcept;

        ~LinkedQueue() noexcept;

        void enqueue(const T& el);
        T    dequeue();

        T& front();
        const T& front() const;

        bool empty() const { return head == nullptr; }
        
    private:
        void copy(const LinkedQueue& other);
        static void clear(node*& head) noexcept;

        node *head, *tail;
    };

    #include "LinkedQueue.inl"
}

#endif