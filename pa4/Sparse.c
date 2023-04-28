/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA3
* FindComponents.c
* FindComponents for Graph
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "Matrix.h"

int main(int argc, char *argv[]) {
  // check command line for correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: <input file> <output file>\n");
    exit(EXIT_FAILURE);
  }
  // open files for reading and writing
  FILE *in = fopen(argv[1], "r");
  if (in == NULL) {
    printf("Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }

  FILE *out = fopen(argv[2], "w");
  if (out == NULL) {
    printf("Unable to open file %s for writing\n", argv[2]);
    exit(1);
  }

  int n, a, b;
  // warning suppressor
  if (fscanf(in, "%i %i %i", &n, &a, &b) == 1) {
    printf("Error while reading input file");
    //exit(1);
  }
  
  Matrix A = newMatrix(n);
  Matrix B = newMatrix(n);
  
  int row, col;
  double val;
  for (int i = 0; i < a; i++) {
    // warning suppressor
    if (fscanf(in, "%i %i %lf", &row, &col, &val) == 1) {
      printf("Error while reading input file");
      //exit(1); 
    }
    changeEntry(A, row, col, val);
  }

  for (int i = 0; i < b; i++) {
    // warning suppressor
    if (fscanf(in, "%i %i %lf", &row, &col, &val) == 1) {
      printf("Error while reading input file");
      //exit(1);      
    }
    changeEntry(B, row, col, val);
  }

  fprintf(out, "A has %i non-zero entries:\n", NNZ(A));
  printMatrix(out, A);
  fprintf(out, "\n");

  fprintf(out, "B has %i non-zero entries:\n", NNZ(B));
  printMatrix(out, B);
  fprintf(out, "\n");  

  Matrix C = scalarMult(1.5, A);
  fprintf(out, "(1.5)*A =\n");
  printMatrix(out, C);
  fprintf(out, "\n");

  Matrix D = sum(A, B);
  fprintf(out, "A+B =\n");
  printMatrix(out, D);
  fprintf(out, "\n");

  Matrix E = sum(A, A);
  fprintf(out, "A+A =\n");
  printMatrix(out, E);
  fprintf(out, "\n");

  Matrix F = diff(B, A);
  fprintf(out, "B-A =\n");
  printMatrix(out, F);
  fprintf(out, "\n"); 

  Matrix G = diff(A, A);
  fprintf(out, "A-A =\n");
  printMatrix(out, G);
  fprintf(out, "\n"); 

  Matrix H = transpose(A);
  fprintf(out, "Transpose(A) =\n");
  printMatrix(out, H);
  fprintf(out, "\n"); 

  Matrix I = product(A, B);
  fprintf(out, "A*B =\n");
  printMatrix(out, I);
  fprintf(out, "\n"); 

  Matrix J = product(B, B);
  fprintf(out, "B*B =\n");
  printMatrix(out, J);
  fprintf(out, "\n"); 

  // do not touch here
  fclose(in);
  fclose(out);

  freeMatrix(&A);
  freeMatrix(&B);
  freeMatrix(&C);
  freeMatrix(&D);
  freeMatrix(&E);
  freeMatrix(&F);
  freeMatrix(&G);
  freeMatrix(&H);
  freeMatrix(&I);
  freeMatrix(&J);
  
  return 0;
}