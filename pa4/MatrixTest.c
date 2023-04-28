/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA4
* MatrixTest.c
* MatrixTest for Matrix ADT
*********************************************************************************/
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main() {
  int n = 6;
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  Matrix C, D, E, F, G, H;
  
  // populate matrices A and B with values
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
       if (i == j) {
          changeEntry(A, i, j, i * j);
          changeEntry(B, i, j, i + j);
       } else if (i % 2 == 0) {
          changeEntry(A, i, j, 2 * j);
          changeEntry(B, i, j, j);
       } else {
          changeEntry(A, i, j, j);
          changeEntry(B, i, j, i);
       }
    }
  }

  // create a 3x3 matrix L and set values
  Matrix L = newMatrix(3);
  changeEntry(L, 1, 1, 1.0);
  changeEntry(L, 1, 2, 2.0);
  changeEntry(L, 1, 3, 3.0);
  changeEntry(L, 2, 1, 4.0);
  changeEntry(L, 2, 2, 5.0);
  changeEntry(L, 2, 3, 6.0);
  changeEntry(L, 3, 1, 7.0);
  changeEntry(L, 3, 2, 8.0);
  changeEntry(L, 3, 3, 9.0);
  
  // create a 3x3 matrix M and set values
  Matrix M = newMatrix(3);
  changeEntry(M, 1, 1, 1.0);
  changeEntry(M, 1, 2, 0.0);
  changeEntry(M, 1, 3, 1.0);
  changeEntry(M, 2, 1, 0.0);
  changeEntry(M, 2, 2, 1.0);
  changeEntry(M, 2, 3, 0.0);
  changeEntry(M, 3, 1, 1.0);
  changeEntry(M, 3, 2, 1.0);
  changeEntry(M, 3, 3, 1.0);
  
  // create a 3x3 matrix O and set values
  Matrix O = newMatrix(3);
  changeEntry(O, 1, 1, 2.0);
  changeEntry(O, 1, 2, 4.0);
  changeEntry(O, 1, 3, 6.0);
  changeEntry(O, 2, 1, 8.0);
  changeEntry(O, 2, 2, 10.0);
  changeEntry(O, 2, 3, 12.0);
  changeEntry(O, 3, 1, 14.0);
  changeEntry(O, 3, 2, 16.0);
  changeEntry(O, 3, 3, 18.0);
  
  // perform operations on matrices A and B
  printf("A:\n");
  printMatrix(stdout, A);
  printf("\n");
  printf("B:\n");
  printMatrix(stdout, B);
  printf("\n");
  
  C = scalarMult(2.5, A);
  printf("C = 2.5 * A:\n");
  printMatrix(stdout, C);
  printf("\n");
  
  D = sum(A, B);
  printf("D = A + B:\n");
  printMatrix(stdout, D);
  printf("\n");
  
  E = diff(A, A);
  printf("E = A - A:\n");
  printMatrix(stdout, E);
  printf("\n");
  
  F = transpose(B);
  printf("F = transpose(B):\n");
  printMatrix(stdout, F);
  printf("\n");
  
  G = product(B, B);
  printf("G = B * B:\n");
  printMatrix(stdout, G);
  printf("\n");
  
  H = copy(A);
  printf("H = copy(A):\n");
  printMatrix(stdout, H);
  printf("\n");
  
  printf("A == H: %s\n", equals(A, H) ? "true" : "false");
  printf("A == B: %s\n", equals(A, B) ? "true" : "false");
  printf("A == A: %s\n", equals(A, A) ? "true" : "false");
  
  // test transpose
  Matrix P = transpose(L);
  printf("L^T =\n");
  printMatrix(stdout, P);
  
  // test scalar multiplication
  Matrix Q = scalarMult(2.0, L);
  printf("2L =\n");
  printMatrix(stdout, Q);
  
  // test matrix addition
  Matrix R = sum(L, M);
  printf("L + M =\n");
  printMatrix(stdout, R);
  
  // test matrix subtraction
  Matrix S = diff(L, M);
  printf("L - M =\n");
  printMatrix(stdout, S);
  
  // test matrix multiplication
  Matrix T = product(L, M);
  printf("L * M =\n");
  printMatrix(stdout, T);
  
  // test copy
  Matrix U = copy(L);
  printf("L copy =\n");
  printMatrix(stdout, U);
  
  // test makeZero
  makeZero(L);
  printf("Zeroed out L =\n");
  printMatrix(stdout, L);
  
  makeZero(A);
  printf("A after makeZero:\n");
  printMatrix(stdout, A);
  printf("\n");
  
  // free matrices
  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&E);
  freeMatrix(&F);
  freeMatrix(&G);
  freeMatrix(&H);
  freeMatrix(&L);
  freeMatrix(&M);
  freeMatrix(&O);
  freeMatrix(&P);
  freeMatrix(&Q);
  freeMatrix(&R);
  freeMatrix(&S);
  freeMatrix(&T);
  freeMatrix(&U);
  
  return EXIT_SUCCESS;
}

/* Output of MatrixTest */

