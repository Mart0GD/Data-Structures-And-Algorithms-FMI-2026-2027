#ifndef __LCRS_HPP_INCLUDED__
#define __LCRS_HPP_INCLUDED__

#include <string>
#include <stdexcept>
#include <assert>

namespace sdp
{
    template<typename T>
    class LcRs
    {
	struct node
	{
	    T data;
	    node *left, *right;

	    node(const T& data, node *left = nullptr, node *right = nullptr) : data(data), left(left), right(right) {};
	};
	
    public:
	LcRs();

	LcRs(const LcRs&);
	LcRs& operator=(const LcRs&);

	LcRs(LcRs&&) noexcept;
	LcRs& operator=(LcRs&&) noexcept;

	~LcRs() noexcept;

	void insert(const T& el, const char* path = "/");
	void remove(const T& el);

	bool find(const T& el);

	class BFS_Iterator;

	BFS_Iterator begin() { return BFS_Iterator(root); } 
	BFS_Iterator end()   { return BFS_Iterator(nullptr); }

	class DFS_Iterator;

	DFS_Iterator begin() { return DFS_Iterator(root); } 
	DFS_Iterator end()   { return DFS_Iterator(nullptr); }
	
    private:
	node* root;

	node* copy(node* n);
	void clear();

	void remove(node*& n, const T& el);
	void insert(node*& n, const T& el, const char* path);
    };

    template<typename T>
    class LcRs<T>::BSF_Iterator
    {
	friend class LcRs<T>;
	node* itt;

	BFS_Iterator(node* ptr) : itt(ptr) {};
    public:

	BFS_Iterator& operator ++ ();		   
	BFS_Iterator  operator ++ (int);

	bool operator == (const BFS_Iterator& other);
	bool operator != (const BFS_Iterator& other);

	T&   operator *   () { return itt->data;}
	T*   operator ->  () { return &itt->data;}
    }


    template<typename T>
    class LcRs<T>::BSF_Iterator
    {

    }

    #include "LcRs.inl"
};

#endif
