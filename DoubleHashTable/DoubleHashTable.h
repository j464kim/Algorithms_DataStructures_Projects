
#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

#include "Exception.h"

using namespace std;

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array[i] = 0;
	}

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	delete[] array;
	delete[] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    // Return true if the hash table is empty, false .otherwise
    if (size() == 0) {
    	return true;
    } else {
    	return false;
    }
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {

	int valueToInsert = static_cast<int>(obj); 
	int firstHashNum = valueToInsert % array_size; 

	if (firstHashNum < 0) {
		firstHashNum = firstHashNum + array_size;
	}

	return firstHashNum;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {

	int valueToInsert = static_cast<int>(obj); 
	int secondHashNum = (valueToInsert/array_size) % array_size; 

	if (secondHashNum < 0) {
		secondHashNum = secondHashNum + array_size;
	}

	if (secondHashNum % 2 == 0) {
		secondHashNum++;
	}

	return secondHashNum;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	// Return true if object obj is in the hash table and false otherwise 
	// use hashing for constant time
	int hashNum1 = h1(obj);
	int hashNum2 = h2(obj);

	int collision = 0;
	int doubleHashNum = 0;

	do {
		doubleHashNum = (hashNum1 + collision*hashNum2) % array_size;
		collision++;

		if (array[doubleHashNum] == obj && array_state[doubleHashNum] == OCCUPIED) {
			return true;
		}

	} while ( 
		// # times of probing doesnt exceed the array size
		// if the index is empty, it means the element doesnt exsit 
		collision < array_size && array_state[doubleHashNum] != EMPTY 
		);

	return false;

}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {          
  	// checks n is within the range of array
	if (n < 0||n >= array_size)
	{
  		throw ArrayBoundsException(); 
	}

	T object = array[n];    
	
	return T(object);
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	// Insert the new object into the hash table in the appropriate bin
	// If the table is full, throw an overflow exception
	if (count == array_size) {
		throw overflow();
	}
 	
	int hashNum1 = h1(obj);
	int hashNum2 = h2(obj);

	int collision = 0;
	int doubleHashNum = 0;

	do {
		doubleHashNum = (hashNum1 + collision*hashNum2) % array_size;
		collision++;
	} while (array_state[doubleHashNum] == OCCUPIED);

	// empty bin is found
	array[doubleHashNum] = obj;
	array_state[doubleHashNum] = OCCUPIED;
	count++;

  	return ; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 // Remove the object from the hash table if it is in the hash table 
	 // (returning false if it is not) by setting the corresponding flag of the bin to deleted.

	int hashNum1 = h1(obj);
	int hashNum2 = h2(obj);

	int collision = 0;
	int doubleHashNum = 0;

	do {
		doubleHashNum = (hashNum1 + collision*hashNum2) % array_size;
		collision++;

		if (array[doubleHashNum] == obj && array_state[doubleHashNum] == OCCUPIED) {
			// found an element to be deleted
			array[doubleHashNum] = 0;
			array_state[doubleHashNum] = DELETED;
			count--;

			return true;
		}

	} while ( 
		// # times of probing doesnt exceed the array size
		// if the index is empty, it means the element doesnt exsit 
		collision < array_size && array_state[doubleHashNum] != EMPTY 
		);

	return false;

}

template<typename T >
void DoubleHashTable<T >::clear() {
	 // Remove all the elements in the hash table.
	 for (int i = 0; i < array_size; i++) {
	 	// clear array
	 		array[i] = 0;
	 	// clear array_state
	 		array_state[i] = EMPTY;
	 }	
	 count = 0;

	 return; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
	cout << "Stack: ";
	for (int i=0; i<array_size; i++) {
		cout << array[i] << " ";
	}
	cout << endl;

	cout << "Stack State: ";
	for (int i=0; i<array_size; i++) {
		cout << array_state[i] << " ";
	}
	cout << endl;

	cout << "count: " << size() << endl;
	cout << "power: " << power << endl;
	cout << "array_size: " << capacity() <<endl;
	return;
}

#endif