#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include <string>
#include <cctype>

class Trie;

class Trie_node {
	private:
		Trie_node **children;
		bool is_terminal;
		static int const CHARACTERS = 26;


	public:
		Trie_node();
		Trie_node *child( int ) const;

		bool member( std::string const &, int ) const;

		bool insert( std::string const &, int );
		bool erase( std::string const &, int, Trie_node *& );
		void clear();

		friend class Trie;

		// if ptr is a pointer to a Trie_node object
		// in one of the friendly classes, you should:
		//    use   ptr->next_   to modify it
		//    use   ptr->next()      to access it
};

Trie_node::Trie_node():
children( nullptr ),
is_terminal( false ) {
	// empty constructor
}

Trie_node *Trie_node::child( int n ) const {
	if ( children == nullptr ) {
		return nullptr;
	} else {
		return children[n];
	}
}

bool Trie_node::member( std::string const &str, int depth ) const {
	
	// convert char to ascii
	char c = str[depth];
    char lower = (tolower(c));
	int index = lower - 'a';

	// false if there is no word at all in trie 
	if (children == nullptr) {
		return false;
	} 
	// false if the next word doesn't exist
	else if (children[index] == nullptr) { 
		return false;
	} 
	// check if the letter reaches the end of word and the is_terminal is true 
	// to see if the word is what we're searching for
	else if (str.length()-1 == depth) { 
		if (children[index] -> is_terminal == true) {
			
			return true;
		} else {
			return false;
		}	
	} 
	// traverse through the letter
	else  {
		return children[index] -> member(str, depth+1);
	}
}

bool Trie_node::insert( std::string const &str, int depth ) {
	
	// convert char to ascii
	char c = str[depth];
    char lower = (tolower(c));
	int index = lower - 'a';

	// create children and initialize it
	if (children == nullptr) {
		children = new Trie_node*[CHARACTERS]();
		for (int i = 0; i < CHARACTERS; i++) {
			children[i] = nullptr;
		}
	}

	// check if the child at the index of letter is NULL
	// if so, create a new node at the index
	if (children[index] == nullptr) { 
		children[index] = new Trie_node();
	}
	
	// set is_terminal to true if it reaches end of word
	if (str.length()-1 == depth) {
		children[index] -> is_terminal = true;
		return children[index] -> is_terminal;
	} else {
		// otherwise ,recursively call the insert
		return children[index] -> insert(str, depth+1);
	}

}

bool Trie_node::erase( std::string const &str, int depth, Trie_node *&ptr_to_this ) {
	// convert char to ascii
	char c = str[depth];
    char lower = (tolower(c));
	int index = lower - 'a';	
	bool nullCheck = true;
	
	if (str.length() != depth || ptr_to_this -> is_terminal != true) {
			children[index] -> erase(str, depth+1, children[index]);
	}

	// when it reached end of word
	
	// check if the node has any other child
	if (children == nullptr) 
	{
		delete ptr_to_this;
		ptr_to_this = nullptr;
	}
	else {
		// set is_terminal to null only for this word. if it repeats again, don't do anything.
		if (str.length() == depth) {
			
			ptr_to_this -> is_terminal = false;
		}
	}
}

void Trie_node::clear() {
	if(children != nullptr){
		for (int i=0; i<CHARACTERS; i++) {
			if(children[i] != nullptr){
				children[i] -> clear();
				delete children[i];
				children[i] = nullptr;
			}
		}
		delete[] children;
		children = nullptr;
	}
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif