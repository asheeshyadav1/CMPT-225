/*
 * Dictionary.cpp
 * 
 * Class Description: Dictionary data collection ADT class.
 *                    The implementation of this class is based on 
 *                    the hashing strategy and the open addressing 
 *                    collision resolution strategy called linear probing hashing. 
 *            
 * Class Invariant: Each element stored in this Dictionary is unique (no duplications allowed).
 *
 * Author: AL
 * Date: Last modified: April 2024
 */

// You can add more #include statements if you wish.

#include <iostream>
#include <cstring>
#include "Dictionary.h"  
#include "Profile.h"
#include "UnableToInsertException.h"
#include "ElementAlreadyExistsException.h"
#include "EmptyDataCollectionException.h"
#include "ElementDoesNotExistException.h"

using std::cout;
using std::endl;
using std::__cxx11::stoul;

// Constructor
Dictionary::Dictionary() {}

// Destructor
// Description: Destruct a Dictionary object, releasing heap-allocated memory.
Dictionary::~Dictionary() {
  // Release all heap memory
  if ( hashTable != nullptr ) { 
    for ( unsigned int i = 0; i < CAPACITY; i++ ) 
      if ( hashTable[i] != nullptr ) {      
        delete hashTable[i]; // Delete object of Profile class on heap
        hashTable[i] = nullptr;
      }
    delete [] hashTable;
    hashTable = nullptr;	
  }
}

// Description: Returns the total element count currently stored in Dictionary.
// Postcondition: Dictionary remains unchanged.
unsigned int Dictionary::getElementCount() const {
   return elementCount;
}

// Description: Returns the CAPACITY (size) of the Dictionary.
// Postcondition: Dictionary remains unchanged.
unsigned int Dictionary::getCapacity() const{
   return CAPACITY;
}

// Hash Function
// Description: Hashes the given indexingKey producing a "hash table index".
// My Time Efficiency: max(O(1),O(1),O(1),O(1)) = O(1)
// Time Efficiency: <- For you to complete!
// My Space Efficiency: O(1) 
// Space Efficiency: <- For you to complete!
unsigned int Dictionary::hashFunction( string indexingKey ) {

  uint64_t indexingKeyInt = stoul(indexingKey);  // O(1)
  
  // "hashCode" is an intermediate result
  unsigned int hashCode = indexingKeyInt % CAPACITY; // O(1)
  // cout << "string indexingKey = " << indexingKey << " uint64_t indexingKeyInt = " << indexingKeyInt << " hashCode = " << hashCode << endl; // O(1)
 
  return hashCode; // O(1)
}

// Description: Inserts an element into the Dictionary and increments "elementCount".
//              For this Assignment 5, you do not have to expand the hashTable when it is full. 
// Precondition: newElement must not already be in in the Dictionary.  
// Exception: Throws UnableToInsertException if we cannot insert newElement in the Dictionary.
//            For example, if the operator "new" fails, or Dictionary is full (temporary solution).
// Exception: Throws ElementAlreadyExistsException if newElement is already in the Dictionary. 
void Dictionary::insert( Profile * newElement )  {

   // Have we allocated memory for the hashTable yet?
   if ( elementCount == 0 ) {
      hashTable = new Profile*[CAPACITY];
      if (hashTable == nullptr) throw UnableToInsertException("In insert(): new failed.");
      for ( unsigned int i = 0; i < CAPACITY; i++ ) 
        hashTable[i] = nullptr; // Initialize each cell of hashTable, i.e., each pointer to nullptr.
   }

   // If Dictionary is full - to do: expand the Dictionary when full!
   // For this Assignment 5, you do not have to expand the Dictionary when it is full. 
   if ( elementCount == CAPACITY ) 
     throw UnableToInsertException("In insert(): Dictionary is full.");
   
   // Call hash function using indexing key to get hash index
   unsigned int hashIndex = hashFunction(newElement->getUserName());

   // Keep hashing and probing until no more collisions using Linear Collision Resolution Stratetgy
   unsigned int i = 0;
   unsigned int count = 0;
   while ( hashTable[(hashIndex + i)%CAPACITY] != nullptr ) {   
     // If newElement not already in Dictionary
     if ( *(hashTable[(hashIndex + i)%CAPACITY]) == *newElement ) {
	     // newElement was found -> already exists in Dictionary.
	     throw ElementAlreadyExistsException("In insert(): newElement already in Dictionary.");
	   }
     count++;
	   i++;
     if ( count == CAPACITY ) 
		   throw UnableToInsertException("In insertHelper(): Dictionary is full.");
   }
   
    // When found a cell: insert newElement in hashTable at hashIndex
   // When found a cell: insert newElement in hashTable at (hashIndex + i)%CAPACITY
    hashTable[(hashIndex + i)%CAPACITY] = newElement; 
/* 
	 cout << "In insert: newElement = " << *newElement << "\t address of newElement = " 
	   << newElement << " *(hashTable[hashIndex]) = " << *(hashTable[hashIndex]) << endl;
*/

  // One more element inserted!
  elementCount++;
    
  return;
}


// Description: Returns a pointer to the target element if found.
// Postcondition: Dictionary remains unchanged.
// Exception: Throws EmptyDataCollectionException if the Dictionary is empty.
// Exception: Throws ElementDoesNotExistException if target is not found in the Dictionary.
Profile * Dictionary::get( Profile & target )  {
  // If the Dictionary is empty, throw an exception
  if (elementCount == 0) {
    throw EmptyDataCollectionException("In get(): Dictionary is empty.");
  }

  // Call hash function using indexing key to get hash index
  unsigned int hashIndex = hashFunction(target.getUserName());

  // Keep hashing and probing until no more collisions using Linear Collision Resolution Strategy
  unsigned int i = 0;
  unsigned int count = 0;
  while (hashTable[(hashIndex + i) % CAPACITY] != nullptr) {
    // If target is found in Dictionary
    if (*(hashTable[(hashIndex + i) % CAPACITY]) == target) {
      // target was found -> return a pointer to it.
      return hashTable[(hashIndex + i) % CAPACITY];
    }
    count++;
    i++;
    if (count == CAPACITY) {
      // If we have searched the entire Dictionary and not found the target, throw an exception
      throw ElementDoesNotExistException("In get(): target not found in Dictionary.");
    }
  }

  // If we have searched the entire Dictionary and not found the target, throw an exception
  throw ElementDoesNotExistException("In get(): target not found in Dictionary.");
}
   
// Description: Prints all elements stored in the Dictionary (unsorted).
// Postcondition: Dictionary remains unchanged.
// Exception: Throws EmptyDataCollectionException if the Dictionary is empty.
void Dictionary::printDictionary()  const {
  if ( elementCount == 0 ) 
     throw EmptyDataCollectionException("In printDictionary(): hashTable is empty.");

  cout << endl << "Printing the Dictionary with " << this->elementCount << " elements: " << endl;
  for (unsigned int index = 0; index < CAPACITY; index++) {
    if ( hashTable[index] != nullptr ) 
		cout << "HashTable[" << index << "] = " << *(hashTable[index]) << endl; 
  }   
  return;
}
