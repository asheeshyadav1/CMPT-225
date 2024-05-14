/*
 * PriorityQueue.h
 *
 * Description: This a Priotty Queue ADT with a min binary heap as its underlying data structure.
 *
 * Class Invariant: element with the highest priority is always first to be dequeued.
 *
 * Author: Asheesh Yadav + Eeshan V
 * Last Modified: April 5, 2024
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "BinaryHeap.h"
#include "EmptyDataCollectionException.h"

// Declaration of the PriorityQueue class template
template <class ElementType>
class PriorityQueue {
private:
    BinaryHeap<ElementType> heap; // Binary heap to implement priority queue

public:
    // Checks if the priority queue is empty
    // Time Complexity: O(1)
    bool isEmpty() const;

    // Enqueues a new element into the priority queue
    // Time Complexity: O(log n)
    bool enqueue(ElementType & newElement);

    // Dequeues the element with the highest priority from the priority queue
    // Time Complexity: O(log n)
    void dequeue();

    // Retrieves the element with the highest priority from the priority queue
    // Time Complexity: O(1)
    ElementType & peek() const;

    // Returns the number of elements in the priority queue
    unsigned int getElementCount() const;
};

#include "PriorityQueue.cpp" // Include the implementation file

#endif // PRIORITYQUEUE_H