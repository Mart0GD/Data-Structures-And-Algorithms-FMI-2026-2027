
template<typename T>
flist<T>::flist(const flist& other)
    : flist()
{
    copy(other);
}

template<typename T>
flist<T>& flist<T>::operator=(const flist& other)
{
    if(this != &other)
    {
        // Copy and swap 
        flist<T> copy = other;
        *this = std::move(copy);
    }

    return *this;
}

template<typename T>
flist<T>::flist(flist&& other) noexcept
    : flist()
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template<typename T>
flist<T>& flist<T>::operator=(flist&& other) noexcept
{
    if(this != &other)
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }

    return *this;
}

template<typename T>
flist<T>::~flist() noexcept
{
    clearMemory(head);
    head = tail = nullptr;
}

template<typename T>
void flist<T>::clearMemory(node*& n)
{
    while(n)
    {
        node* to_del = n;
        n = n->next;

        delete to_del;
        to_del = nullptr;
    }
}

template<typename T>
void flist<T>::copy(const flist& other)
{
    // Copy only an empty list
    assert(head == nullptr && tail == nullptr);

    node* new_head = nullptr;
    node* new_tail = nullptr;

    try
    {
        for (node* itt = other.head; itt; itt = itt->next)
        {
            node* n = new node(itt->data);

            if(!new_head) new_head = n;
            if(new_tail) new_tail->next = n;

            new_tail = n;
        }
    }
    catch(...)
    {
        clearMemory(new_head);
        new_head = new_tail = nullptr;
        throw;
    }
    
    head = new_head;
    tail = new_tail;
}

template<typename T>
void flist<T>::pushFront(const T& el)
{
    node* n = new node(el, head);

    if(empty()) head = tail = n;
    else        head = n;
}

template<typename T>
void flist<T>::pushBack(const T& el)
{
    node* n = new node(el);

    if(empty()) head = n;
    else        tail->next = n;

    tail = n;
}

template<typename T>
void flist<T>::pushAfter(ForwardIterator& itt, const T& el)
{
    if(!itt) throw std::invalid_argument("Invalid iterator!");

    //   # 
    // * -> *   -->  * -> # -> *
    node* n = new node(el, itt.ptr->next);
    itt.ptr->next = n;

    if(itt.ptr == tail) tail = n;
}

template<typename T>
void flist<T>::pushAt(size_t pos, const T& el)
{
    if(pos == 0) pushFront(el);
    else
    {
        node* itt = head;
        for(size_t i = 0; i < pos - 1 && itt; ++i, itt = itt->next);

        if(itt == nullptr) throw std::out_of_range("Invalid index!");

        node* n = new node(el, itt->next);
        itt->next = n;

        if(itt == tail) tail = n;
    }
}

template<typename T>
T flist<T>::popFront()
{
    if(empty()) throw std::runtime_error("List is empty!");

    T el = std::move(head->data);

    node* to_del = head;
    head = head->next;

    if(!head) head = tail = nullptr;

    delete to_del;
    return el;
}

template<typename T>
T flist<T>::popBack()
{
    if(empty()) throw std::runtime_error("List is empty!");

    node* prev = head;
    node* itt = head;
    for(; itt->next; prev = itt, itt = itt->next);

    prev->next = nullptr;
    tail = prev;

    T el = std::move(itt->data);

    if(prev == itt) head = tail = nullptr;

    delete itt;
    return el;
}

template<typename T>
T flist<T>::popAfter(ForwardIterator& itt)
{
    if(!itt) throw std::invalid_argument("Invalid iterator!");
    if(!itt.ptr->next) throw std::out_of_range("Invalid position!");

    node* keep = itt.ptr->next;
    itt.ptr->next = keep->next;
    if(keep == tail)
    {
        tail = itt.ptr;
    }

    T el = std::move(keep->data);
    delete keep;
    return el;
}

