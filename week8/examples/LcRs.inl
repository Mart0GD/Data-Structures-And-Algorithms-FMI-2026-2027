

template<typename T>
LcRs<T>::LcRs()
    : root(nullptr) {}

template<typename T>
LcRs<T>::(const LcRs& other)
    : LcRs()
{
   root = copy(other);
}

template<typename T>
LcRs<T>& LcRs<T>::operator=(const LcRs& other)
{
    if(this != &other)
    {
        LcRs copy = other;
	*this = std::move(copy);
    }

    return *this;
}

template<typename T>
LcRs<T>& LcRs<T>::operator = (T&& other)
{

    if(this != &other)
    {
        
    }
    
    return *this;
}



template<typename T>
void copy(node* n)
{
    if(!n) return nullptr;

    node *curr = new node(n->data);

    try
    {
        curr->left = copy(n->left);
	curr->right = copy(n->right);
    }
    catch(...)
    {
        clear(curr);
	throw;
    }

    return curr;
}
