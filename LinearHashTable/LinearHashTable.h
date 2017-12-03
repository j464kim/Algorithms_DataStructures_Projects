#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

#include "Exception.h"

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
	private:
		int count;
		int power;
		int array_size;
        	int mod;
       	int m;
		T *array;
		state *array_status;

	public:
		LinearHashTable( int = 5 ); // make the constructor size 5 if it isn't explicitly defined.
		~LinearHashTable();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;


		void insert( T const & );
		bool remove( T const & );
		void clear();
		void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( m ): // constructor
array_size( 1 << power ){
	array_size = 2^m;
	array = new int[array_size];
	array_status = new int[array_size];
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {  // destructor
	delete[] array;
	delete[] array_status;
}

template<typename T >
int LinearHashTable<T >::size() const {
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
	return count / array_size;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
    if (count == 0) {
    	return true;
    } else {
    	return false;
    }
}

template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
	for (int i=0; i<array_size; i++) {
		if (obj == array[i]) {
			return true;
		} 
	} 
	return false;
}

template<typename T >
T LinearHashTable<T >::bin( int index ) const {
	return array[index];
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
	mod = obj % array_size;
	loadF = count / array_size;

	if (loadF > 0.75) { // if load factor is greater than 0.75
		newArray = new int [array_size * 2]; // double the size
        for (int i = 0; i < array_size; i++) { // rehash all elements
        	if (array_status[i] != EMPTY) {
        		item = array[i];
        		newMod = item % array_size*2;
        		newArray[newMod] = item;
        	}
        }
        delete[] array; // remove the allocated address
        array = newArray;
        array_size = array_size*2;

        while (array_status[mod] != EMPTY) {
			mod++;
			mod = mod % array_size;
		} array[mod] = obj;
    }
    while (array_status[mod] != EMPTY) { // find the next available spot if the bin isn't empty
		mod++;
		mod = mod % array_size;
	} array[mod] = obj;
}


template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {
	loadF = count / array_size;

	if (loadF < 0.25) { // if the load factor is less than 0.25
		if (array_size != 2^m ) {
			newArray = new int [array_size / 2]; // shrink the size by half
			for (int i=0; i<array_size; i++) { // rehash all elements
				item = array[i];
				newMod = item % array_size/2;
				newArray[newMod] = item;
			}
			delete[] array; // remove the allocated address
	        array = newArray;
	        array_size = array_size/2;
		}
	}
	for (int i=0; i<array_size; i++) {
		if (array[i] == obj) {
			array[i] = 0;
			array_status[i] = DELETED;
			return;
		}
	} return false;
}

template<typename T >
void LinearHashTable<T >::clear() {
	for (int i=0; i<array_size; i++) {
		array[i] = 0;
	}
}

template<typename T >
void LinearHashTable<T >::print() const{
	cout << "{ ";
	for (int i=0; i<array_size; i++) {
		cout << array[i] << ", ";
	}
	cout << " }";
}

#endif