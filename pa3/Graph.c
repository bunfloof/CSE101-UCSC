/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA3
* Graph.c 
* Graph for Graph
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"

#define INF -6
#define NIL 0
#define UNDEF -1

typedef struct GraphObj{
	List *neighbors;
	char *color;
	int *parent;
	int *discovered;
  int *finished;
	int order;
	int size;
} GraphObj;

void Visit(Graph G, int x, int *time);

/*** Constructors-Destructors ***/

// Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	assert(G!=NULL);
	
	G->neighbors = malloc(sizeof(List*) * (n + 1));
 	G->color = malloc(sizeof(char*) * (n + 1));
 	G->parent = malloc(sizeof(int*) * (n + 1));
  G->discovered = malloc(sizeof(int*) * (n + 1)); 
  G->finished = malloc(sizeof(int*) * (n + 1));
	for (int i = 1; i <= n; i++) {
    G->neighbors[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
    G->discovered[i] = UNDEF; 
    G->finished[i] = UNDEF;
	}

  G->order = n;
  G->size = 0;
  
	return G;
}
// Function freeGraph frees all heap memory associated with the Graph *pG, then sets the handle *pG to NULL.
void freeGraph(Graph* pG) { 
	if (pG != NULL && *pG != NULL){
		for (int i = 1; i <= (*pG)->order; i++) {
      freeList(&(*pG)->neighbors[i]);
    }
		free((*pG)->neighbors);
		free((*pG)->color);
		free((*pG)->parent);
    free((*pG)->finished);
    free((*pG)->discovered);
		free(*pG);
    *pG = NULL;
	}
}

/*** Access functions ***/
// Function getOrder eturns the number of vertices
int getOrder(Graph G) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling getOrder() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  // final
  return(G->order);
}

// Function getSize returns the number of edges
int getSize(Graph G) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling getSize() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  // final
  return(G->size);
}

// Function getParent returns the parent of vertex u in the BFS tree created by BFS(), or NIL if BFS() has not yet been called.
// precondition 1 <= u <= getOrder(G).
int getParent(Graph G, int u) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling getSource() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  if (1 > u || u > getOrder(G)) {
    printf("Graph Error: calling getSource() on invalid vertex\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (u >= 1 && u <= G->order) {
    return(G->parent[u]);
  } else {
    printf("Graph Error: calling getSource() unknown error\n");
    exit(EXIT_FAILURE);
  }
}

