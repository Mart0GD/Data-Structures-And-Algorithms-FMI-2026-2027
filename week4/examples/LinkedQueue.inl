#include "LinkedQueue.hpp"
using namespace sdp;

template<typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& other)
    : head(nullptr)
    , tail(nullptr)
{
    copy(other);
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue& other)
{
    if(this != &other)
    {
        LinkedQueue copy = other;
        *this = std::move(copy);
    }

    return *this;
}

template<typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue&& other) noexcept
{
    if(this != &other)
    {
        std::swap(head, other.head);
        std::swap(tail, other.tail);
    }
    
    return *this;
}

template<typename T>
LinkedQueue<T>::LinkedQueue(LinkedQueue&& other) noexcept
    : head(nullptr)
    , tail(nullptr) 
{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

template<typename T>
LinkedQueue<T>::~LinkedQueue() noexcept
{
    clear(head);
    head = tail = nullptr;
}

template<typename T>
void LinkedQueue<T>::copy(const LinkedQueue& other)
{
    node* new_head = nullptr;
    node* new_tail = nullptr;

    try
    {
        for(node* itt = other.head; itt; itt = itt->next)
        {
            node* n = new node(itt->data);
            if(new_tail) new_tail->next = n;
            else         new_head = n;
            new_tail = n; 
        }
    }
    catch(...)
    {
        clear(new_head);
        throw;
    }
    
    head = new_head;
    tail = new_tail;
}


template<typename T>
void LinkedQueue<T>::clear(node*& head) noexcept
{
    while (head)
    {
        node* to_del = head;
        head = head->next;

        delete to_del;
        to_del = nullptr;
    }

    head = nullptr;
}

template<typename T>
void LinkedQueue<T>::enqueue(const T& el)
{
    node* new_el = new node(el);

    // first element
    if(!head)
    {
        head = tail = new_el;
    }
    else
    {
        tail->next = new_el;
        tail = new_el;
    }
}

template<typename T>
T LinkedQueue<T>::dequeue()
{
    if(empty()) throw std::length_error("Queue is empty!");

    T el = std::move(head->data);

    node* to_del = head;
    head = head->next;

    // Last element 
    if(head == nullptr)  tail = nullptr;

    delete to_del; to_del = nullptr;
    return el; // RVO
}

template<typename T>
T& LinkedQueue<T>::front()
{
    if(empty()) throw std::length_error("Queue is empty!");
    return head->data;
}

template<typename T>
const T& LinkedQueue<T>::front() const
{
    if(empty()) throw std::length_error("Queue is empty!");
    return head->data;
}