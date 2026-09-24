
template<typename T>
StaticStack<T>::StaticStack(size_t capacity)
    : data(nullptr)
    , tos(0)
    , size(capacity)
{
    if(capacity == 0)
    {
        throw std::invalid_argument("Invalid capacity!");
    }

    data = new T[size];
}

template<typename T>
StaticStack<T>::StaticStack(const StaticStack& other)
    : StaticStack(other.size)
{
    try
    {
        while(tos < other.tos)
        {
            push(other.data[tos]);
        }
    }
    catch(...)
    {
        clear();
        throw;
    }
}   

template<typename T>
StaticStack<T>& StaticStack<T>::operator=(const StaticStack& other)
{
    if(this != &other)
    {
        if(size < other.tos)
        {
            throw std::runtime_error("Not enough space!");
        }

        tos = 0;
        while(tos < other.tos)
        {
            push(other.data[tos]);
        }
    }

    return *this;
}

template<typename T>
StaticStack<T>::~StaticStack() noexcept
{
    clear();
} 

template<typename T>
void StaticStack<T>::push(const T& element)
{
    if(full())
    {
        throw std::overflow_error("Stack overflow!");
    }

    data[tos] = element;
    ++tos;
}

template<typename T>
void StaticStack<T>::push(T&& element)
{
    if(full())
    {
        throw std::overflow_error("Stack overflow!");
    }

    data[tos] = std::move(element);
    ++tos;
}

template<typename T>
T StaticStack<T>::pop()
{
    if(empty())
    {
        throw std::underflow_error("Stack underflow!");
    }

    T el = std::move(data[tos - 1]);
    --tos;

    return el; // RVO
}

template<typename T>
void StaticStack<T>::clear() noexcept
{
    delete[] data; 
    data = nullptr;
}

