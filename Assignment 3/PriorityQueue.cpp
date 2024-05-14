/*
 * PriorityQueue.cpp
 *
 * Description: This a Priotty Queue ADT with a min binary heap as its underlying data structure.
 *
 * Class Invariant: element with the highest priority is always first to be dequeued.
 *
 * Author: Asheesh Yadav + Eeshan V
 * Last Modified: April 5, 2024
*/

#include "PriorityQueue.h"

// Checks if the priority queue is empty
//  Time Complexity: O(1)
template <class ElementType>
bool PriorityQueue<ElementType>::isEmpty() const {
    return heap.getElementCount() == 0;
}

// Enqueues a new element into the priority queue
// Time Complexity: O(log n)
template <class ElementType>
bool PriorityQueue<ElementType>::enqueue(ElementType & newElement) {
    return heap.insert(newElement);
}

// Dequeues the element with the highest priority from the priority queue
// Time Complexity: O(log n)
template <class ElementType>
void PriorityQueue<ElementType>::dequeue(){
    if (heap.getElementCount() == 0) {
        throw EmptyDataCollectionException("Queue is empty.");
    }
    heap.remove();
}

// Retrieves the element with the highest priority from the priority queue
// Time Complexity: O(1)
template <class ElementType>
ElementType & PriorityQueue<ElementType>::peek() const{
    if (heap.getElementCount() == 0) {
        throw EmptyDataCollectionException("Queue is empty.");
    }
    return heap.retrieve();
}


// Returns total # of elements in the PQ
// Time Complexity: O(1)
template <class ElementType>
unsigned int PriorityQueue<ElementType>::getElementCount() const {
    return heap.getElementCount();
}