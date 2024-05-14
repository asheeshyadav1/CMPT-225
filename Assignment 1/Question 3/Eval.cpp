
/* 
 * Eval.cpp
 *
 * Description: Evaluation of infix expressions using two Stacks.
 *
 * Authors: Asheesh Yadav + Eshaan Virk
 * Date: February 16th 2024
 */

#include <iostream> // include iostream library
#include "Scanner.h"// include scanner header file
#include "Stack.h" // include stack header file
using namespace std; // use standard namespace

// Determine precedence of operators using PEMDAS
int preceOpr(char oprChar) {
    // lower precedence
    if (oprChar == '+' || oprChar == '-') { 
        return 1;
        
    } else if (oprChar == '*' || oprChar == '/') { // higher precedence
        return 2;
    }
    return 0;  
}

// Helper function to do operations 
int operCalc(int opr1, int opr2, char oprChar) {
    switch (oprChar) {
        case '+':
            return opr1 + opr2;
        case '-':
            return opr1 - opr2;
        case '*':
            return opr1 * opr2;
        case '/':
            if (opr2 != 0) { // check for div by 0
                return opr1 / opr2;
            } else { // Throw exception
                throw -1;
            }
        default: // if invalid operator
            throw -2; // Throw exception
    }
}

int main () {
    Stack<int> numstack; // create stack for numbers
    Stack<char> opstack; // create stack for operators

    Scanner Scn(cin); // create scanner instance
    Token tok; // create token instance
    
    tok = Scn.getnext(); // get next token
    
    while (tok.tt != eof) {
        try {
            if (tok.tt == integer) { // if integer, push onto number stack
                numstack.push(tok.val); 
            } else if (tok.tt == lptok) { // if left parenthesis, push onto operator stack
                opstack.push(tok.text[0]);
            } else if (tok.tt == rptok) {
                // Perform operations until '(' or empty stack
                while (!opstack.isEmpty() && opstack.peek() != '(') {
                    int opr2 = numstack.pop();
                    int opr1 = numstack.pop();
                    char oprChar = opstack.pop();

                    numstack.push(operCalc(opr1, opr2, oprChar)); // perform operation
                }
                opstack.pop(); // Pop the left parenthesis
            } else if (tok.tt == pltok || tok.tt == mitok || tok.tt == asttok 
                                                                            || tok.tt == slashtok) {
                // While there are operators on the stack with greater or equal precedence
                while (!opstack.isEmpty() && preceOpr(opstack.peek()) >= preceOpr(tok.text[0])){
                    int opr2 = numstack.pop();
                    int opr1 = numstack.pop();
                    char oprChar = opstack.pop();

                    numstack.push(operCalc(opr1, opr2, oprChar)); // perform operation
                }
                opstack.push(tok.text[0]); // Push current operator onto operator stack
            }
            tok = Scn.getnext(); // get next token

          // Catch exceptions
        } catch (int err) {
            if (err == -1) {
                cerr << "Error: Division by zero not allowed" << endl;
                return 1;
            } else if (err == -2) {
                cerr << "Error: Invalid operator" << endl;
                return 1;
            }
        }
    }

    // Process any remaining operators in the stack
    while (!opstack.isEmpty()) {
        try {
            int opr2 = numstack.pop();
            int opr1 = numstack.pop();
            char oprChar = opstack.pop();

            numstack.push(operCalc(opr1, opr2, oprChar)); // perform operation
        } catch (int err) {
            if (err == -1) {
                cerr << "Error: Division by zero not allowed" << endl;
                return 1;
            } else if (err == -2) {
                cerr << "Error: Invalid operator" << endl;
                return 1;
            }
        }
    }
    
    // Result is on the top of the number stack
    cout << numstack.pop() << endl; 

    return 0;
}
