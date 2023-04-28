/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA2
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
#define NIL -9
// end of to satisfy autograder

// start this is a public struct
typedef struct GraphObj* Graph;
// end this is a public struct

// start of pa2.pdf modified
/*** Constructors-Destructors ***/
Graph newGraph(int n);     // returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
void freeGraph(Graph* pG); // frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL. 

/*** Access functions ***/
int getOrder(Graph G);         // Returns the number of vertices
int getSize(Graph G);          // Returns the number of edges
int getSource(Graph G);        // Returns the source of the graph
int getParent(Graph G, int u); // Returns the parent of vertex u
int getDist(Graph G, int u);    // Returns the from source distance to vertex u
void getPath(List L, Graph G, int u); // Appends to List L the vertices of shortest path in Graph G from source to vertex u

/*** Manipulation procedures ***/
void makeNull(Graph G);              // Deletes all edges of Graph G
void addEdge(Graph G, int u, int v); // Inserts new edge joining vertex u to v
void addArc(Graph G, int u, int v);  // Inserts a new directed edge from vertex u to v
void BFS(Graph G, int s);            // Runs the BFS algorithm on Graph G with source S

/*** Other operations ***/
void printGraph(FILE* out, Graph G); // Prints the adjency list representation of Grpah G to FILE* out

// end of pa2.pdf modified

// start of faculty Alex Rudnick's idea
// Idea for the UNUSED macro from Stack Overflow user mtvec. Thanks!
// https://stackoverflow.com/a/3599170
#define UNUSED(x) (void)(x)
// end of faculty Alex Rudnick's idea

#endif