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
 * Author: Eshaan Virk + Asheesh Yadav
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
#include <random>

using std::cout;
using std::endl;
using std::__cxx11::stoul;
using std::rand;


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
  // Time Efficiency: since stoul() is O(n) and thats the max time complexity of the function
                      // then we know that the time complexity of the function is O(n)
  // Time Efficiency: max(0(n), O(1), O(1), O(1), O(1)) => O(n)
  // Space Efficiency:Because we are doing everything in place, the space efficiency is O(1)
                      // (no extra space is used to store anything other than the input)
  // Space Efficiency: O(1)
unsigned int Dictionary::hashFunction(string indexingKey) {
  //convert the string to an unsigned int
   uint64_t indexingKeyInt = std::stoul(indexingKey); //O(n)
        //check if 16 digit number is odd 
        if (indexingKeyInt % 2 == 1) { //O(1)
          //muliplied by Radkes equation
            unsigned int hashIndex = 4 * indexingKeyInt + 3; //O(1)
            return (hashIndex) % CAPACITY; //O(1)
        }
        //return the hash index
        return (indexingKeyInt) % CAPACITY; //O(1)
    }

void Dictionary::insert(Profile* newElement) {
    // Have we allocated memory for the hashTable yet?
    if (elementCount == 0) {
        hashTable = new Profile*[CAPACITY];
        if (hashTable == nullptr) throw UnableToInsertException("In insert(): new failed.");
        for (unsigned int i = 0; i < CAPACITY; i++)
            hashTable[i] = nullptr; // Initialize each cell of hashTable, i.e., each pointer to nullptr.
    }

    // If Dictionary is full - to do: expand the Dictionary when full!
    // For this Assignment 5, you do not have to expand the Dictionary when it is full. 
    if (elementCount == CAPACITY)
        throw UnableToInsertException("In insert(): Dictionary is full.");

    // Call hash function using indexing key to get hash index
    unsigned int hashIndex = hashFunction(newElement->getUserName());

    // Keep hashing and probing until no more collisions using Linear Collision Resolution Strategy
    unsigned int i = 0;
    unsigned int count = 0;
    while (hashTable[(hashIndex + i) % CAPACITY] != nullptr) {
        // If newElement not already in Dictionary
        if (*(hashTable[(hashIndex + i) % CAPACITY]) == *newElement) {
            // newElement was found -> already exists in Dictionary.
            throw ElementAlreadyExistsException("In insert(): newElement already in Dictionary.");
        }
        count++;
        i++;
        if (count == CAPACITY)
            throw UnableToInsertException("In insertHelper(): Dictionary is full.");
    }

    // When found a cell: insert newElement in hashTable at the probed index
    hashTable[(hashIndex + i) % CAPACITY] = newElement;

    // One more element inserted!
    elementCount++;

    return;
}


// Description: Returns a pointer to the target element if found.
// Postcondition: Dictionary remains unchanged.
// Exception: Throws EmptyDataCollectionException if the Dictionary is empty.
// Exception: Throws ElementDoesNotExistException if target is not found in the Dictionary.
Profile * Dictionary::get( Profile & target ) {
    if (elementCount == 0) {
        throw EmptyDataCollectionException("Dictionary is empty.");
    }

    unsigned int hashIndex = hashFunction(target.getUserName());

    unsigned int i = 0;
    unsigned int count = 0;
    while (hashTable[(hashIndex + i) % CAPACITY] != nullptr) {
        if (*hashTable[(hashIndex + i) % CAPACITY] == target) {
            return hashTable[(hashIndex + i) % CAPACITY];
        }
        count++;
        i++;
        if (count == CAPACITY)
            throw ElementDoesNotExistException("Target element does not exist in the Dictionary.");
    }

    throw ElementDoesNotExistException("Target element does not exist in the Dictionary.");
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
