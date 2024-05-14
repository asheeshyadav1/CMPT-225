/*
 * Queue.cpp
 *
 * Description: A Linked List based implementation of a Queue
 *
 * Class Invariant: FIFO order
 *
 * Author: Asheesh Yadav + Eeshan V
 * Last Modified: April 5, 2024
 */
#include "Queue.h"

// Constructor
//creates an empty queue.
// Time Complexity: O(1)
template <typename ElementType>
Queue<ElementType>::Queue() : front(nullptr), back(nullptr), elementCount(0) {}

// Destructor
// Deletes all elemnts in queue
// Time Complexity: O(n)
template <typename ElementType>
Queue<ElementType>::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Copy Constructor
// copies data over to new queue
// Time Complexity: O(n)
template <typename ElementType>
Queue<ElementType>::Queue(const Queue &other) : front(nullptr), back(nullptr) {
    Node *current = other.front;
    while (current) {
        enqueue(current->data); // Enqueues each element from the other queue.
        current = current->next;
    }
}

// Copy Assignment Operator
// gives the content of 1 queue to another
// Time Complexity: O(n)
template <typename ElementType>
Queue<ElementType>& Queue<ElementType>::operator=(const Queue &other) {
    if (this != &other) {
        while (!isEmpty()) {
            dequeue(); // Clears the current queue.
        }
        Node *current = other.front;
        while (current) {
            enqueue(current->data); // Enqueues each element from the other queue.
            current = current->next;
        }
    }
    return *this;
}

// checks if queue is empty
// Time Complexity: O(1)
template <typename ElementType>
bool Queue<ElementType>::isEmpty() const {
    if(getElementCount() == 0) {
        return true;
    } else {
        return false;
    }
}

// eqnueues an element into queue
// Time Complexity: O(1)
template <typename ElementType>
bool Queue<ElementType>::enqueue(ElementType &newElement) {
    Node *newNode = new Node;
    newNode->data = newElement;
    newNode->next = nullptr;
    if (isEmpty()) {
        front = back = newNode; // If the queue is empty, new node becomes both front and back.
    } else {
        back->next = newNode; // Otherwise, insert at the back.
        back = newNode;
    }
    elementCount++; // Increment the element count.
    return true;
}

// dequeues an element from the queue
// Time Complexity: O(1)
template <typename ElementType>
void Queue<ElementType>::dequeue() {
    if (isEmpty()) {
         throw EmptyDataCollectionException("Queue is empty"); // Throws exception if queue is empty
    } else {
        Node *oldFront = front;
        front = front->next; // Move front pointer.
        delete oldFront; // Delete the old front node.
        if (isEmpty()) {
            back = nullptr; // If queue becomes empty, back should also be nullptr.
        }
        elementCount--; // Decrement the element count.
    }
}

// shows the front element in the queue
// Time Complexity: O(1)
template <typename ElementType>
ElementType &Queue<ElementType>::peek() const {
    if (isEmpty()) {
        throw EmptyDataCollectionException("Queue is empty"); // Throws exception if queue is empty
    } else {
        return front->data;
    }
}


// return # of elements in queue
// Time Complexity: O(1)
template <typename ElementType>
unsigned int Queue<ElementType>::getElementCount() const {
    return elementCount;
}