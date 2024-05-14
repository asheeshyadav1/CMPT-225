/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Inspired from our textbook + Asheesh Yadav + Eshaan Virk
 * Date: March 15th, 2024
 */
 
#include "BST.h"
#include "WordPair.h"
#include <iostream>

using std::cout;
using std::endl;
using std::nothrow;


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.


/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            


// Copy constructor
// Creates a deep copy of the given BST
BST::BST(const BST & aBST) {
   if (aBST.root == nullptr) {
      root = nullptr;
      elementCount = 0;
   } else {
      root = new BSTNode;
      root->element = aBST.root->element;
      root->left = nullptr;
      root->right = nullptr;
      elementCount = aBST.elementCount;

      // Recursively copy the left subtree
      if (aBST.root->left != nullptr) {
         root->left = new BSTNode(*(aBST.root->left));
      }

      // Recursively copy the right subtree
      if (aBST.root->right != nullptr) {
         root->right = new BSTNode(*(aBST.root->right));
      }
   }
}

// Destructor 
// Releases memory occupied by the BST
// Note: This implementation assumes the destructor of BSTNode handles the subtree deletion
BST::~BST() {
   if (root != nullptr) {
       delete root;
   }
}
              
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     
     return this->elementCount;
   }
   

/* BST Operations */

// Description: Inserts an element into the binary search tree.
//              This is a wrapper method which calls the recursive insertR( ).
// Precondition: "newElement" does not already exist in the binary search tree.
// Exception: Throws the exception "UnableToInsertException" when newElement 
//            cannot be inserted because the "new" operator failed. 
// Exception: Throws the exception "ElementAlreadyExistsException" 
//            if "newElement" already exists in the binary search tree.
// Time efficiency: O(log2 n)   
void BST::insert(WordPair & newElement) {
    // Create a new node with the given element

    BSTNode* newNode = new BSTNode(newElement); 

    if(newNode == nullptr){
        // Unable to allocate memory using the new operator
        throw UnableToInsertException("New Operator has failed so you cannot insert it here"); 
    }
    if(root == nullptr){
        // If the tree is empty, set the new node as the root
        root = newNode;
        elementCount++;
    } else {
        // Call the recursive insertR method to insert the new node into the tree
        bool result = insertR(newNode, root);
        if(result) {
            // Increment the element count if the insertion is successful
            elementCount++; 
        } else {
            // The element already exists in the tree, throw an exception
            throw ElementAlreadyExistsException("Element already exists in the tree");
        }
    }
} 

// Description: Recursive insertion into a binary search tree.
//              Returns true when "anElement" has been successfully inserted into the 
//              binary search tree. Otherwise, returns false.
bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  
    // Compare the new element with the current node's element
    if(newBSTNode->element < current->element){
        // If the new element is less than the current node's element, move to the left subtree
        if(current->left == nullptr){
            // If the left child is null, insert the new node here
            current->left = newBSTNode;
            return true;
        } else {
            // Continue recursively inserting into the left subtree
            return insertR(newBSTNode, current->left);
        }
    }
    if(newBSTNode->element > current->element){
        // If the new element is greater than the current node's element, move to the right subtree
        if(current->right == nullptr){
            // If the right child is null, insert the new node here
            current->right = newBSTNode;
            return true;
        } else {
            // Continue recursively inserting into the right subtree
            return insertR(newBSTNode, current->right);
        }
    }
    // The element already exists in the tree
    return false;
}

   
   // Description: Retrieves "targetElement" from the binary search tree.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(log2 n)
   WordPair& BST::retrieve(WordPair & targetElement) const {
     if (elementCount == 0)  
        throw EmptyDataCollectionException("Binary search tree is empty.");
	
     WordPair& translated = retrieveR(targetElement, root);
	 
     return translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {
   if(current==nullptr){
      throw ElementDoesNotExistException("Element you are seeking does not exist");
   }
   if(targetElement == current->element){
      return current->element; 
   }
   if(targetElement < current->element){
      return retrieveR(targetElement,current->left);
   }else {
      return retrieveR(targetElement, current->right);
   }
}
         
   
   // Description: Traverses the binary search tree in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     if (elementCount == 0)  
       throw EmptyDataCollectionException("Binary search tree is empty.");

     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   // Postcondition: This method does not change the binary search tree. 
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 
   
   if(current!= nullptr){
      traverseInOrderR(visit,current->left);
      visit(current->element);
      traverseInOrderR(visit, current->right); 
   }
	  
   return;
   }
