/*
 * BinaryHeap.h
 *
 * Description: This is a min binary heap class that stores elements in a binary tree.
 *
 * Class Invariant: Smallest element is always at the root.
 *
 * Author: Asheesh Yadav + Eeshan V
 * Last Modified: April 5, 2024
 */
#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "Event.h"
#include "EmptyDataCollectionException.h"
#include <iostream>

// Declaration of the BinaryHeap class template
template <class ElementType>
class BinaryHeap {
private:
    ElementType* elements; // Array to store elements
    unsigned int elementCount; // Number of elements in the heap
    unsigned int capacity; // Capacity of the heap

    // Re-heapify down operation
    // Time Complexity: O(log n)
    void reHeapDown(unsigned int indexOfRoot);
    
    // Re-heapify up operation
    // Time Complexity: O(log n)
    void reHeapUp(unsigned int indexOfChild);

public:
    // Constructor: Initializes an empty binary heap
    // Time Complexity: O(1)
    BinaryHeap();
    
    // Destructor: Deallocates memory
    // Time Complexity: O(1)
    ~BinaryHeap();

    // Returns the number of elements in the heap
    // Time Complexity: O(1)
    unsigned int getElementCount() const;

    // Inserts a new element into the heap
    // Time Complexity: O(log n)
    bool insert(ElementType & newElement);

    // Removes the root element from the heap
    // Time Complexity: O(log n)
    void remove();

    // Retrieves the root element of the heap
    // Time Complexity: O(1)
    ElementType & retrieve() const;
};

#include "BinaryHeap.cpp" // Include the implementation file

#endif //BINARY_HEAP_H