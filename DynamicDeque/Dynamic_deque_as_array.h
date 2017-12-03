#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H

#include "Exception.h"

using namespace std;


class Dynamic_deque_as_array

{
    // define member variables
    int* array;
    int* newArray;
    int heads;
    int tails;
    int count;
    int array_size;

public:
    Dynamic_deque_as_array( int = 10 ); // make the array size 10 if it isn't explicitly defined.


    ~Dynamic_deque_as_array();

    // define functions of this class
    int head() const;
    int tail() const;
    int size() const;
    bool empty() const;
    int capacity() const;

    void enqueue_head( const int & );
    void enqueue_tail( const int & );
    int dequeue_head();
    int dequeue_tail();
    void clear();
};


Dynamic_deque_as_array::Dynamic_deque_as_array( int n) { // constructor that initializes member variables

    heads = 0;
    tails = 0;
    count = 0;

    if (n < 1) { // array size less than one is to be one
        array_size = 1;
    }   
    else { // otherwise, it is n
        array_size = n;
    }
    array = new int [array_size]; // create it

}


Dynamic_deque_as_array::~Dynamic_deque_as_array() { 
    delete [] array;
}


int Dynamic_deque_as_array::size() const { // return the number of elements in deq
    return count;
}


int Dynamic_deque_as_array::capacity() const { // return the capacity
    return array_size;
}


bool Dynamic_deque_as_array::empty() const { // return true if it's empty, false otherwise
    if (count == 0) {
        return true;
    } else {
        return false;
    }
}

int Dynamic_deque_as_array::head() const { // return the element in the head
    return array[0];
}


int Dynamic_deque_as_array::tail() const { // return the element in the tail
    return array[count-1];
}

void Dynamic_deque_as_array::enqueue_head( const int &obj ) {  // Heads always points to the first index 
    if (count == 0) { // when the array is empty

    }
    else if (count == array_size) {   // when the arrray is full
        newArray = new int [array_size * 2]; // make a new array of size 2

        for (int i = 0; i < array_size; i++) { // move the element to the new array
            newArray[i] = array[i];
        }
        delete[] array; // remove the allocated address
        array = newArray;
        array_size = array_size*2;

        // shift every element to the right
        for (int i = tails; i >= 0; i--) {
        array[i+1] = array[i];
      }
        
    } 
    else { 
        // shift every element to the right
        for (int i = tails; i >= 0; i--) {
        array[i+1] = array[i];
      }
    }
      
      // input an element into head
      array[heads] = obj;
      count++;
      tails = count-1;
      // cout << "Enqueued Head: " << obj << endl;

    return;
}


void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
    if (count == 0) {

    }
    else if (count == array_size) {   // when the array is full
        newArray = new int [array_size * 2];

        for (int i=0; i<array_size; i++) {
            newArray[i] = array[i];
        }
        delete[] array;
        array = newArray;
        array_size = array_size * 2;
        
    } 
    // input an element into tail    
    array[count] = obj;
    count++;
    tails = count-1 ;
    // cout << "Enqueued Tail: " << obj << endl;

    return;
}


int Dynamic_deque_as_array::dequeue_head() {  // pop one from the head
    if (count == 0) {
        throw underflow();
    }
    int temp = array[0]; 
    // shift every element to the left
    for (int i=0; i<count-1; i++) {
        array[i]=array[i+1];
    }
    tails--;
    count--;
    // cout << "Dequeued Head: " << temp << endl;
    return temp;
}

int Dynamic_deque_as_array::dequeue_tail() { // pop one from the tail
    if (count == 0) {
        throw underflow();
    }
    tails--;
    count--;
    // cout << "Dequeued Tail: " << array[count] << endl;  
    return array[count];
}


void Dynamic_deque_as_array::clear() { // clear the deq

    for (int i=0; i<count; i++) {
        array[i] = 0;
    }
    heads = 0;
    tails = 0;
    count = 0;
    return;
}


#endif
