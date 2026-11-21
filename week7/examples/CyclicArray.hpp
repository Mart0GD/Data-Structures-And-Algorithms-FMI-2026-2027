#ifndef __Cyclic_Array_HPP_INCLUDED
#define __Cyclic_Array_HPP_INCLUDED

#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace sdp{

/*
*   Simple implementation of a static cyclic array. The Data Structure supports:
*   
*   Add/Remove in front --> O(1)
*   Add/Remove in back  --> O(1)
*   Indert/Remove_At    --> O(n)
*   Indexing            --> O(1)
*   Iteration
*/
template<typename T>
class CyclicArray {
public:
    //  ### LIFE CYCLE  ####

    CyclicArray(uint32_t size = 0);
    
    CyclicArray(const CyclicArray&);
    CyclicArray& operator=(const CyclicArray&);

    CyclicArray(CyclicArray&&)              noexcept;
    CyclicArray& operator=(CyclicArray&&)   noexcept;

    ~CyclicArray() noexcept;

    //  #### FAST STACK/QUEUE OPPERATIONS  --> O(1) ####

    void        push_front(const T& val);
    void        push_back(const T& val);

    void        push_front(T&& val);
    void        push_back(T&& val);

    bool        pop_back();
    bool        pop_front();

    T&          front();
    T&          back();   

    const T&    front() const;   
    const T&    back()  const;  

    //  #### SLOW ARRAY OPERATIONS    --> O(n) ####

    void        remove_at(uint32_t index);
    void        insert_at(uint32_t index, const T& val);

    // #### GETTERS ####

    inline bool     empty()     const { return size == 0;}
    inline bool     full()      const { return size == cap; }
    inline uint32_t get_size()  const { return size; } 
    inline uint32_t get_cap()   const { return cap; }

    void print() const;

public:

    T&          operator [] (int32_t index);
    const T&    operator [] (int32_t index) const;

private:
    void clear() noexcept;

    T*          data;
    int32_t     head, size, cap;
};

#include "CyclicArray.inl"

}

#endif