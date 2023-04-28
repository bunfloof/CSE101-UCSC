/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA1
* ListTest.c 
* Test client for List ADT 
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   List D = newList();
   List E = newList();
   int i;

   // card number, date, and cvv
   int mastercard[] = {5571, 6219, 8091, 1342, 10, 27, 308};

   for(i=0; i<sizeof(mastercard)/sizeof(mastercard[0]); i++) {
      append(A,mastercard[i]);
      prepend(B,mastercard[i]);
   }

   // phone number, social security number, 69, 420, and zip code
   int personal[] = {408, 216, 8731, 450, 60, 3078, 69, 420, 95064};

   for(i=0; i<sizeof(personal)/sizeof(personal[0]); i++) {
      append(D,personal[i]);
      prepend(E,personal[i]);
   }

   printList(stdout,A); 
   printf("\n");
   printList(stdout,B); 
   printf("\n");
   printList(stdout,D); 
   printf("\n");
   printList(stdout,E); 
   printf("\n");

   deleteFront(D);
   deleteFront(E);
   deleteBack(D);
   deleteBack(D);
   //deleteFront(A);

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");
   for(moveBack(D); index(D)>=0; movePrev(D)){
      printf("%d ", get(D));
   }
   printf("\n");
   for(moveBack(D); index(D)>=0; movePrev(D)){
      printf("%d ", get(D));
   }
  
  
   printf("\n");
   C = copyList(A);
   printf("%s\n", equals(A,B)?"true":"false");
   printf("%s\n", equals(B,C)?"true":"false");
   printf("%s\n", equals(C,A)?"true":"false");


   moveFront(A);
   for(i=0; i<2; i++) {
     moveNext(A);
   }
  
   insertBefore(A, -1);

   // test cursors

   //insertBefore(D, -69);

   insertBefore(E, -5);
   printList(stdout,D);
   printf("\n");
   printList(stdout,E);
   printf("\n");
   printf("%d\n", length(D));
   printf("%d\n", length(E));

   for(i=0; i<2; i++) {
     moveNext(A);
   }     
     
   insertAfter(A, -2);
  
   for(i=0; i<2; i++) {
     movePrev(A);
   }
  
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);
   freeList(&D);
   freeList(&E);
   return(0);
}

/*
Output of this program:
5571 6219 8091 1342 10 27 308 
308 27 10 1342 8091 6219 5571 
408 216 8731 450 60 3078 69 420 95064 
95064 420 69 3078 60 450 8731 216 408 
5571 6219 8091 1342 10 27 308 
5571 6219 8091 1342 10 27 308 
69 3078 60 450 8731 216 
69 3078 60 450 8731 216 
false
false
true
216 8731 450 60 3078 69 
420 69 3078 60 450 8731 216 408 
6
8
5571 6219 -1 1342 10 -2 27 308 
8
0
*/