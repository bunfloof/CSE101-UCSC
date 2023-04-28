/********************************************************************************* 
* Bun Ma, jma363
* 2022 Winter CSE101 PA2
* Graph.c 
* Graph for Graph
*********************************************************************************/ 
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "Graph.h"

#define INF -6
#define NIL -9

typedef struct GraphObj{
	List *neighbors;
	char *color;
	int *parent;
	int *distance;
	int order;
	int size;
	int source;
} GraphObj;

/*** Constructors-Destructors ***/

// Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges.
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	assert(G!=NULL);
	
	G->neighbors = malloc(sizeof(List*) * (n + 1));
 	G->color = malloc(sizeof(char*) * (n + 1));
 	G->parent = malloc(sizeof(int*) * (n + 1));
 	G->distance = malloc(sizeof(int*) * (n + 1));

	for (int i = 1; i <= n; i++) {
    G->neighbors[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

  G->order = n;
  G->size = 0;
  G->source = NIL;
  
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
		free((*pG)->distance);
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
// Function getSource returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling getSource() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }
  // final
  return(G->source);
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
  if (G->source == NIL) return NIL;
  if (u >= 1 && u <= G->order) {
    return(G->parent[u]);
  } else {
    printf("Graph Error: calling getSource() unknown error\n");
    exit(EXIT_FAILURE);
  }
}
// Function getDist() returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
// precondition 1 <= u <= getOrder(G).
int getDist(Graph G, int u) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling getDist() on NULL Graph\n");
    exit(EXIT_FAILURE);
  }  
  if (1 > u || u > getOrder(G)) {
    printf("Graph Error: calling getDist() on invalid vertex\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (G->source == NIL) return INF; // INF
  if (u >= 1 && u <= G->order) {
    return G->distance[u];
  } else {
    printf("Graph Error: calling getDist() unknown error\n");
    exit(EXIT_FAILURE);
  }
}
// Function getPath() appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists.
// precondition 1 <= u <= getOrder(G).
void getPath(List L, Graph G, int u) {
  // checks
  if (G==NULL) {
    printf("Graph Error: calling getPath() on NULL Graph\n");
    exit(EXIT_FAILURE);
  } 
  if (L==NULL) {
    printf("Graph Error: calling getPath() on NULL List\n");
    exit(EXIT_FAILURE);
  }  
  if (1 > u || u > getOrder(G)) {
    printf("Graph Error: calling getPath() on invalid vertex\n");
    exit(EXIT_FAILURE);
  }
  if (G->source == NIL) {
    printf("Graph Error: calling getPath() on invalid before BFS call\n");
    exit(EXIT_FAILURE);
  }
  // final
  if (u == getSource(G)) {
    append(L, u);
  } else if (G->parent[u] == NIL) {
    append(L, NIL);
  } else {
    getPath(L, G, G->parent[u]);
    append(L, u); // retog
  }
}
 
/*** Manipulation procedures ***/
// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G) {
  for (int i = 1; i <= getOrder(G); i++) {
    freeList(&G->neighbors[i]);
    G->color[i] = 'w';
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  G->size = 0;
  G->source = NIL;
}
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
  if (u == v) {
    printf("Graph Error: calling addEdge() on invalid vertex u and v\n");
    exit(EXIT_FAILURE);
  }
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
  if (u == v) {
    printf("Graph Error: calling addEdge() on invalid vertex u and v\n");
    exit(EXIT_FAILURE);
  }
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
// Function BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly.
void BFS(Graph G, int s) {
  for (int i = 1; i <= getOrder(G); i++) {
    G->color[i] = 'w';
    G->distance[i] = INF;
    G->parent[i] = NIL;
  }

  G->color[s] = 'g';
  G->distance[s] = 0;
  G->parent[s] = NIL;

  List Q = newList();
  append(Q, s);

  while(length(Q) > 0) {
    moveFront(Q);
    int x = get(Q);
    deleteFront(Q);
    moveFront(G->neighbors[x]);
    while(index(G->neighbors[x]) != -1) {
      int y = get(G->neighbors[x]);
      if (G->color[y] == 'w') {
        G->color[y] = 'g';
        G->distance[y] = G->distance[x] + 1;
        G->parent[y] = x;
        append(Q, y);
      }
      moveNext(G->neighbors[x]);
    }
    G->color[x] = 'b';
  }
  G->source = s;
  freeList(&Q);
}

// extra functions

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