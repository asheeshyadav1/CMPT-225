/*
 * Dictionary.cpp
 * 
 * Description: Implementation of the Dictionary data collection ADT class.
 *              BST-based implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: AL
 * Date of last modification: Feb. 2024
 */

#include "Dictionary.h"
#include "UnableToInsertException.h"
#include "ElementAlreadyExistsException.h"
#include "ElementDoesNotExistException.h"
#include <iostream>
#include "BST.h"

using std::cout;
using std::endl;

// Constructor
Dictionary::Dictionary() {
    keyValuePairs = new BST();
}

// Destructor
Dictionary::~Dictionary() {
    delete keyValuePairs;
}

// Returns the number of elements currently stored in the Dictionary.
unsigned int Dictionary::getElementCount() const {
    return keyValuePairs->getElementCount();
}

// Puts "newElement" (association of key-value) into the Dictionary.
void Dictionary::put(WordPair &newElement) {
    try {
        keyValuePairs->insert(newElement);
    } catch (UnableToInsertException &e) {
        // Unable to insert newElement
        throw UnableToInsertException(e.what());
    } catch (ElementAlreadyExistsException &e) {
        // Element already exists in the Dictionary
        throw ElementAlreadyExistsException(e.what());
    }
}

// Gets "newElement" from the Dictionary
WordPair &Dictionary::get(WordPair &targetElement) const {
    try {
        return keyValuePairs->retrieve(targetElement);
    } catch (EmptyDataCollectionException &e) {
        // Dictionary is empty
        throw EmptyDataCollectionException(e.what());
    } catch (ElementDoesNotExistException &e) {
        // Element does not exist in the Dictionary
        throw ElementDoesNotExistException(e.what());
    }
}

// Prints the content of the Dictionary.
void Dictionary::displayContent(void visit(WordPair &)) const {
    if (keyValuePairs->getElementCount()==0) {
        throw EmptyDataCollectionException("Dictionary is empty");
    } else {
        try {
            keyValuePairs->traverseInOrder(visit);
        } catch (EmptyDataCollectionException &e) {
            // Handle any exceptions thrown during traversal
            throw EmptyDataCollectionException(e.what());
        }
    }
}
