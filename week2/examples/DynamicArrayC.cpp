#include "DynamicArrayC.hpp"


void* _darray_create(uint64_t size, uint64_t stride)
{
    const uint32_t header_size = DARRAY_HEADER_SIZE * sizeof(uint64_t);
    const uint32_t array_size = (size * stride) + header_size;
    
    uint64_t* array = (uint64_t*)malloc(array_size);
    if(!array) return nullptr;

    // Setup fields 
    array[DARRAY_CAPACITY] = size;
    array[DARRAY_SIZE] = 0;
    array[DARRAY_STRIDE] = stride;
    
    return (void*)(array + DARRAY_HEADER_SIZE);
}

void  _darray_free    (void* array)
{
    void* header = (uint64_t*)array - DARRAY_HEADER_SIZE;
    free(header);
}

void  _darray_push(void** array, const void* value)
{
    const uint64_t size = darray_get_size(*array);
    const uint64_t stride = darray_get_stride(*array);
    
    _darray_ensure_size(array, size + 1);
    
    // Pointer arithmetic with void* is UB
    uint64_t address = (uint64_t)(*array);
    address += stride * size;
    
    memcpy((void*)(address), value, stride);
    darray_set_size(*array, size + 1);
}

void _darray_pop(void** array, void* value)
{
    const uint64_t size = darray_get_size(*array);
    const uint64_t stride = darray_get_stride(*array);

    assert(size > 0);
    
    uint64_t address = (uint64_t)*array;
    address += stride * (size - 1);
    memcpy(value, (void*)address, stride);
    darray_set_size(*array, size - 1);
}

uint64_t _darray_get_field(void* array, uint64_t index)
{
    uint64_t* header = (uint64_t*)array - DARRAY_HEADER_SIZE;
    return header[index];
}

void _darray_set_field(void* array, uint64_t value, uint64_t index)
{
    uint64_t* header = (uint64_t*)array - DARRAY_HEADER_SIZE;
    header[index] = value;
}

void  _darray_ensure_size(void** array, uint64_t new_size)
{
    uint64_t cap = darray_get_capacity(*array);
    uint64_t new_cap = cap;

    while(new_cap < new_size)
    {
        new_cap *= RESIZE_FACTOR;
    }

    if(new_cap != cap)
    {
	_darray_resize(array, new_cap);
    }
}

void  _darray_resize  (void** array, uint64_t new_size)
{
    const uint64_t size = darray_get_size(*array);    
    const uint64_t cap  = darray_get_capacity(*array);    
    const uint64_t stride = darray_get_stride(*array);

    void* tmp = _darray_create(new_size, stride);
    memcpy(tmp, *array, size * stride);
    
    darray_free(*array);
    *array = tmp;
    darray_set_size(*array, size);
}
