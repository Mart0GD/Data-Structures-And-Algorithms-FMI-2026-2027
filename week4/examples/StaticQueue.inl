
template<typename T>
StaticQueue<T>::StaticQueue(size_t capacity)
    : data(nullptr)
    , head(0)
    , size(0)
    , capacity(capacity)
{
    data = new T[capacity];
}

template<typename T>
StaticQueue<T>::StaticQueue(const StaticQueue& other)
    : StaticQueue(other.capacity)
{   
    // Delegating constructor hase finised. The destructor will be called on exception
    for(; size < other.size; ++size)
    {
        data[size] = other.data[(other.head + size) % other.capacity];
    }
}


template<typename T>
StaticQueue<T>& StaticQueue<T>::operator=(const StaticQueue& other)
{
    if(this != &other)
    {
        if(this->capacity < other.size)
        {
            throw std::runtime_error("Not enough capacity!");
        }

        // Weak safety
        size = 0;
        head = 0;

        for(size_t i = 0; i < other.size; ++i)
        {
            enqueue(other.data[(other.head + i) % other.capacity]);
        }
    }

    return *this;
}

template<typename T>
StaticQueue<T>::~StaticQueue() noexcept
{
    clear();
}

template<typename T>
void StaticQueue<T>::clear() noexcept
{
    delete[] data; data = nullptr;
    head = size = capacity = 0;
}

template<typename T>
void StaticQueue<T>::enqueue(const T& el)
{
    if(full()) throw std::length_error("Queue full!");
    
    data[(head + size) % capacity] = el;
    ++size;
}

template<typename T>
T StaticQueue<T>::dequeue()
{
    if(empty()) throw std::length_error("Queue empty!");

    T el = std::move(data[head]);
    head = (head + 1) % capacity;
    --size;

    return el;
}

template<typename T>
T&   StaticQueue<T>::front()
{
    if(empty()) throw std::length_error("Queue is empty!");
    return data[head];
}

template<typename T>
const T&   StaticQueue<T>::front() const
{
    if(empty()) throw std::length_error("Queue is empty!");
    return data[head];
}