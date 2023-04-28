/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA4
* Matrix.c 
* Matrix for Matrix ADT
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Matrix.h"
#include "List.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj {
  int col;
  double val;
} EntryObj;

typedef struct MatrixObj {
  int size;
  int NNZ;
  List *elements;
} MatrixObj;

// newMatrix() returns a reference to a new n*n Matrix object in the zero state.
Matrix newMatrix(int n) {
  if (n <= 0) {
printf("Matrix Error: calling newMatrix() on NULL Matrix reference\n");    
  exit(EXIT_FAILURE);
    }
  Matrix M = malloc(sizeof(MatrixObj));
  M->elements = malloc((n+1) * sizeof(List));
  for (int i = 1; i <= n; i++) {
    (M->elements)[i] = newList();
  }
  M->size = n;
  M->NNZ = 0;

  return M;
}
// Start of private functions for entry

Entry newEntry(double val, int col) {
  Entry E = malloc(sizeof(EntryObj));
  E->val = val;
  E->col = col;
  return E;
}

void freeEntry(Entry* pE) {
  if (pE != NULL && *pE != NULL) {
    free(*pE);
    *pE = NULL;
  }
}

// freeMatrix() frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
  if (pM != NULL && *pM != NULL) {
    for (int i = 1; i <= size(*pM); i++) {
      List element = (*pM)->elements[i];
      for (moveFront(element); index(element) >= 0; moveNext(element)) {
        Entry E = get(element);
        Entry temp = E;
        freeEntry(&temp);
        //freeEntry(&E);
        E = NULL;
        set(element, NULL);
      }
      freeList(&((*pM)->elements[i]));
    }
    free((*pM)->elements);
    (*pM)->elements = NULL;
    free(*pM);
    *pM = NULL;
  }
}


/*** Access functions ***/

// size() return the size of square Matrix M.
int size(Matrix M) {
  if (M == NULL) {
    printf("Matrix Error: calling size() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return M->size;
}

// NNZ() return the number of non-zero elements in M.
int NNZ(Matrix M) {
  if (M == NULL) {
    printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  return M->NNZ;  
}

// equals() return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
  // checks
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling equals() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (A->size != B->size) return 0;

  for (int i = 1; i <= size(A); i++) {
    if (length(A->elements[i]) != length(B->elements[i])) return 0;
    
    for (moveFront(A->elements[i]), moveFront(B->elements[i]);
    index(A->elements[i]) >= 0 && index(B->elements[i]) >= 0;
    moveNext(A->elements[i]), moveNext(B->elements[i])) {
      Entry Ae = get(A->elements[i]);
      Entry Be = get(B->elements[i]);
      if (Ae->col != Be->col || Ae->val != Be->val) return 0;
    }
  }
  return 1;
}

/*** Manipulation procedures ***/

// makeZero() Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
  // checks
  if (M == NULL) {
    printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  // final
  for (int i = 1; i <= size(M); i++) {
    List row = M->elements[i];
    for (moveFront(row); index(row) >= 0; moveNext(row)) {
      Entry e = get(row);
      freeEntry(&e);
    }
    clear(row);
  }

  M->NNZ = 0;
}

// changeEntry changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
  // checks
  if (M == NULL) {
    printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);    
  }
  if (i < 1 || i > size(M) || j < 1 || j > size(M)) {
    printf("Matrix Error: calling changeEntry() with invalid i or j indices\n");
    exit(EXIT_FAILURE);
  }
  // final
  List L = M->elements[i];
  moveFront(L);
  Entry E = NULL;

  while (index(L) >= 0 && ((Entry)get(L))->col < j) {
    moveNext(L);
  }

  if (index(L) >= 0 && ((Entry)get(L))->col == j) {
    E = (Entry)get(L);
    if (x == 0) {
      delete(L);
      M->NNZ--;
	  freeEntry(&E);
    } else {
      E->val = x;
    }
  } else if (x != 0) {
    E = malloc(sizeof(EntryObj));
    E->col = j;
    E->val = x;
    if (index(L) < 0) append(L, E);
    else insertBefore(L, E);
    M->NNZ++;
  }
}

/*** Matrix Arithmetic operations ***/

// copy() returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
  if (A == NULL) {
    printf("Matrix Error: calling copy() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);    
  }
  Matrix M = newMatrix(size(A));

  for (int i = 1; i <= size(A); i++) {
    List element = A->elements[i];
    for (moveFront(element); index(element) >= 0; moveNext(element)) {
      Entry E = (Entry) get((A->elements)[i]);
      append((M->elements)[i], newEntry(E->val, E->col));
      M->NNZ++;
    }
  }
  M->NNZ = A->NNZ;
  return M;
}

