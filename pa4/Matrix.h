/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA4
* Matrix.h
* Matrix header for Matrix ADT
*********************************************************************************/ 

// Start: from Queue.h example
#ifndef MATRIX_H_INCLUDE_
#define MATRIX_H_INCLUDE_
#include<stdbool.h>

// End: Queue.h example

// Start this is a public struct
typedef struct MatrixObj* Matrix;
// End this is a public struct

/*** Constructors-Destructors ***/
Matrix newMatrix(int n); // Returns a reference to a new nXn Matrix object in the zero state.
void freeMatrix(Matrix* pM); // Frees heap memory associated with *pM, sets *pM to NULL.

/*** Access functions ***/
int size(Matrix M); // Return the size of square Matrix M.
int NNZ(Matrix M); // Return the number of non-zero elements in M.
int equals(Matrix A, Matrix B); // Return true (1) if matrices A and B are equal, false (0) otherwise.

/*** Manipulation procedures ***/
void makeZero(Matrix M); // Re-sets M to the zero Matrix state.
void changeEntry(Matrix M, int i, int j, double x); // Pre: 1<=i<=size(M), 1<=j<=size(M) - Changes the ith row, jth 
                                                    // column of M to the value x.

/*** Matrix Arithmetic operations ***/
Matrix copy(Matrix A); // Returns a reference to a new Matrix object having the same entries as A.
Matrix transpose(Matrix A); // Returns a reference to a new Matrix object representing the transpose of A.
Matrix scalarMult(double x, Matrix A); // Returns a reference to a new Matrix object representing xA.
Matrix sum(Matrix A, Matrix B); // pre: size(A)==size(B) - Returns a reference to a new Matrix object representing A+B.
Matrix diff(Matrix A, Matrix B); // pre: size(A)==size(B) - Returns a reference to a new Matrix object representing A-B.
Matrix product(Matrix A, Matrix B); // pre: size(A)==size(B) - Returns a reference to a new Matrix object representing AB
void printMatrix(FILE* out, Matrix M); // Prints a string representation of Matrix M to filestream out. Zero rows
                                       // are not printed. Each non-zero row is represented as one line consisting
                                       // of the row number, followed by a colon, a space, then a space separated
                                       // list of pairs "(col, val)" giving the column numbers and non-zero values
                                       // in that row. The double val will be rounded to 1 decimal point.

/*** Cumtastic placeholders ***/
// start of faculty Alex Rudnick's idea
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
// end of faculty Alex Rudnick's idea

#endif