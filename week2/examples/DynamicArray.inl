
template<typename T>
DynamicArray<T>::DynamicArray(size_t initial_size)
    : data(nullptr)
    , size(0)
    , capacity(initial_size)
{
    if(initial_size == 0)
    {
        throw std::invalid_argument("Invalid size!");
    }
    data = new T[capacity];
}

template<typename T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> elements)
    : DynamicArray(elements.size())
{
    for (const T& el: elements) pushBack(el);
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other)
{
    capacity = other.capacity;
    size = 0;
    data = new T[capacity];

    try
    {
        for (size_t i = 0; i < other.size; i++)
        {
            data[i] = other.data[i];
            ++size;
        }
        
    }
    catch(...)
    {
        clear();
        throw;
    }
    
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other)
{
    if(this != &other)
    {
        // Amortisation for O(n)
        if(capacity < other.size)
        {
            clear();
            ensureSize(other.capacity);
        }

        // Weak safety
        for (size = 0; size < other.size; ++size)
        {
            data[size] = other.data[size];
        }
        
    }
    return *this;
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other)
    : capacity(0)
    , size(0)
    , data(nullptr)
{
    std::swap(data, other.data);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other)
{
    if(this != &other)
    {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }

    return *this;
}

template<typename T>
DynamicArray<T>::~DynamicArray() noexcept
{
    clear();
}

template<typename T>
void DynamicArray<T>::clear() noexcept
{
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator += (const T& element)
{
    pushBack(element);
    return *this;
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator += (const DynamicArray<T>& other)
{
    ensureSize(size + other.size);
    for (size_t i = 0; i < other.size; ++i)
    {
        data[size + i] = other[i];
    }

    // in case of self append
    size += other.size;

    return *this;
}

template<typename T>
void DynamicArray<T>::pushBack(const T& element)
{
    ensureSize(size + 1);
    data[size] = element;
    ++size;
}

template<typename T>
void DynamicArray<T>::pushBack(T&& element)
{
    ensureSize(size + 1);
    data[size] = std::move(element);
    ++size;
}

template<typename T>
void DynamicArray<T>::popBack()
{
    if(size == 0)
    {
        throw std::invalid_argument("Array is empty!");
    }
    --size;
}

template<typename T>
T& DynamicArray<T>::operator [] (size_t index)
{
    assert(index < size);
    return data[index];
}

template<typename T>
const T& DynamicArray<T>::operator [] (size_t index) const
{
    assert(index < size);
    return data[index];
}

template<typename T>
bool DynamicArray<T>::contains(const T& element) const
{
    for (size_t i = 0; i < size; i++)
    {
        if(element == data[i]) return true;
    }
    
    return false;
}

template<typename T>
void DynamicArray<T>::remove(size_t index)
{
    if(index >= size)
    {
        throw std::out_of_range("Invalid index!");
    }

    for (size_t i = index; i < size - 1; ++i)
    {
        data[i] = std::move(data[i + 1]); 
    }
    --size;
}

template<typename T>
void DynamicArray<T>::insert(const T& element, size_t pos)
{
    if(pos > size)
    {
        throw std::out_of_range("Invalid index!");
    }

    ensureSize(size + 1);
    for (size_t i = size; i > pos; --i)
    {
        data[i] = std::move(data[i - 1]);
    }

    data[pos] = element;
    ++size;
}

template<typename T>
void DynamicArray<T>::insert(T&& element, size_t pos)
{
    if(pos > size)
    {
        throw std::out_of_range("Invalid index!");
    }

    ensureSize(size + 1);
    for (size_t i = size; i > pos; --i)
    {
        data[i] = std::move(data[i - 1]);
    }

    data[pos] = std::move(element);
    ++size;
}

template<typename T>
void DynamicArray<T>::ensureSize(size_t test)
{
    assert(!data || capacity != 0);

    size_t new_size = data ? capacity : 1;
    while(new_size < test)
    {
        // update until it is enough
        new_size *= 2;
    }

    if(new_size != capacity) resize(new_size);
}   


template<typename T>
void DynamicArray<T>::resize(size_t new_cap)
{
    if(new_cap == capacity) return;
    assert(new_cap != 0);
    
    T* new_data = new T[new_cap];

    try
    {
        for (size_t i = 0; i < size && i < new_cap; ++i)
        {
            new_data[i] = data[i];
        }
    }
    catch(...)
    {
        delete[] new_data;
        throw;
    }
    
    delete[] data;

    capacity = new_cap;
    data = new_data;
    size = size > capacity ? capacity : size;
}

template<typename T>
void DynamicArray<T>::print() const
{
    for (size_t i = 0; i < size; i++)
    {
        std::cout << data[i] << ' ';
    }
    std::cout << std::endl;
}