/*
A:
1: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0) (6, 6.0)
2: (1, 2.0) (2, 4.0) (3, 6.0) (4, 8.0) (5, 10.0) (6, 12.0)
3: (1, 1.0) (2, 2.0) (3, 9.0) (4, 4.0) (5, 5.0) (6, 6.0)
4: (1, 2.0) (2, 4.0) (3, 6.0) (4, 16.0) (5, 10.0) (6, 12.0)
5: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 25.0) (6, 6.0)
6: (1, 2.0) (2, 4.0) (3, 6.0) (4, 8.0) (5, 10.0) (6, 36.0)

B:
1: (1, 2.0) (2, 1.0) (3, 1.0) (4, 1.0) (5, 1.0) (6, 1.0)
2: (1, 1.0) (2, 4.0) (3, 3.0) (4, 4.0) (5, 5.0) (6, 6.0)
3: (1, 3.0) (2, 3.0) (3, 6.0) (4, 3.0) (5, 3.0) (6, 3.0)
4: (1, 1.0) (2, 2.0) (3, 3.0) (4, 8.0) (5, 5.0) (6, 6.0)
5: (1, 5.0) (2, 5.0) (3, 5.0) (4, 5.0) (5, 10.0) (6, 5.0)
6: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0) (6, 12.0)

C = 2.5 * A:
1: (1, 2.5) (2, 5.0) (3, 7.5) (4, 10.0) (5, 12.5) (6, 15.0)
2: (1, 5.0) (2, 10.0) (3, 15.0) (4, 20.0) (5, 25.0) (6, 30.0)
3: (1, 2.5) (2, 5.0) (3, 22.5) (4, 10.0) (5, 12.5) (6, 15.0)
4: (1, 5.0) (2, 10.0) (3, 15.0) (4, 40.0) (5, 25.0) (6, 30.0)
5: (1, 2.5) (2, 5.0) (3, 7.5) (4, 10.0) (5, 62.5) (6, 15.0)
6: (1, 5.0) (2, 10.0) (3, 15.0) (4, 20.0) (5, 25.0) (6, 90.0)

D = A + B:
1: (1, 3.0) (2, 3.0) (3, 4.0) (4, 5.0) (5, 6.0) (6, 7.0)
2: (1, 3.0) (2, 8.0) (3, 9.0) (4, 12.0) (5, 15.0) (6, 18.0)
3: (1, 4.0) (2, 5.0) (3, 15.0) (4, 7.0) (5, 8.0) (6, 9.0)
4: (1, 3.0) (2, 6.0) (3, 9.0) (4, 24.0) (5, 15.0) (6, 18.0)
5: (1, 6.0) (2, 7.0) (3, 8.0) (4, 9.0) (5, 35.0) (6, 11.0)
6: (1, 3.0) (2, 6.0) (3, 9.0) (4, 12.0) (5, 15.0) (6, 48.0)

E = A - A:

F = transpose(B):
1: (1, 2.0) (2, 1.0) (3, 3.0) (4, 1.0) (5, 5.0) (6, 1.0)
2: (1, 1.0) (2, 4.0) (3, 3.0) (4, 2.0) (5, 5.0) (6, 2.0)
3: (1, 1.0) (2, 3.0) (3, 6.0) (4, 3.0) (5, 5.0) (6, 3.0)
4: (1, 1.0) (2, 4.0) (3, 3.0) (4, 8.0) (5, 5.0) (6, 4.0)
5: (1, 1.0) (2, 5.0) (3, 3.0) (4, 5.0) (5, 10.0) (6, 5.0)
6: (1, 1.0) (2, 6.0) (3, 3.0) (4, 6.0) (5, 5.0) (6, 12.0)

G = B * B:
1: (1, 15.0) (2, 18.0) (3, 22.0) (4, 26.0) (5, 30.0) (6, 34.0)
2: (1, 50.0) (2, 71.0) (3, 86.0) (4, 107.0) (5, 130.0) (6, 155.0)
3: (1, 48.0) (2, 60.0) (3, 81.0) (4, 84.0) (5, 96.0) (6, 108.0)
4: (1, 52.0) (2, 71.0) (3, 92.0) (4, 131.0) (5, 140.0) (6, 167.0)
5: (1, 90.0) (2, 110.0) (3, 130.0) (4, 150.0) (5, 195.0) (6, 190.0)
6: (1, 54.0) (2, 75.0) (3, 98.0) (4, 123.0) (5, 150.0) (6, 215.0)

H = copy(A):
1: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0) (6, 6.0)
2: (1, 2.0) (2, 4.0) (3, 6.0) (4, 8.0) (5, 10.0) (6, 12.0)
3: (1, 1.0) (2, 2.0) (3, 9.0) (4, 4.0) (5, 5.0) (6, 6.0)
4: (1, 2.0) (2, 4.0) (3, 6.0) (4, 16.0) (5, 10.0) (6, 12.0)
5: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 25.0) (6, 6.0)
6: (1, 2.0) (2, 4.0) (3, 6.0) (4, 8.0) (5, 10.0) (6, 36.0)

A == H: true
A == B: false
A == A: true
L^T =
1: (1, 1.0) (2, 4.0) (3, 7.0)
2: (1, 2.0) (2, 5.0) (3, 8.0)
3: (1, 3.0) (2, 6.0) (3, 9.0)
2L =
1: (1, 2.0) (2, 4.0) (3, 6.0)
2: (1, 8.0) (2, 10.0) (3, 12.0)
3: (1, 14.0) (2, 16.0) (3, 18.0)
L + M =
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)
L - M =
1: (2, 2.0) (3, 2.0)
2: (1, 4.0) (2, 4.0) (3, 6.0)
3: (1, 6.0) (2, 7.0) (3, 8.0)
L * M =
1: (1, 4.0) (2, 5.0) (3, 4.0)
2: (1, 10.0) (2, 11.0) (3, 10.0)
3: (1, 16.0) (2, 17.0) (3, 16.0)
L copy =
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)
Zeroed out L =
A after makeZero:

*/
