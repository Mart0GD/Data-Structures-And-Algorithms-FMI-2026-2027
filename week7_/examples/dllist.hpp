#ifndef __DLLIST_HPP_INCLUDED__
#define __DLLIST_HPP_INCLUDED__

#include <utility>
#include <stdexcept>
#include <cassert>

namespace sdp
{
    template<typename T>
    class dllist
    {
        struct node
        {
            node() : data(), prev(nullptr), next(nullptr) {}; 
            node(const T& data, node *prev = nullptr, node *next = nullptr) 
                : data(data), prev(prev), next(next) {};

            T data;
            node *prev, *next;
        };

    public:

        dllist();

        dllist(const dllist&);
        dllist& operator=(const dllist&);

        dllist(dllist&&) noexcept;
        dllist& operator=(dllist&&) noexcept;

        ~dllist() noexcept;

    /// 
    //  --- Iterator ---

        class BidirectionalIterator;

        BidirectionalIterator begin() { return BidirectionalIterator(sentinel.next); }
        BidirectionalIterator end() { return BidirectionalIterator(&sentinel); }

    ///
    //  --- Modify ---

        void pushFront(const T& el);
        void pushBack(const T& el);

        void pushBefore(BidirectionalIterator itt, const T& el);
        void pushAfter(BidirectionalIterator itt, const T& el);

        void popFront();
        void popBack();

        void popBefore(BidirectionalIterator itt);
        void popAfter(BidirectionalIterator itt);

    ///
    //  --- Query ---

        T& front();
        const T& front() const;

        T& back();
        const T& back() const;

        bool empty() const { return sentinel.next == &sentinel;}

    private:
        void clear() noexcept;
        void copy(const dllist& other);

        node sentinel;
    };

    template<typename T>
    class dllist<T>::BidirectionalIterator
    {
        friend class dllist<T>;
        node* ptr;
        BidirectionalIterator(node* ptr) : ptr(ptr) {};

    public:

        T&  operator * () const { return ptr->data; }
        T* operator -> () const { return &ptr->data;  }

        bool operator == (const BidirectionalIterator& other) const 
        {
            return ptr == other.ptr;
        }

        bool operator != (const BidirectionalIterator& other) const 
        {
            return !(*this == other);
        }

        BidirectionalIterator& operator ++ ()
        {
            ptr = ptr->next;
            return *this;
        }

        BidirectionalIterator operator ++ (int)
        {
            BidirectionalIterator copy = *this;
            ++(*this);
            return copy;
        }

        BidirectionalIterator& operator -- ()
        {
            ptr = ptr->prev;
            return *this;
        }

        BidirectionalIterator operator -- (int)
        {
            BidirectionalIterator copy = *this;
            --(*this);
            return copy;
        }

    private:

    };

    #include "dllist.inl"
}

#endif