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
#include"Graph.h"

int main(int argc, char *argv[]) {
  // check command line for correct number of arguments
  if (argc != 3) {
    fprintf(stderr, "Usage: <input file> <output file\n");
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

  // start of final
  int n, u, v;

  // start of check to suppress warning
  if (fscanf(in, "%d", &n) != 1) {
    printf("Error while reading input file");
    exit(1);
  }
  // end of check to suppress warning

  Graph G = newGraph(n);
  while (fscanf(in, "%d %d", &u, &v) == 2) {
    if (u == 0 && v == 0) break;
    addArc(G, u, v);
  }

  // Printing part
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, G);
  fprintf(out, "\n");

  // do not done here

  List stack = newList();
  for (int i = 1; i <= getOrder(G); i++) {
      append(stack, i);
  }
  
  Graph T = transpose(G);
  DFS(G, stack);
  DFS(T, stack);

  int ctrack = 0;
  List *sstack = malloc(sizeof(List) * (getOrder(G) + 1));
  
  moveBack(stack);
  sstack[ctrack] = newList();
  for (int j = length(stack) - 1; j >= 0; j--) {
    int x = get(stack);
    if (getParent(T, x) == NIL) {
      append(sstack[ctrack], x);
      ctrack++;
      if (ctrack <= getOrder(G)) sstack[ctrack] = newList(); // maws
    } else {
      append(sstack[ctrack], x);
    }
    movePrev(stack);
  }
  
  fprintf(out, "G contains %d strongly connected components:\n", ctrack);
  for (int i = 0; i < ctrack; i++) {
    moveBack(sstack[i]);
    fprintf(out, "Component %d:", (i + 1));
    for (int k = length(sstack[i]) - 1; k >= 0; k--) {
      fprintf(out, " %d", get(sstack[i]));
      movePrev(sstack[i]);
    }
    fprintf(out, "\n");
  }

  // do not touch here
  fclose(in);
  fclose(out);
  for (int i = 0; i < ctrack + 1; i++) {
    freeList(&(sstack[i]));
  }
  free(sstack);
  freeGraph(&T);
  freeList(&stack);
  freeGraph(&G);
  
  return 0;
}
