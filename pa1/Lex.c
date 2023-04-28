/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA1
* Lex.c 
* Lex for List ADT 
*********************************************************************************/ 

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){

   int line_count = 0;
   FILE *in, *out;
   char line[MAX_LEN];
   // char tokenBuffer[MAX_LEN];
   // char* token;

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
      if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }

   out = fopen(argv[2], "w");
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   int init_line_count = 0;
   // read each line of input file
  
   while(fgets(line, MAX_LEN, in) != NULL)  {
     init_line_count++;
    }
   rewind(in); // move to beginning
  
   char **str = (char**)malloc(init_line_count * sizeof(char*));

   while(fgets(line, MAX_LEN, in) != NULL)  {
      str[line_count] = (char*)malloc(MAX_LEN * sizeof(char) * strlen(line));
      strcpy(str[line_count], line);
      line_count++;
   }
  
   List L = newList();
   append(L, 0);
   moveFront(L);
   //moveBack(L);


  for (int i = 1; i < line_count; i++) {
    while (index(L) >= 0) {
      if (strcmp(str[i], str[get(L)]) > 0) {
        moveNext(L);
      } else break;
    }
    if (index(L) >= 0) {
      insertBefore(L, i);
    } else append(L, i);
    moveFront(L);
  }

  while (index(L) >= 0) {
    fprintf(out, "%s", str[get(L)]);
    moveNext(L);
  }
   
   // close files 
   fclose(in);
   fclose(out);

   // to pass valgrind memcheck
   for (int i = 0; i < line_count; i++) {
     free(str[i]);
   }
   freeList(&L);
   free(str);
   // end of to pass valgrind memcheck
   return(0);
}