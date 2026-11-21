
template<typename T>
CyclicArray<T>::CyclicArray(uint32_t size)
    : data(nullptr)
    , head(0)
    , size(0)
    , cap(size)
{
    if(size > 0)
    {
        data = new T [size]{};
    }
}

template<typename T>
CyclicArray<T>::CyclicArray(const CyclicArray& other)
    : CyclicArray(other.cap)
{
    try
    {
        for (int i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[(other.head + i) % other.cap];
        }
    }
    catch(...)
    {
        clear();
        throw;
    }

    this->size = other.size;
}

template<typename T>
CyclicArray<T>& CyclicArray<T>::operator=(const CyclicArray& other)
{
    if(this != &other)
    {
        CyclicArray copy(other);
        *this = std::move(copy);
    }

    return *this;
}

template<typename T>
CyclicArray<T>::CyclicArray(CyclicArray&& other) noexcept
    : data(other.data)
    , head(other.head)
    , size(other.size)
    , cap(other.cap)
{
    other.data = nullptr;
}   

template<typename T>
CyclicArray<T>& CyclicArray<T>::operator =(CyclicArray&& other) noexcept
{
    if(this != &other)
    {
        std::swap(data, other.data);
        std::swap(head, other.head);
        std::swap(size, other.size);
        std::swap(cap, other.cap);
    }

    return *this;
}

template<typename T>
CyclicArray<T>::~CyclicArray() noexcept
{
    clear();
}

template<typename T>
void CyclicArray<T>::clear() noexcept
{
    delete[] data; data = nullptr;
    this->head = this->size = this->cap = 0;
}

template<typename T>
void CyclicArray<T>::push_front(const T& val)
{
    if(full()) throw std::runtime_error("Array full!");

    this->data[(this->head - 1 + this->cap) % this->cap] = val;
    this->head = (this->head - 1 + this->cap) % this->cap;
    ++(this->size);
}

template<typename T>
void CyclicArray<T>::push_back(const T& val)
{
    if(full()) throw std::runtime_error("Array full!");

    data[(this->head + this->size) % this->cap] = val;
    ++this->size;
}

template<typename T>
void CyclicArray<T>::push_front(T&& val)
{
    if(full()) throw std::runtime_error("Array full!");

    data[(head - 1 + cap) % cap] = std::move(val);
    head = (head - 1 + cap) % cap;
    ++size;
}

template<typename T>
void CyclicArray<T>::push_back(T&& val)
{
    if(full()) throw std::runtime_error("Array full!");

    data[(head + size) % cap] = std::move(val);
    ++size;
}

template<typename T>
bool CyclicArray<T>::pop_back()
{
    if(empty()) return false;
    --size;

    return true;
}

template<typename T>
bool CyclicArray<T>::pop_front()
{
    if(empty()) return false;
    --size;
    head = (head + 1) % cap;

    return true;
}

template<typename T>
T& CyclicArray<T>::front() 
{
    if(empty()) throw std::runtime_error("Array is empty!");
    return data[head];
}

template<typename T>
T& CyclicArray<T>::back()
{
    if(empty()) throw std::runtime_error("Array is empty!");
    return data[(head + size - 1) % cap];
}

template<typename T>
const T&    CyclicArray<T>::front() const {
    if(empty()) throw std::runtime_error("Array is empty!");
    return data[head];
}   

template<typename T>
const T&    CyclicArray<T>::back()  const
{
    if(empty()) throw std::runtime_error("Array is empty!");
    return data[(head + size - 1) % cap];
}  

template<typename T>
T& CyclicArray<T>::operator [] (int32_t index)
{
    if(index >= size) throw std::runtime_error("Invalid index!");
    return data[(head + index) % cap];
}

template<typename T>
const T&    CyclicArray<T>::operator [] (int32_t index) const
{
    if(index >= size) throw std::runtime_error("Invalid index!");
    return data[(head + index) % cap];
}

template<typename T>
void CyclicArray<T>::remove_at(uint32_t index)
{
    if(index >= size) throw std::runtime_error("Invalid index!");
    if(empty())       throw std::runtime_error("Aray is empty!");

    if(index == 0) pop_front();
    else if(index == size - 1) pop_back();
    else {
        for (int32_t i = index; i < size - 1; i++)
        {
            data[(head + i) % cap] = data[(head + i + 1) % cap];
        }
        --size;
    }
}

template<typename T>
void CyclicArray<T>::insert_at(uint32_t index, const T& val)
{
    if(index > size)   throw std::runtime_error("Invalid index!");
    if(full())          throw std::runtime_error("Array is full!");
    
    if(index == 0) push_front(val);
    else if(index == size) push_back(val);
    else{
        for (int32_t i = size; i > index; --i) {
            int32_t current_phys_idx = (head + i) % cap;
            int32_t prev_phys_idx    = (head + i - 1) % cap;
            
            data[current_phys_idx] = data[prev_phys_idx];
        }

        data[(head + index) % cap] = val;
        ++size;
    }
}

template<typename T>
void CyclicArray<T>::print() const {
    for (int i = 0; i < size; i++)
    {
        std::cout << data[(head + i) % cap];
        if(i + 1 < size) std::cout << ", ";
    }
    
}