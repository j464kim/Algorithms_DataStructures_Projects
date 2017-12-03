#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif


#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;
	set_info** sets;
	int set_counter;
	int initial_num_sets;
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]),  
sets (new set_info*[n]),  // nodes = new ll_entry*[n]); sets = new set_info*[n])
set_counter(n),
initial_num_sets(n) {
	// initialize the sets	
	for (int i = 0; i < n; i++) {
		nodes[i] = new ll_entry;
		sets[i] = new set_info;
		nodes[i] -> content = i;
		nodes[i] -> next = nullptr;
		nodes[i] -> ptr_to_info = sets[i];		// points to where it belongs
		sets[i] -> head = nodes[i];
		sets[i] -> tail = nodes[i];
		sets[i] -> size = 1;
	}
	set_counter = n;
}

Disjoint_set::~Disjoint_set() {
	for (int i = 0; i < initial_num_sets; i++) {
		delete nodes[i];
		delete sets[i];
	}
	delete[] sets;
	delete[] nodes;
}
int Disjoint_set::find_set(int item) const{
	// the first node's content in the set represents the entire set
	return nodes[item]->ptr_to_info->head->content; 
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;

	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

	// ni1: the vertex of larger set, ni2: the vertext of the smaller set
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;

	int size1 = nodes[ni1] -> ptr_to_info -> size; // get the large set's size
	int size2 = nodes[ni2] -> ptr_to_info -> size; // get the small set's size

	// create a pointer that points to the first element of the smaller set
	ll_entry* curr = nodes[ni2] -> ptr_to_info -> head;

	// let the last element in larger set point to first element in smaller set
	nodes[ni1] -> ptr_to_info -> tail -> next = nodes[ni2] -> ptr_to_info -> head;

	// set_info's tail points to the last element of small set
	nodes[ni1] -> ptr_to_info -> tail = nodes[ni2] -> ptr_to_info -> tail;

	// update the size of the unioned set (large size + small size)
	nodes[ni1] -> ptr_to_info -> size = size1 + size2;	

	for (int i = 0; i < size2; i++) {
		curr -> ptr_to_info = nodes[ni1] -> ptr_to_info;	// let elements in small set point to the larger set
		curr = curr -> next;		// iterate through the shorter list
	}
	curr = nullptr;					// last element's next points to nullptr

	set_counter--;
	
}


#endif
