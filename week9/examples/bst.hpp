#pragma once

#include <iostream>
#include <vector>

namespace sdp {

template<typename T>
class bst{
public:

    bst();
    
    bst(const bst& other);
    bst(bst&& other) noexcept;

    bst& operator=(const bst& other);
    bst& operator=(bst&& other) noexcept;

    ~bst() noexcept;

    bool find(const T& elem) {return find(root, elem);}
    void insert(const T& elem) { return insert(root, elem); }
    bool remove(const T& elem) { return remove(root, elem); }

    std::size_t get_size() const { return size; }

    std::size_t get_height()    const  { return height(root);   }
    bool is_balanced()          const  { return balanced(root); }
    bool is_perfectly_balancd() const  { return perfectly_balanced(root); }

    void static_balance();

private:
    struct node
    {
        T data;
        node *left, *right;

        node(const T& data, node *left = nullptr, node *right = nullptr)
            : left(left), right(right), data(data) {}
    } *root;
    
    std::size_t size;

private:

    void clear(node* root) noexcept;
    node* copy(node* root);

    bool find(node* node, const T& elem);
    void insert(node*& root, const T& elem);
    bool remove(node*& root, const T& elem);

    node* extract_min(node*& root);

    std::size_t height(node* root) const;
    std::size_t weight(node* root) const;

    bool        balanced(node* root) const;
    bool        perfectly_balanced(node* root) const;

    void        extract_nodes(node*& root, std::vector<node*>& nodes);
    node*       build_PBT(std::vector<node*>& nodes, std::size_t start, std::size_t end);
};

template<typename T>
bst<T>::bst()
    : root(nullptr), size(0) {}

template<typename T>
bst<T>::bst(const bst& other)
    : root(copy(other.root))
    , size(other.size) {}

template<typename T>    
bst<T>::bst(bst&& other) noexcept
    : bst()
{
    std::swap(root, other.root);
    std::swap(size, other.size);
}

template<typename T>
bst<T>& bst<T>::operator=(const bst& other){

    if(this != &other){
        *this = bst(other);
    }

    return *this;
}

template<typename T>
bst<T>& bst<T>::operator=(bst&& other) noexcept{
    
    if(*this != &other){
        std::swap(root, other.root);
        std::swap(size, other.size);
    }

    return *this;
}

template<typename T>
bst<T>::~bst() noexcept{
    clear(root);
}

template<typename T>
void bst<T>::clear(node* root) noexcept{
    while (root)
    {
        clear(root->left);
        clear(root->right);

        delete root; root = nullptr;
    }
}

template<typename T>
typename bst<T>::node* bst<T>::copy(node* root) {

    while (root)
    {
        node* res = new node(root->data);

        try
        {
            res->left = copy(root->left);
            res->left = copy(root->right);
        }
        catch(const std::exception& e)
        {
            clear(res);
            throw;
        }

        return res;
    }
    
}

template<typename T>
bool bst<T>::find(node* node, const T& elem){

    if(!root) return false;
    if(root->data == elem) return true;
    
    return elem < node->data
    ? find(node->left, elem)
    : find(node->right, elem);
}

template<typename T>
void bst<T>::insert(node*& root, const T& elem){
    if(!root) root = new node(elem);
    else insert(elem < root->data ? root->left : root->right, elem);
}

template<typename T>
bool bst<T>::remove(node*& root, const T& elem){
    if(!root) return false;

    if(root->data == elem){
        node *to_delete = root;

        if(!root->right)        root = root->left;
        else if (!root->left)   root = root->right;
        else{
            node* min = extarct_min(root->right);
            min->left = root->left;
            min->right = root->right;
            root = min;
        }

        delete to_delete;
    }
    else {
        remove(elem < root->left ? root->left : root->right, elem);
    }
}

template<typename T>
typename bst<T>::node* bst<T>::extract_min(node*& root){
    if(root->left) return extract_min(root->left);

    node* res = root;
    root = root->right;
    return res;
}

template<typename T>
std::size_t bst<T>::height(node* root) const{
    if(!root) return 0;
    return 1 + std::max(height(root->left), height(root->right));
}

template<typename T>
std::size_t bst<T>::weight(bst<T>::node* root) const
{
    if (!root) return 0;
    return 1 + weight(root->left) + weight(root->right);
}

template<typename T>
bool bst<T>::balanced(node* root) const{
    if(!root) return true;

    return std::abs(height(root->left) - height(root->right)) < 2 &&
           balanced(root->left) && balanced(root->right);
}

template<typename T>
bool bst<T>::perfectly_balanced(node* root) const{
    if(!root) return true;

    return 
    std::abs(weight(root->left), weight(root->right)) &&
    perfectly_balanced(root->left) && perfectly_balanced(root->right);
}

template<typename T>
void bst<T>::static_balance(){

    if(!root){
        std::vector<node*> nodes_sorted;
        extract_nodes(root, nodes_sorted);
        root = build_PBT(nodes_sorted, 0, nodes_sorted.size());
    }
}

template<typename T>
void bst<T>::extract_nodes(node*& root, std::vector<node*>& nodes){

    if(root){
        extract_nodes(root->left, nodes); 
        nodes.push_back(root);
        extract_nodes(root->right);
    }
    
}

template<typename T>
typename bst<T>::node* bst<T>::build_PBT(std::vector<node*>& nodes, std::size_t start, std::size_t end){

    std::size_t mid = start + (end - start) / 2;
    node* root = nodes[mid];

    root->left = build_PBT(nodes, 0, mid);
    root->left = build_PBT(nodes, mid + 1, end);

    return root;
}

}
