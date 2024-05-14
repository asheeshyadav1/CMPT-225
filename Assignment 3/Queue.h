/*
 * Queue.h
 *
 * Description: A Linked List based implementation of a Queue
 *
 * Class Invariant: FIFO order
 *
 * Author: Asheesh Yadav + Eeshan V
 * Last Modified: April 5, 2024
 */
#ifndef QUEUE_H
#define QUEUE_H

#include "EmptyDataCollectionException.h"
using namespace std;

// Declaration of the Queue class template
template <typename ElementType>
class Queue {
public:
    //Constructor
    //Time Complexity: O(1)
    Queue(); 

    // Destructor
    //Time Complexity: O(n)
    ~Queue(); 

    // Copy constructor
    //Time Complexity: O(n)
    Queue(const Queue &other); 

    // Overloaded assignment operator
    //Time Complexity: O(n)
    Queue& operator=(const Queue &other);

    //Description: checks if the queue is empty
    //Time Complexity: O(1)
    bool isEmpty() const;

    //Description: adds an element to the queue
    //Time Complexity: O(1)
    bool enqueue(ElementType &newElement);

    //Description: removes an element from the queue
    //Time Complexity: O(1)
    void dequeue();

    //Description: returns the front element of the queue
    //Time Complexity: O(1)
    ElementType &peek() const;

    //Description: returns the element count
    //Time Complexity: O(1)
    unsigned int getElementCount() const;

private:
    struct Node { // Node structure
        ElementType data;
        Node *next;
    };

    Node *front;
    Node *back;
    //Element count
    unsigned int elementCount;
};
#include "Queue.cpp"
#endif // QUEUE_H