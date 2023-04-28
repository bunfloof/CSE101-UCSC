/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA3
* Graph.h
* Graph header for Graph
*********************************************************************************/ 
// start of referenced from Queue.h example
#ifndef GRAPH_H_INCLUDE_
#define GRAPH_H_INCLUDE_
// end of referenced from Queue.h example

#include<stdbool.h>
#include "List.h"

// start of to satisfy autograder
#define INF -6
#define NIL 0
#define UNDEF -1
// end of to satisfy autograder

// start this is a public struct
typedef struct GraphObj* Graph;
// end this is a public struct

// PA3 consists of a total of 13 functions--5 of which are new functions: getDiscover, getFinish, DFS, transpose, and copyGraph; and reuses 8 functions from PA2: newGraph, freeGraph, getOrder, getSize, getParent, addEdge, addArc, and printGraph.

/*** Constructors-Destructors ***/
Graph newGraph(int n);     // returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges. PA2 funct reuse for PA3
void freeGraph(Graph* pG); // frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL. PA2 funct reuse for PA3

/*** Access functions ***/
int getOrder(Graph G);         // Returns the number of vertices PA2 funct resuse for PA3
int getSize(Graph G);          // Returns the number of edges PA2 funct resuse for PA3
int getParent(Graph G, int u); // Returns the parent of vertex PA2 funct reuse for PA3
int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) PA3 new funct*/
int getFinish(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) PA3 new funct*/

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v); // Inserts new edge joining vertex u to v PA2 funct reuse for PA3
void addArc(Graph G, int u, int v);  // Inserts a new directed edge from vertex u to v PA2 funct reuse for PA3
void DFS(Graph G, List S);           // Runs the DFS algorithm on Graph G with source S PA3 new funct
/*** Other operations ***/
Graph transpose(Graph G);            // Transpose PA3 new funct
Graph copyGraph(Graph G);            // Prints graph PA3 new funct
void printGraph(FILE* out, Graph G); // Prints the adjency list representation of Grpah G to FILE* out PA2 funct reuse for PA3

// start of faculty Alex Rudnick's idea
// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
// end of faculty Alex Rudnick's idea

#endif