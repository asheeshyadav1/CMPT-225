
/* 
 * Stack.cpp
 *
 * Description: Implementation of a linked list-based Stack ADT class - SHSL list
 * Class Invariant: LIFO order
 *                  Top of Stack located at the back of SHSL list.
 *
 * Author: Asheesh Yadav + Eshaan Virk
 * Date: February 16th 2024
 */

#include "Stack.h" // include the stack header 

// Constructor
Stack::Stack() {
    top = nullptr;
}

// Destructor
Stack::~Stack() {
    // Implement code to free memory and delete nodes
    while (!isEmpty()) {
        pop();
    }
}

// Push operation
void Stack::push(int value) {

    // Create a new node
    StackNode* newNode = new StackNode; 
    newNode->data = value; 
    newNode->next = nullptr; 
    if (isEmpty()) { 
        //if its empty make top node the new node
        top = newNode; 
    } else { 
        //create a temp node
        StackNode* temp = top;
        // Traverse the stack to the last node
        while (temp->next != nullptr) { 
            temp = temp->next; 
        }
        // Update the next pointer of the last node to the new node
        temp->next = newNode;
    }
} 
// Pop operation
int Stack::pop() {

    //case for when the stack is empty
    if (isEmpty()) {
        return -1; 
    }

    // If there's only one element, update top to nullptr
    if (top->next == nullptr) { 
        int data = top->data; 
        delete top; 
        top = nullptr; 
        return data; 
    }

    // If there are multiple elements, remove the last node
    StackNode* temp = top; 
    while (temp->next->next != nullptr) { 
        temp = temp->next; 
    }
    
    // Store the data of the last node
    int data = temp->next->data;
    
    // Delete the last node 
    delete temp->next;

    // Update the next pointer of the second last node to nullptr
    temp->next = nullptr; 
    return data; 
} 
// Peek operation
int Stack::peek() const {
    //when the stack is empty
    if (isEmpty()) {
        return -1; 
    }

    // Create a temp pointer to traverse the stack
    StackNode* temp = top; 

    // Traverse the stack to the last node
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    // Return the data of the last node
    return temp->data; 
}

// to check is the stack is empty
bool Stack::isEmpty() const {
    // if its empty it will return true
    return top == nullptr;
}
