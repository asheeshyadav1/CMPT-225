/* 
 * Stack.h
 *
 * Description: Implementation of a linked list-based Stack ADT class - SHSL list
 * Class Invariant: LIFO order
 *                  Top of Stack located at the back of SHSL list.
 *
 * Author: Asheesh Yadav + Eshaan Virk
 * Date: February 16th 2024
 */

#include <iostream> // include iostream lib
#include <string> // include string lib 
#include <cctype> // include cctype lib
 
class Stack {

    private:
        
        // Description:  Nodes for a singly-linked list - Do not modify!
        class StackNode {
            public:
                int data;
                StackNode * next;
        };
        
    StackNode* top; // Pointer to the top of the stack (back of the linked list)     
        

    public:
    

// Constructor and Destructor
    Stack();
    ~Stack();

    // Stack operations
    void push(int value);
    int pop();
    int peek() const;
    bool isEmpty() const;


};
