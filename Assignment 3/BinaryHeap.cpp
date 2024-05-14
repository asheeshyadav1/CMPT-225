/*
 * BinaryHeap.cpp
 *
 * Description: This is a min binary heap class that stores elements in a binary tree.
 *
 * Class Invariant: Smallest element is always at the root.
 *
 * Author: Asheesh Yadav + Eeshan V
 * Last Modified: April 5, 2024
 */

#include "BinaryHeap.h"

// Constructor
// make a default binary heap with default values
// Time Complexity: O(1)
template <class ElementType>
BinaryHeap<ElementType>::BinaryHeap() : elementCount(0), capacity(10) {
    elements = new ElementType[capacity]; // allocate mem for elements[]
}

// Destructor
// Deallocates memory
// Time Complexity: O(1)
template <class ElementType>
BinaryHeap<ElementType>::~BinaryHeap() {
    delete[] elements; // free mem allocated for elements[]
}

// return # of elements in min bin heap
// Time Complexity: O(1)
template <class ElementType>
unsigned int BinaryHeap<ElementType>::getElementCount() const {
    return elementCount;
}

// inserting an element into heap
// Time Complexity: O(log n)
template <class ElementType>
bool BinaryHeap<ElementType>::insert(ElementType & newElement) {
    //resize if needed
    //double capactity -> copy elements  
    // -> delete old elements -> assign new elements
    if (elementCount >= capacity) {
        capacity *= 2; 
        ElementType* newElements = new ElementType[capacity]; 
        for (unsigned int i = 0; i < elementCount; i++) {
            newElements[i] = elements[i]; 
        }
        delete[] elements; 
        elements = newElements; 
    }
    //insert element
    elements[elementCount] = newElement; 
    elementCount++; // inc element count

    reHeapUp(elementCount - 1); // re-heapify up
    return true;
}

// Removes the root element from the heap
// Time Complexity: O(log n)
template <class ElementType>
void BinaryHeap<ElementType>::remove() {
    //throw exception if heap is empty
    if(elementCount == 0) 
        throw EmptyDataCollectionException("remove() called with an empty BinaryHeap.");
    
    // replace root with last element
    elements[0] = elements[elementCount - 1]; 

    elementCount--; // Dec element count

    if (elementCount > 0) 
        reHeapDown(0); // re-heapify down
}

// Retrieves the root element of the heap
// Time Complexity: O(1)
template <class ElementType>
ElementType & BinaryHeap<ElementType>::retrieve() const {
    if(elementCount == 0) //thow exception if heap is empty
        throw EmptyDataCollectionException("retrieve() called with an empty BinaryHeap.");

    return elements[0]; // Return root
}


// Re-heapify down operation
// Time Complexity: O(log n)
//(as modeled in the lecture slides)
template <class ElementType>
void BinaryHeap<ElementType>::reHeapDown(unsigned int indexOfRoot) {
    //equations to find left and right child
    unsigned int leftChildIndex = 2 * indexOfRoot + 1;
    unsigned int rightChildIndex = 2 * indexOfRoot + 2;

    if (leftChildIndex >= elementCount) {
        return; // Reached a leaf
    }

    unsigned int minIndex = indexOfRoot;

    if (!(elements[indexOfRoot] <= elements[leftChildIndex])) {
        minIndex = leftChildIndex;
    }

    if ((rightChildIndex < elementCount) && !(elements[minIndex] <= elements[rightChildIndex])) {
        minIndex = rightChildIndex;
    }

    if (minIndex != indexOfRoot) {
        ElementType temp = elements[indexOfRoot];
        elements[indexOfRoot] = elements[minIndex];
        elements[minIndex] = temp;

        reHeapDown(minIndex); // Recursively re-heapify down.
    }
}

// Re-heapify up operation
// Time Complexity: O(log n)
//(as modeled in the lecture slides)
template <class ElementType>
void BinaryHeap<ElementType>::reHeapUp(unsigned int indexOfChild) {
    if (indexOfChild == 0) {
        return; // Reached the root
    }
    //no need to floor it since we are doing int division
    unsigned int parentIndex = (indexOfChild - 1) / 2;

    if (!(elements[parentIndex] <= elements[indexOfChild])) {
        ElementType temp = elements[parentIndex];
        elements[parentIndex] = elements[indexOfChild];
        elements[indexOfChild] = temp;

        reHeapUp(parentIndex); // Recursively re-heapify up.
    }
}