// transpose() returns a reference to a new Matrix object representing the transpose of A.
Matrix transpose(Matrix A) {
  if (A == NULL) {
    printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);    
  }
  Matrix M = newMatrix(size(A));

  for (int i = 1; i <= size(A); i++) {
    List element = A->elements[i];
    for (moveFront(element); index(element) >= 0; moveNext(element)) {
      Entry E = (Entry) get((A->elements)[i]);
      append((M->elements)[E->col], newEntry(E->val, i));
      M->NNZ++;
    }
  }
  M->NNZ = A->NNZ;
  return M;
}

// scalarMult() returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
  if (A == NULL) {
    printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);    
  }
  Matrix M = newMatrix(size(A));

  for (int i = 1; i <= size(A); i++) {
    List element = A->elements[i];
    for (moveFront(element); index(element) >= 0; moveNext(element)) {
      Entry E = (Entry) get((A->elements)[i]);
      append((M->elements)[i], newEntry(x * E->val, E->col));
      M->NNZ++;
    }
  }
  //M->NNZ = A->NNZ; // do not uncomment ples
  return M;
}

// sum() returns a reference to a new Matrix object representing A+B.
Matrix sum(Matrix A, Matrix B) {
  // checks
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling sum() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Matrix Error: calling sum() on invalid Matrix sizes\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (equals(A, B)) return scalarMult(2, A);

  Matrix C = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    int j = 0;
    for (moveFront(A->elements[i]), moveFront(B->elements[i]);
    index(A->elements[i]) >= 0 || index(B->elements[i]) >= 0;
    ) {
      Entry a = (index(A->elements[i]) >= 0) ? (Entry)get(A->elements[i]) : NULL;
      Entry b = (index(B->elements[i]) >= 0) ? (Entry)get(B->elements[i]) : NULL;
      if (A == NULL && B == NULL) break;
      if (a != NULL && b != NULL && a->col == b->col) {
        double sum = a->val + b->val;
        if (sum != 0) {
          Entry e = newEntry(sum, a->col);
          append(C->elements[i], e);
          j++;
        }
        moveNext(A->elements[i]);
        moveNext(B->elements[i]);
      } else if (b == NULL || (a != NULL && a->col < b->col)) { // A
        Entry e = newEntry(a->val, a->col);
        append(C->elements[i], e);
        j++;
        moveNext(A->elements[i]);
      } else { // B
        Entry e = newEntry(b->val, b->col);
        append(C->elements[i], e);
        j++;
        moveNext(B->elements[i]);
      }
    }
    C->NNZ += j;
  }
  return C;
}

/**  
Notes for myself:

Edit: Falling back to less optimized code due to incorrect NNZ value.

Freeing memory is not needed for sum().
Freeing memory is needed for diff().

Memory leak in the diff function is due to not deallocating memory for the Entry struct created by newEntry() function calls. Fixed the memory leak by deallocating the memory for each Entry struct created by calling the freeEntry() function after the changeEntry() function.

No need to add freeEntry for sum() function because the entries are allocated on the fly using the newEntry() function and are then immediately appended to the matrix. Since they are no longer being used after they are added to the matrix, there is no need to free them explicitly. 

Matrix diff(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling diff() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }

  if (equals(A, B)) {
    Matrix C = newMatrix(size(A));
    return C;
  }

  Matrix C = newMatrix(size(A));
  for (int i = 1; i <= size(A); i++) {
    int j = 0;
    for (moveFront(A->elements[i]), moveFront(B->elements[i]);
         index(A->elements[i]) >= 0 || index(B->elements[i]) >= 0;
         ) {
      Entry a = (index(A->elements[i]) >= 0) ? (Entry)get(A->elements[i]) : NULL;
      Entry b = (index(B->elements[i]) >= 0) ? (Entry)get(B->elements[i]) : NULL;
      Entry e;
      if (a == NULL) {
        e = newEntry(-b->val, b->col);
        moveNext(B->elements[i]);
        j++;
      } else if (b == NULL) {
        e = newEntry(a->val, a->col);
        moveNext(A->elements[i]);
        j++;
      } else if (a->col == b->col) {
        double diff = a->val - b->val;
        if (diff != 0) {
          e = newEntry(diff, a->col);
          moveNext(A->elements[i]);
          moveNext(B->elements[i]);
          j++;
        } else {
          moveNext(A->elements[i]);
          moveNext(B->elements[i]);
          continue;
        }
      } else if (a->col < b->col) {
        e = newEntry(a->val, a->col);
        moveNext(A->elements[i]);
        j++;
      } else {
        e = newEntry(-b->val, b->col);
        moveNext(B->elements[i]);
        j++;
      }
      changeEntry(C, i, e->col, e->val);
      freeEntry(&e); // adding this line to deallocate memory
    }
    C->NNZ += j;
  }
  return C;
}

**/

