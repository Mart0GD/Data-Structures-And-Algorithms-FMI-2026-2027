
template<typename T>
LinkedStack<T>::LinkedStack(const LinkedStack& other)
    : tos(nullptr)
{
    copy(tos);
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack& other)
{
    if(this != &other)
    {
        LinkedStack copy = other;
        *this = std::move(copy);
    }

    return *this;
}

template<typename T>
LinkedStack<T>::LinkedStack(LinkedStack&& other)
    : tos(nullptr) 
{
    std::swap(other.tos, tos);
}

template<typename T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack&& other)
{
    if(this != &other)
    {
        std::swap(tos, other.tos);
    }

    return *this;
}

template<typename T>
LinkedStack<T>::~LinkedStack() noexcept
{
    clear(tos);
}

template<typename T>
void LinkedStack<T>::push(const T& el)
{
    node* new_node = new node(el, tos);
    tos = new_node;
}

template<typename T>
void LinkedStack<T>::pop()
{
    if(empty())
    {
        throw std::underflow_error("Stack is empty!");
    }

    node* tmp = tos;
    tos = tos->next;

    delete tmp;
}

template<typename T>
T& LinkedStack<T>::top()
{
    if(empty())
    {
        throw std::underflow_error("Stack is empty!");
    }

    return tos->data;
}

template<typename T>
void LinkedStack<T>::clear(node*& n) noexcept
{
    while (n)
    {
        node* toDel = n;
        n = n->next;

        delete toDel;
        toDel = nullptr;
    }
}

template<typename T>
LinkedStack<T>::node* LinkedStack<T>::copy(const node* n)
{
    if(!n) return nullptr;

    node* curr = new node(n->data);

    try
    {
        curr->next = copy(n->next);
    }
    catch(...)
    {
        delete curr;
        throw;
    }
    
    return curr;
}

template<typename T>
void LinkedStack<T>::copy(const LinkedStack<T>& other)
{
    assert(!tos);

    node sentinel;

    node* itt = &sentinel;
    node* copy_itt = other.tos;

    while (copy_itt)
    {
        try
        {
            itt->next = new node(copy_itt->data, nullptr);
        }
        catch(...)
        {
            clear(sentinel.next);
            throw;
        }
        
        itt = itt->next;
        copy_itt = copy_itt->next;
    }
    
    tos = sentinel.next;
}