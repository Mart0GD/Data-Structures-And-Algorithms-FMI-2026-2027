#ifndef __DYNAMIC_ARRAY_CPP_HPP_INCLUDED__
#define __DYNAMIC_ARRAY_CPP_HPP_INCLUDED__

#include "stdint.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

typedef enum darray_header
{
    DARRAY_CAPACITY,
    DARRAY_SIZE,
    DARRAY_STRIDE,
    DARRAY_HEADER_SIZE,
} darray_header;


#define RESIZE_FACTOR 2
#define INITIAL_CAPACITY 1

// -- PRIVATE FUNCTIONALITY --

void* _darray_create  (uint64_t size, uint64_t stride);
void  _darray_free    (void* array);

void  _darray_push    (void** array, const void* value);
void  _darray_pop     (void** array, void* value);

void  _darray_resize  (void** array, uint64_t new_size);
void  _darray_ensure_size(void** array, uint64_t new_size);

uint64_t _darray_get_field(void* array, uint64_t index);
void     _darray_set_field(void* array, uint64_t value, uint64_t index);

// -- API --

#define darray_create(type)                _darray_create(INITIAL_CAPACITY, sizeof(type));
#define darray_create_sized(size, type)    _darray_create(size, sizeof(type));

#define darray_free(array)                 _darray_free(array);
#define darray_pop(array, value)           _darray_pop((void**)&array, value)

#define darray_push(array, value)          \
{                                          \
    typeof(value) temp = value;            \
    _darray_push((void**)&array, &temp);   \
};


#define darray_get_capacity(array)         _darray_get_field(array, DARRAY_CAPACITY);
#define darray_get_size(array)             _darray_get_field(array, DARRAY_SIZE);
#define darray_get_stride(array)           _darray_get_field(array, DARRAY_STRIDE);

#define darray_set_capacity(array, value)         _darray_set_field(array, value, DARRAY_CAPACITY);
#define darray_set_size(array, value)             _darray_set_field(array, value, DARRAY_SIZE);
#define darray_set_stride(array, value)           _darray_set_field(array, value, DARRAY_STRIDE);

#endif 