// diff() returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
  // checks
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling sum() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }
  if (size(A) != size(B)) {
    printf("Matrix Error: calling sum() on invalid Matrix sizes\n");
    exit(EXIT_FAILURE);
  }
  // final

  if (equals(A, B)) return newMatrix(size(A));

  Matrix C = newMatrix(size(A));

  for (int i = 1; i <= size(A); i++) {
    moveFront(A->elements[i]);
    moveFront(B->elements[i]);

    for (int j = 0; j < length(A->elements[i]) + length(B->elements[i]); j++) {
      if (index(A->elements[i]) >= 0 && index(B->elements[i]) >= 0) {
        Entry ae = (Entry) get(A->elements[i]);
        Entry be = (Entry) get(B->elements[i]);

        if (ae->col == be->col) {
          double diff = ae->val - be->val;
          if (diff != 0) {
            append(C->elements[i], newEntry(diff, ae->col));
            C->NNZ++;
          }
          moveNext(A->elements[i]);
          moveNext(B->elements[i]);
        }
        else if (ae->col < be->col) {
          append(C->elements[i], newEntry(ae->val, ae->col));
          C->NNZ++;
          moveNext(A->elements[i]);
        } else {
          append(C->elements[i], newEntry(-1 * be->val, be->col));
          C->NNZ++;
          moveNext(B->elements[i]);
        }
      }
      else if (index(A->elements[i]) >= 0) {
        Entry ae = (Entry) get(A->elements[i]);
        append(C->elements[i], newEntry(ae->val, ae->col));
        C->NNZ++;
        moveNext(A->elements[i]);
      }
      else if (index(B->elements[i]) >= 0) {
        Entry be = (Entry) get(B->elements[i]);
        append(C->elements[i], newEntry(-1 * be->val, be->col));
        C->NNZ++;
        moveNext(B->elements[i]);
      }
    }
  }
  return C;
}

// private helper function vectorDot for product function
double vectorDot(List P, List Q) {
    double sum = 0;
    moveFront(P);
    moveFront(Q);
    while(index(P) >= 0 && index(Q) >= 0) {
      Entry e1 = (Entry) get(P);
      Entry e2 = (Entry) get(Q);
      if (e1->col == e2->col) {
        sum += (e1->val * e2->val);
        moveNext(P);
        moveNext(Q);
      } else if (e1->col < e2->col) moveNext(P);
        else moveNext(Q);
  }
    return sum;
}

// product() returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
  if (A == NULL || B == NULL) {
    printf("Matrix Error: calling diff() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);
  }

  Matrix T = transpose(B);
  Matrix P = newMatrix(size(A));
  
  for (int i = 1; i <= size(P); i++) {
    if (length(A->elements[i]) == 0) { // to suppress warning
      // do nutting nut nut i nutted
    } else {
      for (int j = 1; j <= size(P); j++) {
        if (length(T->elements[j]) != 0) {
          double p = vectorDot(A->elements[i], T->elements[j]);
          if (p != 0) {
            Entry e = newEntry(p, j);
            append(P->elements[i], e);
            P->NNZ += 1;
          }
        }
      }
    }
  }
  freeMatrix(&T);
  return P;
}

// printMatrix prints the matrix
void printMatrix(FILE* out, Matrix M) {
  if (M == NULL) {
    printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
    exit(EXIT_FAILURE);    
  }

  for (int i = 1; i <= size(M); i++) {
    if (length(M->elements[i]) != 0) {
      fprintf(out, "%i:", i);
      for (moveFront((M->elements)[i]); index((M->elements)[i]) >= 0; moveNext((M->elements)[i])) {
        Entry E = (Entry) get((M->elements)[i]);
        fprintf(out, " (%i, %.1lf)", E->col, E->val);
      }
      fprintf(out, "\n");
    }
  }
}
