
template<typename T>
dllist<T>::dllist()
{
    // Ouroboros (;
    sentinel.next = &sentinel;
    sentinel.prev = &sentinel;
}

template<typename T>
dllist<T>::dllist(const dllist& other)
    : dllist()
{
    copy(other);
}

template<typename T>
dllist<T>& dllist<T>::operator=(const dllist& other)
{
    if(this != &other)
    {
        dllist tmp = other;
        *this = std::move(tmp);
    }

    return *this;
}

template<typename T>
dllist<T>::dllist(dllist&& other) noexcept
    : dllist()
{
    if(!other.empty())
    {
        sentinel.next = other.sentinel.next;
        sentinel.prev = other.sentinel.prev;

        sentinel.next->prev = sentinel.prev->next = &sentinel;
        other.sentinel.next = other.sentinel.prev = &other.sentinel;
    }

}

template<typename T>
dllist<T>& dllist<T>::operator=(dllist&& other) noexcept
{
    if(this != &other)
    {
        clear();

        if(!other.empty())
        {
            sentinel.next = other.sentinel.next;
            sentinel.prev = other.sentinel.prev;

            sentinel.next->prev = sentinel.prev->next = &sentinel;
            other.sentinel.next = other.sentinel.prev = &other.sentinel;
        }
        
        // --- Second Variant ---

        /*
        node* otherNext = other.sentinel.next;
        node* otherPrev = other.sentinel.prev;
        bool isOtherEmpty = other.empty();

        if(!empty())
        {
            // steal the sentinel
            other.sentinel.next = sentinel.next;
            other.sentinel.prev = sentinel.prev;

            other.sentinel.next->prev = other.sentinel.prev->next = &other.sentinel;
        }
        else
        {
            // empty
            other.sentinel.next = other.sentinel.prev = &other.sentinel;
        }

        if(!isOtherEmpty)
        {
            // steal from the copy
            sentinel.next = otherNext;
            sentinel.prev = otherPrev;

            sentinel.next->prev = sentinel.prev->next = &sentinel;
        }
        else
        {
            // empty
            sentinel.next = sentinel.prev = &sentinel;
        }
        */
    }

    return *this;
}

template<typename T>
dllist<T>::~dllist() noexcept
{
    clear();
}

template<typename T>
void dllist<T>::copy(const dllist& other)
{   
    assert(empty());

    node *itt = &sentinel;
    node *curr = other.sentinel.next;

    while(curr != &other.sentinel)
    {
        try
        {
            itt->next = new node(curr->data, itt, &sentinel);
        }   
        catch(...)
        {
            clear();
            throw;
        }

        itt = itt->next;
        curr = curr->next;
    }

    sentinel.prev = itt;
}

template<typename T>
void dllist<T>::clear() noexcept
{
    while(sentinel.next != &sentinel)
    {
        node *toDel = sentinel.next;
        sentinel.next = toDel->next;

        delete toDel;
    }

    sentinel.next = sentinel.prev = &sentinel;
}

template<typename T>
void dllist<T>::pushFront(const T& el)
{
    pushAfter(end(), el);
}

template<typename T>
void dllist<T>::pushBack(const T& el)
{
    pushBefore(end(), el);
}

template<typename T>
void dllist<T>::pushBefore(BidirectionalIterator itt, const T& el)
{
    node *n = new node(el, itt.ptr->prev, itt.ptr);
    n->prev->next = n;
    n->next->prev = n; 
}

template<typename T>
void dllist<T>::pushAfter(BidirectionalIterator itt, const T& el)
{
    node *n = new node(el, itt.ptr, itt.ptr->next);
    n->prev->next = n;
    n->next->prev = n; 
}

template<typename T>
void dllist<T>::popFront()
{
    popAfter(end());
}

template<typename T>
void dllist<T>::popBack()
{
    popBefore(end());
}

template<typename T>
void dllist<T>::popBefore(BidirectionalIterator itt)
{
    if(empty()) throw std::underflow_error("List is empty!");
    if(itt.ptr->prev == &sentinel) throw std::runtime_error("No element before!");

    node *keep = itt.ptr->prev;
    itt.ptr->prev = keep->prev;
    itt.ptr->prev->next = itt.ptr;

    delete keep;
}

template<typename T>
void dllist<T>::popAfter(BidirectionalIterator itt)
{
    if(empty()) throw std::underflow_error("List is empty!");
    if(itt.ptr->next == &sentinel) throw std::runtime_error("No next element!");

    node *keep = itt.ptr->next;
    itt.ptr->next = keep->next;
    itt.ptr->next->prev = itt.ptr;

    delete keep;    
}

template<typename T>
T& dllist<T>::front()
{
    if(empty()) throw std::underflow_error("List is empty!");
    return sentinel.next->data;
}

template<typename T>
const T& dllist<T>::front() const
{
    if(empty()) throw std::underflow_error("List is empty!");
    return sentinel.next->data;
}

template<typename T>
T& dllist<T>::back()
{
    if(empty()) throw std::underflow_error("List is empty!");
    return sentinel.prev->data;
}

template<typename T>
const T& dllist<T>::back() const
{
    if(empty()) throw std::underflow_error("List is empty!");
    return sentinel.prev->data;
}