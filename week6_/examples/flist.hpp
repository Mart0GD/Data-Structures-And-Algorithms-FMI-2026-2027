#ifndef __FLIST_HPP_INCLUDED__
#define __FLIST_HPP_INCLUDED__

#include <stdexcept>
#include <utility>
#include <cstddef>
#include <cassert>

namespace sdp
{
    template<typename T>
    class flist
    {
        struct node
        {
            T data;
            node* next;

            node() : data(), next(nullptr) {};
            node(const T& data, node* next = nullptr) : data(data), next(next) {};
        };

    public:

        flist() : head(nullptr), tail(nullptr) {};

        flist(const flist&);
        flist& operator=(const flist&);

        flist(flist&&) noexcept;
        flist& operator=(flist&&) noexcept;

        ~flist() noexcept;

        class ForwardIterator;

        ForwardIterator begin() { return ForwardIterator(head); }
        ForwardIterator end()   { return ForwardIterator(nullptr); }

        void pushFront(const T& el);
        void pushBack(const T& el);
        void pushAfter(ForwardIterator& itt, const T& el);
        void pushAt(size_t pos, const T& el);   // Linear complexity

        T    popFront();
        T    popBack();                         // Linear complexity
        T    popAfter(ForwardIterator& itt);
        T    popAt(size_t pos);                 // Linear complexity

        const T& front() const;
        const T& back()  const;
        const T& at(size_t index) const;        // Linear complexity

        bool empty() const { return head == nullptr; }
        
        void append(flist other);
        
        void sortInplace();
        void sort();
        
        void reverse();

    private:

        void clearMemory(node*& n);
        void copy(const flist& other);

        node* mergeSort(node* n);

        node* split(node* n);
        node* merge(node* n1, node* n2);
        void  fixTail();

        node *head, *tail;
    };

    template<typename T>
    class flist<T>::ForwardIterator 
    {
        friend class flist<T>;
        flist<T>::node *ptr;

        ForwardIterator(flist<T>::node *ptr) : ptr(ptr) {};
    public:

        T&        operator *()         { return ptr->data; }
        const T&  operator *()   const { return ptr->data; }

        T*        operator -> ()       {return &ptr->data; }
        const T*  operator -> () const {return &ptr->data; }

        ForwardIterator& operator ++ ()
        {
            ptr = ptr->next;
            return *this;
        }

        ForwardIterator operator ++ (int)
        {
            ForwardIterator copy = ForwardIterator(*this);
            ++(*this);
            return copy;
        }

        bool operator == (const ForwardIterator& other) const
        {
            return ptr == other.ptr;
        }

        bool operator != (const ForwardIterator& other) const
        {
            return !(*this == other);
        }

        operator bool () const
        {
            return ptr != nullptr;
        }
    };

    #include "flist.inl"
}

#endif