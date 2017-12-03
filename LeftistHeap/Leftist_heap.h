#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node;
		int heap_size;

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		

		bool empty() const;
		int size() const;
		int null_path_length() const;
		Type top() const;
		int count( Type const & ) const;

		void push( Type const & );
		Type pop();
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

// some sample functions are given

template <typename Type>
Leftist_heap<Type>::Leftist_heap():
root_node( nullptr ),
heap_size( 0 ) {
	// does nothing
}

template<typename Type>
bool Leftist_heap<Type>::empty() const {
	if (heap_size != 0) {
		return false;
	}
	return true;
}

template <typename Type>
void Leftist_heap<Type>::clear() {
	if (root_node != nullptr) {
		root_node->clear();
		root_node = nullptr;
		heap_size = 0;
	}
}

template<typename Type>
int Leftist_heap<Type>::size() const {
	if (heap_size < 0) {
		throw underflow();
	}
	return heap_size;
}

template<typename Type>
Type Leftist_heap<Type>::top() const {
	if (heap_size <= 0) {
		throw underflow();
	}
	return root_node->retrieve();
}

template<typename Type>
int Leftist_heap<Type>::null_path_length() const {
	return root_node->null_path_length();
}

template<typename Type>
int Leftist_heap<Type>::count( const Type &obj ) const {
	return root_node->count(obj);
}

template <typename Type>
void Leftist_heap<Type>::push( Type const &value) {
	Leftist_node<Type> *new_heap = new Leftist_node<Type>(value);
	root_node->push(new_heap, root_node);
	heap_size++;
}

template <typename Type>
Type Leftist_heap<Type>::pop() {
	if (heap_size <= 0) {
		throw underflow();
	}
	// temporarily save the smallest element in the heap and the node which contains the value 
	Type val_to_be_popped = root_node->retrieve();
	Leftist_node<Type> *node_to_be_popped = root_node;

	// left subtree becomes the main heap when the top node is popped
	root_node = node_to_be_popped->left();
	node_to_be_popped->push(node_to_be_popped->right(), root_node);

	delete node_to_be_popped;
	heap_size--;

	return val_to_be_popped;
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

template <typename Type>
Leftist_heap<Type>::~Leftist_heap() {
	clear();  
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}

#endif
