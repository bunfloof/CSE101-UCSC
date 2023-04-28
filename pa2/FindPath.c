/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA1
* FindPath.c 
* FindPath for Graph
*********************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"Graph.h"

#define INF -6
#define NIL -9

int main(int argc, char * argv[]){
  // check command line for correct number of arguments
  if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
  }
  
  // open files for reading and writing 
  FILE *in = fopen(argv[1], "r");
  if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
  }
  
  FILE *out = fopen(argv[2], "w");
  if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
  }

  // start of final
  int n, u, v;
  
  // start of check to suppress warning
  if(fscanf(in, "%d", &n) != 1){
  printf("Error while reading input file");
  exit(1);
  }
  // end of check to suppress warning
  
  Graph G = newGraph(n);
  while (fscanf(in, "%d %d", &u, &v) == 2) {
    if (u == 0 && v == 0) break;
    addEdge(G, u, v);
  }
  
  printGraph(out, G);
  fprintf(out, "\n");
  List L = newList();
  while (fscanf(in, "%d %d", &u, &v) == 2) {
    
    if (u == 0 && v == 0) break;
    BFS(G, u);
    if (getDist(G, v) == INF) {
        fprintf(out, "The distance from %d to %d is infinity\n", u ,v);
        fprintf(out, "No %d-%d path exists\n", u ,v);
    } else {
        fprintf(out, "The distance from %d to %d is %d\n", u, v, getDist(G, v));
        getPath(L, G, v);
        fprintf(out, "A shortest %d-%d path is: ", u, v);
        printList(out, L);
        fprintf(out, "\n");
       
    }
    clear(L);
    fprintf(out, "\n");
  }
  freeList(&L);
  fclose(in);
  fclose(out);
  freeGraph(&G);
  
  return 0;
}
