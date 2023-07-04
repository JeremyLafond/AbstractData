/*
Jeremy Lafond
jalafond
pa5
*/
#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#include "List.h"
#define white 1
#define gray 2
#define black 3
#define NIL 0
#define UNDEF -1

typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/

int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/

void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);
Graph transpose(Graph G);
Graph copyGraph(Graph G);

/*** Other operations ***/

void printGraph(FILE* out, Graph G);

#endif