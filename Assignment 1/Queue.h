/* 
 * Queue.h - Does not work well!
 *
 * Description: Array-based implementation of Queue as an ADT class
 * Class Invariant: Queue maintained in FIFO order
 *
 * Author: Asheesh Yadav + Eshaan Virk
 * Date: February 16, 2024
 */
 
#ifndef QUEUE_H
#define QUEUE_H
 
class Queue {

/* You cannot remove/modify the data members below, 
   except for the "int elements[INITIAL_CAPACITY];". 
   However, you can add more data members.              */
	
    private:
        static unsigned int const INITIAL_CAPACITY = 6; // Constant INITIAL_CAPACITY
        int * elements;                 // To do: replace this by int * elements -> Question 4.a)
        unsigned int elementCount = 0;                  // Number of elements in the Queue - if you need it!
        unsigned int capacity = INITIAL_CAPACITY;       // Actual capacity of the data structure (number of cells in the array)
        unsigned int frontindex = 0;                    // Index of front element (next dequeued/peeked element)
        unsigned int backindex = 0;                     // Index of where the next element will be enqueued                      
/* You can add private methods. */


    public:
 
/* You cannot remove/modify the public methods below. 
   This also applies to their documentation. 
   However, you can add public methods if you need them 
   like "printQueue()", etc.                            */

        // Description: Constructor
        Queue();

        // Description: Inserts newElement at the back of Queue
        // Time Efficiency: O(1)
        void enqueue(int newElement);

        // Description: Removes the frontmost element
        // Precondition: Queue not empty
        // Time Efficiency: O(1)
        void dequeue();

        // Description: Returns a copy of the frontmost element
        // Precondition: Queue not empty
        // Time Efficiency: O(1)
        int peek() const;

        // Description: Returns true if and only if Queue empty
        // Time Efficiency: O(1)
        bool isEmpty() const;

        // Description: Destructor
        //Time Efficiency: O(1)
        ~Queue();

        // Description: Copy constructor
        //Time Efficiency: O(n)
        Queue(const Queue& other); 

        // Description: Assignment operator
        //Time Efficiency: O(n)
        Queue& operator=(const Queue& other);

        // Description: Resizes the array to the new capacity
        //Time Efficiency: O(n)
        void resizeArr(int newCapacity);
        
};
#endif