// precondition 1 <= u <= getOrder(G).
int getDiscover(Graph G, int u) {
  if (G==NULL) {
    printf("Graph Error: calling getDiscover() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  if (1 > u || u > getOrder(G)) {
    printf("Graph Error: calling getDiscover() on invalid vertex\n");
    exit(EXIT_FAILURE);
  }
  return(G->discovered[u]);
}

// precondition 1 <= u <= getOrder(G).
int getFinish(Graph G, int u) {
  if (G==NULL) {
    printf("Graph Error: calling getFinish() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  if (1 > u || u > getOrder(G)) {
    printf("Graph Error: calling getFinish() on invalid vertex\n");
    exit(EXIT_FAILURE);
  }
  return(G->finished[u]);
}

/*** Manipulation procedures ***/

// Function addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
void addEdge(Graph G, int u, int v) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling addEdge() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  if (getOrder(G) < 1) {
    printf("Graph Error: calling addEdge() on invalid vertex\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling addEdge() on invalid vertex u\n");
    exit(EXIT_FAILURE);  
  }
  if (v < 1 || v > getOrder(G)) {
    printf("Graph Error: calling addEdge() on invalid vertex v\n");
    exit(EXIT_FAILURE);
  }
  // COMMENTED OUT for PA3
  // if (u == v) {
  //   printf("Graph Error: calling addEdge() on invalid vertex u and v\n");
  //   exit(EXIT_FAILURE);
  // }
  // final
  addArc(G, u, v);
  addArc(G, v, u);
  G->size--;
}

// Function addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
void addArc(Graph G, int u, int v) {
 // checks
  if (G==NULL) {
    printf("Graph Error: calling addArc() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  if (getOrder(G) < 1) {
    printf("Graph Error: calling addArc() on invalid vertex\n");
    exit(EXIT_FAILURE);
  }
  if (u < 1 || u > getOrder(G)) {
    printf("Graph Error: calling addArc() on invalid vertex u\n");
    exit(EXIT_FAILURE);  
  }
  if (v < 1 || v > getOrder(G)) {
    printf("Graph Error: calling addArc() on invalid vertex v\n");
    exit(EXIT_FAILURE);
  }
  // COMMENTED OUT for PA3
  // if (u == v) {
  //   printf("Graph Error: calling addEdge() on invalid vertex u and v\n");
  //   exit(EXIT_FAILURE);
  // }
  // final
  if (length(G->neighbors[u]) == 0) {
    append(G->neighbors[u], v);
  } else {
    moveFront(G->neighbors[u]);
    while (index(G->neighbors[u]) != -1) {
      if (get(G->neighbors[u]) == v) {
        return;
        } else if (get(G->neighbors[u]) > v) {
          insertBefore(G->neighbors[u], v);
          break;
        }
      moveNext(G->neighbors[u]);
    }
    if (index(G->neighbors[u]) == -1) {
      append(G->neighbors[u], v);
    }
  }
  G->size++;
}

// Function DFS() will perform the depth first search algorithm on 𝐺.
/* Pesudocode from GraphAlgorithms.pdf
DFS(𝐺)
1. for all 𝑥 ∈ 𝑉(𝐺)
2. color[𝑥] = white
3. 𝑝[𝑥] = nil
4. time = 0
5. for all 𝑥 ∈ 𝑉(𝐺)
6. if color[𝑥] == white
7. Visit(𝑥)
*/
void DFS(Graph G, List S) {
   // checks
  if (G==NULL || S == NULL) { 
    printf("Graph Error: calling DFS() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  if (getOrder(G) != length(S)) {
    printf("Graph Error: Invalid stack and order");
    exit(EXIT_FAILURE);
  }
  // final
  for (int i = 1; i <= getOrder(G); i++) {
    G->color[i] = 'w';
    G->parent[i] = NIL;
  }
  int time = 0;
  moveFront(S);
  while (index(S) >= 0) {
    if (G->color[get(S)] == 'w')
      Visit(G, get(S), &time);
    moveNext(S);
  }
  // sort
  List temp = newList();
  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(temp);
    while (index(temp) != -1 && G->finished[get(temp)] > G->finished[i]) moveNext(temp);
    if (index(temp) == -1) append(temp, i);
    else insertBefore(temp, i);
  }
  clear(S);
  moveFront(temp);
  for (int i = 0; i < length(temp); i++) {
    append(S, get(temp));
    moveNext(temp);
  }
  freeList(&temp);
}

void Visit(Graph G, int x, int *time) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling Visit() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  // final
  G->discovered[x] = ++(*time);
  G->color[x] = 'g';
  moveFront(G->neighbors[x]);
  while (index(G->neighbors[x]) >= 0) {
    if (G->color[get(G->neighbors[x])] == 'w') {
      G->parent[get(G->neighbors[x])] = x;
      Visit(G, get(G->neighbors[x]), time);
    } 
    moveNext(G->neighbors[x]);
  }
  G->color[x] = 'b';
  G->finished[x] = ++(*time);
}

// Function transpose() returns a reference to a new graph object representing the transpose of G,
Graph transpose(Graph G) {
   // checks
  if (G==NULL) {
    printf("Graph Error: calling transpose() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  // final
  Graph T = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(G->neighbors[i]);
    while(index(G->neighbors[i]) >= 0) {
      addArc(T, get(G->neighbors[i]), i);
      moveNext(G->neighbors[i]);
    }
  }
  return T;
}

// Function copyGraph() returns a reference to a new graph that is a copy of G
Graph copyGraph(Graph G) {
   // checks
  if (G==NULL) {
    printf("Graph Error: calling copyGraph() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  // final
  Graph C = newGraph(getOrder(G));
  for (int i = 1; i <= getOrder(G); i++) {
    moveFront(G->neighbors[i]);
    while (index(G->neighbors[i]) >= 0) {
      addArc(C, i, get(G->neighbors[i]));
      moveNext(G->neighbors[i]);
    }
  }
  C->order = getOrder(G);
  return C;
}

// Function printGraph() prints the adjacency list representation of G to the file pointed to by out.
void printGraph(FILE* out, Graph G){
  // checks
  if (G==NULL) {
    printf("Graph Error: calling printGraph() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
	for (int i = 1; i <= getOrder(G); i++){
		fprintf(out, "%d: ", i);
		printList(out, G->neighbors[i]);
		fprintf(out, "\n");
	}
}