/*
 * UnableToInsertException.cpp
 *
 * Class Description: Defines the exception that is thrown when a newElement
 *                    cannot be inserted into the data collection ADT class.
 *
 * Author: Inspired from our textbook's authors Frank M. Carrano and Tim Henry.
 *         Copyright (c) 2013 __Pearson Education__. All rights reserved.
 */

#include "UnableToInsertException.h"  

// Constructor
UnableToInsertException::UnableToInsertException(const string& message): 
logic_error("newElement cannot be inserted into the data collection ADT class Exception: " + message) {}

void inner6(vec_ptr u, vec_ptr v, data_t *dest)
{
    // for loop variables
    long i;
    // get the length of the vector
    long length = vec_length(u);
    // get the start of the vector
    data_t *udata = get_vec_start(u);
    // get the start of the vector
    data_t *vdata = get_vec_start(v);
    // initialize the sum
    data_t sum = (data_t) 0;

    /* Process six elements per loop iteration */
    for (i = 0; i < length - 5; i += 6) {
        sum = sum + udata[i] * vdata[i]
                  + udata[i+1] * vdata[i+1]
                  + udata[i+2] * vdata[i+2]
                  + udata[i+3] * vdata[i+3]
                  + udata[i+4] * vdata[i+4]
                  + udata[i+5] * vdata[i+5];
    }

    /* Finish any remaining elements */
    for (; i < length; i++) {
        sum = sum + udata[i] * vdata[i];
    }

    *dest = sum;
}

Consider the syntactly correct function below:

int sumArray(int A[N][N][N]) {
    int i, j, k, sum = 0; // Initialize for loop variables

    // loop through 3D array
    // in terms of [k][i][j] with a stride of 1
    for (k = 0; k < N; k++)
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                sum += A[k][i][j];
    return sum;
}