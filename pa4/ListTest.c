/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA4
* ListTest.c
* Test Client for List ADT
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char *argv[]) {
  List A = newList();
  List B = newList();
  List C = newList();
  int X[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  int Y[] = {11, 12, 13, 14, 15};
  int Z[] = {16, 17, 18, 19, 20};
  int i, u = -1, v = -2, w = -3;
  bool equal;

  // Test append, prepend, and isEmpty
  for (i = 0; i < 10; i++) {
    append(A, &X[i]);
    prepend(B, &X[i]);
  }
  printf("List A is empty: %s\n", isEmpty(A) ? "true" : "false");
  printf("List B is empty: %s\n", isEmpty(B) ? "true" : "false");

  // Test length, front, back, and get
  printf("List A length: %d\n", length(A));
  printf("List B length: %d\n", length(B));
  printf("List A front: %d\n", *(int *)front(A));
  printf("List B front: %d\n", *(int *)front(B));
  printf("List A back: %d\n", *(int *)back(A));
  printf("List B back: %d\n", *(int *)back(B));
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
    printf("%d ", *(int *)get(A));
  }
  printf("\n");
  
  // Test shallow copy and clear
  moveFront(A);
  while( index(A)>=0 ){
    append(C, get(A));
    moveNext(A);
  }
  // print the copy in forward direction
  for(moveFront(C); index(C)>=0; moveNext(C)){
    printf("%d ", *(int*)get(C));
  }
  printf("\n");
  clear(A);
  printf("List C length: %d\n", length(C));
  printf("Clearing List A\n");
  // clear(A);
  printf("List A is empty: %s\n", isEmpty(A) ? "true" : "false");
  printf("List C length: %d\n", length(C));

  //Test set, moveFront, moveBack, movePrev, and moveNext
  moveFront(B);
  for (i = 0; i < 3; i++) {
    moveNext(B);
  }
  printf("Index of B after 3 moves next: %d\n", index(B));
  //set(B, &u);
  for (moveFront(B); index(B) >= 0; moveNext(B)) {
      printf("%d ", *(int *)get(B));
  }
  printf("\n");
  for (moveBack(B); index(B) >= 0; movePrev(B)) {
      printf("%d ", *(int *)get(B));
  }
  printf("\n");
  moveFront(C);

  for (i = 0; i < 7; i++) {
    moveNext(C);
  }
  printf("Index of C after 7 moves next: %d\n", index(C));
  for (i = 0; i < 3; i++) {
    movePrev(C);
  }
  printf("Index of C after 3 moves prev: %d\n", index(C));

  // Test insertBefore, insertAfter, deleteFront, deleteBack, and delete
  for (i = 0; i < 5; i++) {
      append(A, &Y[i]);
  }
  for (i = 0; i < 5; i++) {
      prepend(C, &Z[i]);
  }
  insertBefore(A, &u);
  insertAfter(A, &v);
  insertBefore(B, &w);
  printf("List A after inserts: ");
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
      printf("%d ", *(int *)get(A));
  }
  printf("\n");
  printf("List B after insertBefore: ");
  for (moveFront(B); index(B) >= 0; moveNext(B)) {
      printf("%d ", *(int *)get(B));
  }
  printf("\n");
  printf("List C before deletes: ");
  for (moveFront(C); index(C) >= 0; moveNext(C)) {
      printf("%d ", *(int *)get(C));
  }
  printf("\n");
  deleteFront(A);
  deleteBack(A);
  delete(A);
  deleteFront(B);
  deleteBack(B);
  delete(B);
  delete(C);
  printf("List A after deletes: ");
  for (moveFront(A); index(A) >= 0; moveNext(A)) {
      printf("%d ", *(int *)get(A));
  }
  printf("\n");
  printf("List B after deletes: ");
  for (moveFront(B); index(B) >= 0; moveNext(B)) {
      printf("%d ", *(int *)get(B));
  }
  printf("\n");
  printf("List C after deletes: ");
  for (moveFront(C); index(C) >= 0; moveNext(C)) {
      printf("%d ", *(int *)get(C));
  }
  printf("\n");

  //Test equals
  equal = (length(A) == length(C));
  moveFront(A);
  moveFront(C);
  while(index(A) >=0 && equal){
    equal = (get(A) == get(C));
    moveNext(A);
    moveNext(C);
  }
  printf("List A is equal to List C: %s\n", equal ? "true" : "false");

  // Free memory
  freeList(&A);
  freeList(&B);
  freeList(&C);

  return 0;
}
/* Output of ListTest */
/*
List A is empty: false
List B is empty: false
List A length: 10
List B length: 10
List A front: 1
List B front: 10
List A back: 10
List B back: 1
1 2 3 4 5 6 7 8 9 10 
1 2 3 4 5 6 7 8 9 10 
List C length: 10
Clearing List A
List A is empty: true
List C length: 10
Index of B after 3 moves next: 3
10 9 8 7 6 5 4 3 2 1 
1 2 3 4 5 6 7 8 9 10 
Index of C after 7 moves next: 7
Index of C after 3 moves prev: 4
List A after inserts: 11 12 13 14 15 
List B after insertBefore: 10 9 8 7 6 5 4 3 2 1 
List C before deletes: 20 19 18 17 16 1 2 3 4 5 6 7 8 9 10 
List A after deletes: 12 13 14 
List B after deletes: 9 8 7 6 5 4 3 2 
List C after deletes: 20 19 18 17 16 1 2 3 4 5 6 7 8 9 10 
List A is equal to List C: false
*/