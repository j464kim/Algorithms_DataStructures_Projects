#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const & );

		Type retrieve() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	if (this == nullptr) {
		return true;
	}
	return false;
}

template <typename Type>
void Leftist_node<Type>::clear() {
	if(this->empty() || !this) {
		return;
	}
	this->left()->clear();
	this->right()->clear();
	delete this;
}

template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	if (!empty()) {
		return element;
	}
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
	if (!empty()) {
		return left_tree;
	}
	throw underflow();
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
	if (!empty()) {
		return right_tree;
	}
	throw underflow();
}
#endif

template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if (!empty()) {
		return heap_null_path_length;
	}
	return -1;
}

template <typename Type>
int Leftist_node<Type>::count( Type const &obj ) const {
	if (this->empty()) {
		return 0;
	} 
	else {
		if (retrieve() == obj) {
			return 1 + this->left_tree->count( obj ) + this->right_tree->count( obj );
		}
		else {
			return this->left_tree->count( obj ) + this->right_tree->count( obj );
		}
	}
}

template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&old_heap ) {
	// return if new heap doesnt exist
	if (new_heap == nullptr) {
		return;
	}

	// Swap old and new heap if old heap doesnt exist
	if (old_heap == nullptr) {
		old_heap = new_heap;
		return;
	}

	// if root node of old heap is smaller than the root of new heap, push as usual
	else if (old_heap->retrieve() <= new_heap->retrieve()) {
		push( new_heap, old_heap->right_tree );
	}

	// if new heap's root is smaller than the old heap's, swap the two and push
	else if (old_heap->retrieve() > new_heap->retrieve()) {
		std::swap(old_heap, new_heap);
		push(new_heap, old_heap->right_tree);
	}

	// increment the merged null_path_length
	old_heap->heap_null_path_length = 1 + std::min(old_heap->right_tree->null_path_length(), old_heap->left_tree->null_path_length());
	
	// swap the left and right subtree if right side is heavier than the left
	if (old_heap->left()->null_path_length() < old_heap->right()->null_path_length()) {
		std::swap(old_heap->left_tree, old_heap->right_tree);
	}
}

