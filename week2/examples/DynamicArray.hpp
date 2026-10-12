#ifndef __DYNAMIC_ARRAY_HPP_INCLUDED__
#define __DYNAMIC_ARRAY_HPP_INCLUDED__

#include <cstdint>
#include <cassert>
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <iostream>

namespace sdp
{

    template<typename T>
    class DynamicArray
    {
    public:

    //  --- Class Lifecycle ---

        explicit DynamicArray(size_t initial_size = 16);
        
        DynamicArray(std::initializer_list<T> elements);

        DynamicArray(const DynamicArray& other);
        DynamicArray& operator=(const DynamicArray& other);

        DynamicArray(DynamicArray&& other);
        DynamicArray& operator=(DynamicArray&& other);

        ~DynamicArray() noexcept;

    //  --- Appending ---

        DynamicArray& operator += (const T& element);

        DynamicArray& operator += (const DynamicArray<T>& other);      
        
    //  --- Modify operations ---

        void popBack();

        void remove(size_t index);

        void pushBack(const T& element);
        void pushBack(T&& element);

        void insert(const T& element, size_t pos);
        void insert(T&& element, size_t pos);

    // --- Query ---

        bool contains(const T& element) const;

        inline size_t getSize()        const { return size; }

        inline size_t getCapacity()    const { return capacity; }

        void print() const;

    // --- Access ---

        T& operator [] (size_t index);

        const T& operator [] (size_t index) const;

    // --- Iterator logic ---
    
        class ForwardIterator;

        inline ForwardIterator begin() { return ForwardIterator(data); }
        inline ForwardIterator end()   { return ForwardIterator(data + size); }

    private:
    
        void clear() noexcept;

        void resize(size_t new_size);
        void ensureSize(size_t new_size);

        T* data;
        size_t size, capacity;
    };

    template<typename T>
    class DynamicArray<T>::ForwardIterator
    {
    public:

        ForwardIterator(T* data) : ptr(data) {};

        ForwardIterator& operator ++ ()
        {
            ++ptr;
            return *this;
        }
        
        ForwardIterator operator ++ (int)
        {
            ForwardIterator copy(*this);
            ++ptr;
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

        T& operator * () 
        { 
            return *ptr; 
        }

    private:
        T* ptr;
    };

    // Include implementation
    #include "DynamicArray.inl"
}

#endif