template<typename T>
T flist<T>::popAt(size_t pos)
{
    if(empty()) throw std::runtime_error("List is empty!");

    if(pos == 0) return popFront();
    else
    {
        node* prev = nullptr;
        node* curr = head;
        for(size_t i = 0; i < pos && curr; prev = curr, curr = curr->next, ++i);

        if(!curr) throw std::out_of_range("Index out of bounds!");

        prev->next = curr->next;
        T el = std::move(curr->data);

        delete curr;
        return el;
    }
}

template<typename T>
const T& flist<T>::front() const
{
    if(empty()) throw std::runtime_error("List is empty!");
    return head->data;
}

template<typename T>
const T& flist<T>::back()  const
{
    if(empty()) throw std::runtime_error("List is empty!");
    return tail->data;
}

template<typename T>
const T& flist<T>::at(size_t index) const
{
    if(empty()) throw std::runtime_error("List is empty!");

    node* itt = head;
    for(size_t pos = 0; pos < index && itt; ++pos, itt = itt->next);

    if(itt == nullptr) throw std::out_of_range("Index out of bounds!");
    return itt->data;
}

template<typename T>
void flist<T>::append(flist other)
{
    if(other.empty()) return;

    if(empty()) *this = std::move(other);
    else
    {
        tail->next = other.head;
        tail = other.tail;

        other.head = other.tail = nullptr;
    } 
}

template<typename T>
void flist<T>::sortInplace()
{   
    if(empty()) return;

    const size_t buffer_size = sizeof(size_t) * 8;

    /*
        Each buffer node holds 2^i nodes
        cannot index more than 2^64 for normal 8 byte integers (longs)
    */
    node* buffer[buffer_size]{};
    node* res = head;
    node* next = nullptr;
    size_t i;

    while(res != nullptr)
    {
        next = res->next;
        res->next = nullptr;

        for(i = 0; (i < buffer_size) && (buffer[i] != nullptr); ++i)
        {
            res = merge(res, buffer[i]);
            buffer[i] = nullptr;
        }

        buffer[i] = res;
        res = next;
    }
    
    for (size_t i = 0; i < buffer_size ; i++)
    {
        if(buffer[i] == nullptr) continue;

        res = merge(res, buffer[i]);
    }

    head = res;
    fixTail(); // O(n)
}

template<typename T>
void flist<T>::sort()
{
    head = mergeSort(head);
    fixTail();
}

template<typename T>
typename flist<T>::node* flist<T>::mergeSort(node* n)
{
    if(!n || !n->next) return n;

    node *left = n;
    node *right = split(left);
    return merge(mergeSort(left), mergeSort(right));
}

template<typename T>
typename flist<T>::node* flist<T>::split(node* n)
{
    node* slow = n;
    node* fast = n->next;
    while(fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    node* ret = slow->next;
    slow->next = nullptr;
    return ret;
}

template<typename T>
typename flist<T>::node* flist<T>::merge(node* n1, node* n2)
{
    node sentinel;
    node* itt = &sentinel;

    while(n1 && n2)
    {
        if(n1->data < n2->data)
        {
            itt->next = n1;
            n1 = n1->next;
            
        }
        else
        {
            itt->next = n2;
            n2 = n2->next;
        }

        itt = itt->next;
    }

    if(n1)  itt->next = n1;
    else    itt->next = n2;

    return sentinel.next;
}

template<typename T>
void flist<T>::fixTail()
{
    if(head == nullptr) 
    {
        head = tail = nullptr;
        return;
    }

    node* itt = head;
    for(;itt->next; itt = itt->next);

    tail = itt;
}

template<typename T>
void flist<T>::reverse()
{
    if(empty()) return;

    node* prev = nullptr;
    node* curr = head;

    while(curr)
    {
        node* tmp = prev;
        prev = curr;
        curr = curr->next;

        prev->next = tmp;
    }

    tail = head;
    head = prev;
}