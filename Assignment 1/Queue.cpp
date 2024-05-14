/* 
 * Queue.cpp
 *
 * Description: Array-based implementation of Queue as an ADT class
 * Class Invariant: Queue maintained in FIFO order
 *
 * Author: Asheesh Yadav + Eshaan Virk 
 * Date: February 16, 2024
 */

#include "Queue.h" //include the header file
#include <algorithm> //include the algorithm library

// Description: Constructor
Queue::Queue() {

    //initialize the queue variables
    elementCount = 0;
    capacity = INITIAL_CAPACITY;
    frontindex = 0;
    backindex = 0;
    elements = new int[capacity];

}
// Description: Destructor
Queue::~Queue() {

    //delete the elements array
    delete[] elements;
    elements = nullptr;
}
// Description: Copy constructor
Queue::Queue(const Queue& other) {

    //copy the other queue's elements into the new queue
    elementCount = other.elementCount;
    capacity = other.capacity;
    frontindex = other.frontindex;
    backindex = other.backindex;
    elements = new int[capacity];

    //copy the elements into the new array
    for (int i = 0; i < capacity; ++i) {
    elements[i] = other.elements[i];
    }

}

// Description: Overloaded assignment operator
Queue& Queue::operator=(const Queue& other) {

    //check if the queue is being assigned to itself
    if (this != &other) {
        
        //delete the old array
        delete[] elements;
        elements = nullptr;

        //copy old queue's elements into the new queue
        elementCount = other.elementCount;
        capacity = other.capacity;
        frontindex = other.frontindex;
        backindex = other.backindex;
        elements = new int[capacity];

        //copy the elements into the new array
        for (int i = 0; i < capacity; ++i) {
            elements[i] = other.elements[i];
        }
    }
    return *this;
}

//Description: Resizes the array to the new capacity
//Time Efficiency: O(n)
void Queue::resizeArr(int newCapacity) {

    //create a new array with the new capacity
    int* newElements = new int[newCapacity]; 
    
    //copy elements into new array
    for (unsigned int i = 0; i < elementCount; i++)
        newElements[i] = elements[(frontindex + i) % capacity];
    
    //delete the old array and assign the new array to the elements pointer
    delete[] elements;
    elements = newElements;
    capacity = newCapacity;
    frontindex = 0;
    backindex = elementCount;
}

// Description: Inserts newElement at the back of Queue
// Time Efficiency: O(1)
void Queue::enqueue(int newElement) {

    //if queue is full double the capacity
    // and copy the elements into the new array
    if (elementCount == capacity) {
    resizeArr(capacity * 2);
    }

    //insert the new element at the back of the queue
    elements[backindex] = newElement;
    backindex = (backindex + 1) % capacity;

    //up the countr 
    elementCount++; 

}

// Description: Removes the frontmost element
// Precondition: Queue not empty
// Time Efficiency: O(1)
void Queue::dequeue() {
    
    //decrement the count
    elementCount--;

    //remove the frontmost element
    frontindex = (frontindex + 1) % capacity;
    
    //shrink the array if capacity hasnt been reached AND 
    // the number of elements is less than a fourth of the capacity
    if (capacity > INITIAL_CAPACITY && elementCount <= (capacity/4)) {
            resizeArr(capacity/2);
        }

}

// Description: Returns a copy of the frontmost element
// Precondition: Queue not empty
// Time Efficiency: O(1)
int Queue::peek() const {

    //shows the frontmost element
    return elements[frontindex];  

} 

// Description: Returns true if and only if Queue empty
// Time Efficiency: O(1)
bool Queue::isEmpty() const {

    if(elementCount == 0) {
        return true;
    }else {
        return false;
    }

}