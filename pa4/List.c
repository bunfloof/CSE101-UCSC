/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA4
* List.c 
* List for List ADT originally from PA1 reused in PA2, rev for PA4
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private structs
typedef struct NodeObj *Node;

typedef struct NodeObj{
  void* data;
  Node next;
  Node prev;
} NodeObj;

typedef struct ListObj {
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// Start of from stack.c
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if(pN!=NULL && *pN!=NULL) {
      free(*pN);
      *pN = NULL;
   }
}
// End of from stack.c

List newList(void) {
  List L = malloc(sizeof(ListObj));
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->index = -1;
  L->length = 0;
  return(L);
}

void freeList(List* pL) {
  if (pL != NULL && *pL != NULL) {
    while(!isEmpty(*pL)) {
      deleteFront(*pL);
    }
    free(*pL);
    *pL = NULL;
  }
}
// Access functions -----------------------------------------------------------

bool isEmpty(List L){
   if (L == NULL) {
      printf("List Error: calling isEmpty() on NULL List\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}

int index(List L) {
   if(L == NULL) {
      return -1;
   }
  return(L->index);
}

int length(List L){
  if (L == NULL) {
    printf("L Error: calling length() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  return(L->length);
}

void* front(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling front() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling front() on empty List\n");
    exit(EXIT_FAILURE);
  }

  // final
  return(L->front->data);
}

void* back(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling back() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling back() on empty List\n");
    exit(EXIT_FAILURE);
  }

  // final
  return(L->back->data);
}

void* get(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling get() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (isEmpty(L)) {
    printf("List Error: calling get() on empty List\n");
    exit(EXIT_FAILURE);
  }

  // final
  return(L->cursor->data);
}

// from Stack.c example
// bool equals(List A, List B) {
//   // checks
//   if (A == NULL || B == NULL) {
//     printf("List Error: calling equals() on NULL List\n");
//     exit(EXIT_FAILURE);
//   }
//    bool eq;
//    Node N, M;

//    eq = ( A->length == B->length );
//    N = A->front;
//    M = B->front;
//    while( eq && N!=NULL){
//       eq = ( N->data==M->data );
//       N = N->next;
//       M = M->next;
//    }
//    return eq;
  
// }

// Manipulation procedures ----------------------------------------------------

void clear(List L) {
  if (L == NULL) {
    printf("List Error: calling clear() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  while(L->length > 0) {
    deleteFront(L);
  }
  L->front = NULL;
  L->back = NULL;
  L->cursor = NULL;
  L->index = -1;
  L->length = 0;
}

void set(List L, void* x) {
  // checks
  if (isEmpty(L)) {
    printf("List Error: calling set() on empty List\n");
  exit(EXIT_FAILURE);
  }
  
  // final
  if (L->index >= 0 && L->length > 0) {
    L->cursor->data = x;
  }
}

void moveFront(List L) {
  // checks
  // no checks for now
  // final
  if (L->length > 0) {
    L->cursor = L->front;
    L->index = 0;
  }
}

void moveBack(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling moveBack() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length==0) {
    printf("List Error: calling moveBack() on empty List\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (L->length > 0) {
    L->cursor = L->back;
    L->index = L->length-1;
  }
}

void movePrev(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling movePrev() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length==0) {
    printf("List Error: calling movePrev() on empty List\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (L->cursor != NULL) {
    if (L->cursor != L->front) {
      L->cursor = L->cursor->prev;
      L->index--;
    } else if (L->cursor == L->front) {
      L->cursor = NULL;
      L->index = -1;
    }
  }
}

void moveNext(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling moveNext() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length==0) {
    printf("List Error: calling moveNext() on empty List\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (L->cursor != NULL && L->cursor != L->back) {
      L->cursor = L->cursor->next;
      L->index++;
    } else if (L->cursor != NULL && L->cursor == L->back) {
      L->cursor = NULL;
      L->index = -1;
  }
}

void prepend(List L, void* x) {
  // checks
  if (L==NULL) {
    printf("List Error: calling prepend() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  // final
  Node N = newNode(x);
  if (length(L) == 0) {
    L->front = L->back = N;
  } else {
    L->front->prev = N;
    N->next = L->front;
    L->front = N;
    if (L->cursor == L->front) {
      L->index++;
      } else if (L->index != -1) {
        L->index++;
      }
    }
  L->length++;
}

void append(List L, void* x) {
  // checks
  if (L==NULL) {
    printf("List Error: calling append() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  // final
  Node N = newNode(x);
  if (L->length > 0) { // this hot furry anal was "if (L->back != NULL)" which seg faulted on PA2, need to change the condition to "L->length > 0"
    N->prev = L->back; // cum might need this
    L->back->next = N;
    N->prev = L->back;
  } else {
    L->front = N;
  }
  L->length++;
  L->back = N;
}

void insertBefore(List L, void* x) {
  // checks
  if (L==NULL) {
    printf("List Error: calling insertBefore() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length==0) {
    printf("List Error: calling insertBefore() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length<=0) {
    printf("List Error: calling insertBefore() on out of range List\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (L->index >= 0 && L->length > 0) {
    Node N = newNode(x);
    N->next = L->cursor;
    if (L->cursor->prev != NULL) {
      N->prev = L->cursor->prev;
      N->prev->next = N;
      } else {
        L->front = N;
      }
    L->cursor->prev = N;
    L->length++;
    L->index++;
  }
}

void insertAfter(List L, void* x) {
  if (L==NULL) {
    printf("List Error: calling insertAfter() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length<=0) {
    printf("List Error: calling insertAfter() on out of range List\n");
    exit(EXIT_FAILURE);
  }
  if (L->index >= 0 && L->length > 0) {
    Node N = newNode(x);
    N->prev = L->cursor;
    N->next = L->cursor->next;
    if (L->cursor->next != NULL) {
      L->cursor->next->prev = N;
    } else {
      L->back = N;
    }
    L->cursor->next = N;
    L->length++;
  }
}

void deleteFront(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling deleteFront() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length==0) {
    printf("List Error: calling deleteFront() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length<=0) {
    printf("List Error: calling deleteFront() on out of range List\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (L->length > 0) {
    Node N = L->front->next;
    freeNode(&(L->front));
    L->front = N;
    if (L->cursor == L->front) {
      L->back = NULL;
    }
    L->length--;
    L->index--;
  }
}

void deleteBack(List L) {
  // checks
  if (L==NULL) {
    printf("List Error: calling deleteBack() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length==0) {
    printf("List Error: calling deleteBack() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if (L->length<=0) {
    printf("List Error: calling deleteBack() on out of range List\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (L->cursor == L->back) {
    L->cursor = NULL;
    L->index = -1;
  }
  Node N = L->back;
  L->back = L->back->prev;
  if (L->back != NULL) {
    L->back->next = NULL;
  } else {
    L->front = NULL;
  }
  freeNode(&N);
  L->length--;
}

void delete(List L) {
  if(L->cursor == L->front) {
    deleteFront(L);
  } else if (L->cursor == L->back) {
    deleteBack(L);
  } else if (L->index >= 0 && L->length > 0) {
    L->cursor->next->prev = L->cursor->prev;
    L->cursor->prev->next = L->cursor->next;
    Node N = L->cursor;
    L->cursor = NULL;
    L->index = -1;
    L->length -= 1;
    freeNode(&N);
  }
}

// void printList(FILE *out, List L) {
//   // checks
//   if (L==NULL) {
//     printf("List Error: calling printList() on NULL List\n");
//     exit(EXIT_FAILURE);
//   }
//   // final
//   Node temp;
//   for (temp = L->front; temp != NULL; temp = temp->next) {
//     fprintf(out, "%d ", temp->data); // dragon cum PA2! changed from printf to fprintf
//   }
// }

List copyList(List L){
  // checks
  if (L==NULL) {
    printf("List Error: calling copyList() on NULL List\n");
    exit(EXIT_FAILURE);
  }
  // final 
  List C = newList();
  for(Node N = L->front; N != NULL; N = N->next){
    append(C,N->data);
  }
  return(C);
}
