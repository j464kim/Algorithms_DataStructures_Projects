#ifndef TRIE_H
#define TRIE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Trie_node.h"
#include "Exception.h"
#include <iostream>
#include <string>
#include <cctype>

class Trie {
	private:
		Trie_node *root_node;
		int trie_size;

	public:
		Trie();
		~Trie();

		// Accessors

		int size() const;
		bool empty() const;
		bool member( std::string const & ) const;
		Trie_node *root() const;
		// Mutators

		bool insert( std::string const & );
		bool erase( std::string const & );
		void clear();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Trie const & );
};

Trie::Trie():
root_node( nullptr ),
trie_size( 0 ) {
	// empty constructor
}

Trie::~Trie() {
	clear();
}

int Trie::size() const {
	return trie_size;
}

bool Trie::empty() const {
	if (trie_size == 0) {
		return true;
	}
	else {
		return false;
	}
}

Trie_node *Trie::root() const {
	return root_node;
}

bool Trie::member( std::string const &str ) const {
	for (int i = 0; i < str.length(); i++) {
		if (!isalpha(str[i])) {
			throw illegal_argument();
		}
	}
	// false if there is no root node
    if (root_node == nullptr) { 
		return false;
	} else {
		return root_node -> member(str, 0);
	} 
}

bool Trie::insert( std::string const &str ) {

    if (member(str)) {
		return false;
	} else { 
	 	// create a root node if there isn't
		if (root_node == nullptr) {
			root_node = new Trie_node();
		}
		// call the insert of Trie_node.
		root_node -> insert(str, 0); 
		trie_size++;
		return true;
	}
}

bool Trie::erase( std::string const &str ) {
	
	if (member(str)) {
		root_node -> erase(str, 0, root_node);
		trie_size--;
		return true;
	} else {
		return false;
	}
}

void Trie::clear() {
	if (root_node == nullptr) {
		return;
	} else {
		root_node -> clear();
		trie_size = 0;
		delete root_node;
		root_node = nullptr;
	}
}

// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Trie const &trie ) {

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif