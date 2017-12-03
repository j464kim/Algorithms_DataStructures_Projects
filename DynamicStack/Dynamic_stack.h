#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;


class Dynamic_stack {

	private:
		int *array;
		int *newArray;
		int head;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();
};

Dynamic_stack::Dynamic_stack( int n ):
head( -1 ),
count( 0 ),
array_size( n ),
initial_size(n)
{
	array = new int[array_size];
}


Dynamic_stack::~Dynamic_stack() {
	delete [] array;
}


int Dynamic_stack::top() const {
	//If the array has no elements, throw underflow, else return the value at the head.
	if(head < 0)
    {
        throw underflow();
    }

    return array[head];
}


int Dynamic_stack::size() const {
	return count;
}


bool Dynamic_stack::empty() const {
	if (count == 0) {
        return true;
    } else {
        return false;
    }
}


int Dynamic_stack::capacity() const {
	return array_size;
}

void Dynamic_stack::push( int const &obj ) {
	//If the array is full, double the array size
	if(array_size == count) {
		newArray = new int [array_size * 2]; // make a new array of size 2

        for (int i = 0; i < array_size; i++) { // move the elements to the new array
            newArray[i] = array[i];
        }

        delete[] array; // remove the allocated address of the old array
        array = newArray;
		array_size *= 2;
	}

	// push an element to the stack
    head++;
    array[head] = obj;
    count++;
}

int Dynamic_stack::pop() {
	// throw an underflow exception if the stack is empty
	if(count == 0) {
        throw underflow();
    }

    int const result = array[head];
    head--;
    count--;

    return result;
}

void Dynamic_stack::clear() {
	for (int i=0; i<count; i++) {
        array[i] = 0;
    }

    head = -1;
    count = 0;
    return;
}

#endif